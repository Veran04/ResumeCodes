#include <stdio.h>
#include <stdbool.h>

#include "ast_printer.h"
#include "util.h"
#include "table.h"
#include "typecheck.h"

static T_type INTTYPE;
static T_type CHARTYPE;
static T_type STRINGTYPE;
static T_type STRINGARRAYTYPE;

static T_scope current_scope;

static T_scope create_scope(T_scope parent) {
  T_scope scope = xmalloc(sizeof(*scope));
  scope->table = create_table();
  scope->parent = parent;
  return scope;
}

static void destroy_scope(T_scope scope) {
  free(scope);
}

static T_type lookup_in_all_scopes(T_scope scope, string ident) {
  // loop over each scope and check for a binding for ident
  while (NULL != scope) {
    // check for a binding in this scope
    T_type type = (T_type) lookup(scope->table, ident);
    if (NULL != type) {
      return type;
    }
    // no binding in this scope, so check the parent
    scope = scope->parent;
  }
  // found no binding in any scope
  return NULL;
}

/* the root of the AST */
void check_prog(T_prog prog) {
  // initialize useful types
  INTTYPE = create_primitivetype(E_typename_int);
  CHARTYPE = create_primitivetype(E_typename_char);
  STRINGTYPE = create_pointertype(CHARTYPE);
  STRINGARRAYTYPE = create_pointertype(STRINGTYPE);
  // create the global scope
  current_scope = create_scope(NULL);
  // add the global declarations
  check_decllist(prog->decllist);
  // check the function definitions
  check_funclist(prog->funclist);
  // check the main function
  check_main(prog->main);
  // clean-up the global scope
  destroy_scope(current_scope);
}

/* declarations and function definitions */
static void check_decllist(T_decllist decllist) {
  while (NULL != decllist) {
    check_decl(decllist->decl);
    decllist = decllist->tail;
  }
}

static void check_decl(T_decl decl) {
  //check for duplicate definitions in local T_scope
  if(NULL!=lookup(current_scope->table, decl->ident)){
    type_error("duplicate symbol declaration");
  }
  //add the binding
  insert(current_scope->table, decl->ident, decl->type);
}

static void check_funclist(T_funclist funclist) {
  while (NULL != funclist) {
    check_func(funclist->func);
    funclist = funclist->tail;
  }
}

static void check_func(T_func func) {
  fprintf(stderr, "check_func\n");
  //Check that the function is declared with a function type
  if(func->type == NULL){
    type_error("No type declared for the function");
  }
  //Check for duplicate definitions in the current scope
  T_type binding = lookup(current_scope->table, func->ident);
  if(NULL != binding){
    type_error("already exists");
  }
  //Add the function to the current (global) symbol table
  insert(current_scope->table, func->ident, func->type);
  //Create a new scope
  current_scope = create_scope(current_scope);
  //Add parameters to local scope
  T_typelist paramtypes = func->type->functiontype.paramtypes;
  T_paramlist paramlist = func->paramlist;
  while(NULL != paramtypes && NULL != paramlist ){
    //add the local variable declarations to the local symtab
    insert(current_scope->table, paramlist->ident, paramtypes->type);
    paramlist = paramlist->tail;
    paramtypes = paramtypes->tail;
  }
  //Check for an incorrect number of parameters (paramlist) compared to the type's list of parameters (paramtypes)
  if(NULL != paramlist || NULL != paramtypes){
    type_error("number of args does not match");
  }
  //check the function body for type errors
  check_decllist(func->decllist);
  check_stmtlist(func->stmtlist);
  //check the return expression for type errors
  check_expr(func->returnexpr);
  //check that the return expression's type matches the function type
  if(! compare_types(func->type->functiontype.returntype, func->returnexpr->type)){
    type_error("Function type and return expression type do not match");
  }
  //restore the parent scope
  T_scope parent_scope = current_scope->parent;
  destroy_scope(current_scope); current_scope = parent_scope;
} 

// GIVEN
static void check_main(T_main main) {
  fprintf(stderr, "check_main");
  // create a new scope
  current_scope = create_scope(current_scope);
  // add argc and argv with their C runtime types
  insert(current_scope->table, "argc", INTTYPE);
  insert(current_scope->table, "argv", STRINGARRAYTYPE);
  // add the declarations to the symtab
  check_decllist(main->decllist);
  // check the function body for type errors
  check_stmtlist(main->stmtlist);
  // check the return expression for type errors
  check_expr(main->returnexpr);
  // check that the return type is an int, per C runtime
  if (! compare_types(main->returnexpr->type, INTTYPE)) {
    type_error("the return expression type does not match the function type");
  }
  // restore the parent symbol table
  T_scope parent_scope = current_scope->parent;
  destroy_scope(current_scope); current_scope = parent_scope;
}

/* statements */
static void check_stmtlist(T_stmtlist stmtlist) {
  while (NULL != stmtlist) {
    check_stmt(stmtlist->stmt);
    stmtlist = stmtlist->tail;
  }
}

static void check_stmt(T_stmt stmt) {
  if (NULL == stmt) {
    fprintf(stderr, "FATAL: stmt is NULL in check_stmt\n");
    exit(1);
  }
  switch (stmt->kind) {
  case E_assignstmt: check_assignstmt(stmt); break;
  case E_ifstmt: check_ifstmt(stmt); break;
  case E_ifelsestmt: check_ifelsestmt(stmt); break;
  case E_whilestmt: check_whilestmt(stmt); break;
  case E_compoundstmt: check_compoundstmt(stmt); break;
  default: fprintf(stderr, "FATAL: unexpected stmt kind in check_stmt\n"); exit(1); break;
  }
}

static void check_assignstmt(T_stmt stmt) {
  // check the type of the left-hand-side
  check_expr(stmt->assignstmt.left);
  // check the type of the right-hand-side
  check_expr(stmt->assignstmt.right);
  // check that the left-hand-side is an l-value, i.e., an identexpr or a deref unary expression
  switch (stmt->assignstmt.left->kind) {
  case E_identexpr:
    // okay
    break;
  case E_unaryexpr:
    switch (stmt->assignstmt.left->unaryexpr.op) {
    case E_op_deref:
      // okay
      break;
    default:
      type_error("assignment is not to an l-value");
      break;
    }
    break;
  case E_arrayexpr:
    // okay
    break;
  default:
    type_error("assignment is not to an l-value");
    break;
  }
  // check that the types of the left- and right-hand sides match
  if (! compare_types(stmt->assignstmt.left->type, stmt->assignstmt.right->type)) {
    type_error("left- and right-hand sides of the assignstmt have mismatched types");
  }
}

static void check_ifstmt(T_stmt stmt) {
  fprintf(stderr, "check_ifstmt\n");
  // check the condition expression
  check_expr(stmt->ifstmt.cond);
  // check that the condition is an int
  if (! compare_types(stmt->ifstmt.cond->type, INTTYPE)) {
    type_error("if condition must be an int");
  }
  // recursively check the if branch
  check_stmt(stmt->ifstmt.body);
}

static void check_ifelsestmt(T_stmt stmt) {
  fprintf(stderr, "check_ifelsestmt\n");
  //check the condition expression
  check_expr(stmt->ifelsestmt.cond);
  //check that the condition is an int
  if(! compare_types(stmt->ifelsestmt.cond->type, INTTYPE)){
    type_error("ifelse condition must be an int");
  }
  //recursively check the ifelse branch
  check_stmt(stmt->ifelsestmt.ifbranch);
  check_stmt(stmt->ifelsestmt.elsebranch);
}

static void check_whilestmt(T_stmt stmt) {
  fprintf(stderr, "check_whilestmt\n");
  //check the condition expression
  check_expr(stmt->whilestmt.cond);
  //check that the condition is an int
  if(! compare_types(stmt->whilestmt.cond->type, INTTYPE)){
    type_error("while condition must be an int");
  }
  //recursively check the while branch
  check_stmt(stmt->whilestmt.body);
}

static void check_compoundstmt(T_stmt stmt) {
  fprintf(stderr, "check_compoundstmt\n");
  //Create a new scope before type checking the body. Restore parent scope after
  current_scope = create_scope(current_scope);
  check_stmtlist(stmt->compoundstmt.stmtlist);
  check_decllist(stmt->compoundstmt.decllist);
  T_scope parent_scope = current_scope->parent;
  destroy_scope(current_scope); 
  current_scope = parent_scope;
}

/* expressions */
static void check_expr(T_expr expr) {
  if (NULL == expr) {
    fprintf(stderr, "FATAL: unexpected NULL in check_expr\n");
    exit(1);
  }
  switch (expr->kind) {
  case E_identexpr: check_identexpr(expr); break;
  case E_callexpr: check_callexpr(expr); break;
  case E_intexpr: check_intexpr(expr); break;
  case E_charexpr: check_charexpr(expr); break;
  case E_strexpr: check_strexpr(expr); break;
  case E_arrayexpr: check_arrayexpr(expr); break;
  case E_unaryexpr: check_unaryexpr(expr); break;
  case E_binaryexpr: check_binaryexpr(expr); break;
  case E_castexpr: check_castexpr(expr); break;
  default: fprintf(stderr, "FATAL: unexpected expr kind in check-expr\n"); exit(1); break;
  }
}

static void check_identexpr(T_expr expr) {
  fprintf(stderr, "check_identexpr\n");
  //lookup the symbol below
  T_type binding = lookup_in_all_scopes(current_scope, expr->identexpr);
  //check that symbol has been declared below
  if (NULL==binding){
    type_error("use of undeclared symbol in identexpr");
  }
  //check that the symbol is not a function type below
  if(E_functiontype == binding->kind){
    type_error("cannot use a function as a value");
  }
  //set the type to the binding from the symlab below
  expr->type = binding;
}

static void check_callexpr(T_expr expr) {
  fprintf(stderr, "check_callexpr\n");
  //get the type from the symbtab or call to undeclared function type error
  T_type binding = lookup_in_all_scopes(current_scope, expr->callexpr.ident);
  if(NULL == binding){
    type_error("function call to undeclared symbol");
  }
  //check that the symbol is a function type
  if(E_functiontype != binding->kind){
    type_error("function call to symbol not declared as a function");
  }
  
  //compare the types of each expression to the function type or type error
  T_exprlist args = expr->callexpr.args;
  T_typelist paramtypes = binding->functiontype.paramtypes;
 
  
  while(NULL != args && NULL != paramtypes){
    check_expr(args->expr);
    if(! compare_types(args->expr->type, paramtypes->type)){
      type_error("type does not match");
    }
    args = args->tail;
    paramtypes = paramtypes->tail;
  }
   //check that the number of types matches or type error
  if(NULL != args || NULL != paramtypes){
    type_error("number of args does not match");
  }
  //set this expression to the function's return type
  expr->type = binding->functiontype.returntype;
}

static void check_intexpr(T_expr expr) {
  fprintf(stderr, "check_intexpr\n");
  // integer constants are int type by definition
  expr->type = INTTYPE;
}

static void check_charexpr(T_expr expr) {
  fprintf(stderr, "check_charexpr\n");
  //character constants are char type by definition
  expr->type = CHARTYPE;
}

static void check_strexpr(T_expr expr) {
  fprintf(stderr, "check_strexpr\n");
  //string constants are string type by definition
  expr->type = STRINGTYPE;
}

static void check_arrayexpr(T_expr expr) {
  fprintf(stderr, "check_arrayexpr\n");
//Check that the expr being dereferenced is either a pointer or an array type
check_expr(expr->arrayexpr.expr);
//A dereference unboxes the pointer type
if(expr->arrayexpr.expr->type->kind==E_arraytype){
  expr->type = expr->arrayexpr.expr->type->arraytype.type;
}
//An array access unboxes the array type
else if(expr->arrayexpr.expr->type->kind==E_pointertype){
  expr->type = expr->arrayexpr.expr->type->pointertype;
}
//It's a type error if the expression is neither an array or pointer
else{
  type_error("Expression is neither an array or pointer");
}
}

static void check_unaryexpr(T_expr expr) {
  fprintf(stderr, "check_unaryexpr\n");
  //Recursively check the operand
  check_expr(expr->unaryexpr.expr);
  //Check the type of the operator:
  switch(expr->unaryexpr.op){
    case E_op_ref:
      expr->type = create_pointertype(expr->unaryexpr.expr->type);
      break;
    case E_op_deref:
      if(expr->unaryexpr.expr->type->kind != E_pointertype) {
        type_error("attempted deref of non pointer");
      }
      expr->type = expr->unaryexpr.expr->type->pointertype;
      break;
    case E_op_minus:
      expr->type = expr->unaryexpr.expr->type;
      break;
    case E_op_not:
      expr->type = INTTYPE;
      break;
    default:
      fprintf(stderr, "unexpected operator\n");
      exit(1);
  }
}

  
  


static void check_binaryexpr(T_expr expr) {
  fprintf(stderr, "check_binaryexpr\n");
  //recursively check the left and right operands
  check_expr(expr->binaryexpr.left);
  check_expr(expr->binaryexpr.right);
  //check that both operators are the same type
  if(!compare_types(expr->binaryexpr.left->type, expr->binaryexpr.right->type)){
    type_error("operator mismatch");
  }
  switch(expr->binaryexpr.op){
    case E_op_plus:
      //fall through
    case E_op_minus:
      //fall through
    case E_op_times:
      //fall through
    case E_op_divide:
      //fall through
    case E_op_mod:
      expr->type = expr->binaryexpr.left->type;
      break;
    case E_op_lt:
      //fall through
    case E_op_gt:
      //fall through
    case E_op_le:
      //fall through
    case E_op_ge:
      //fall through
    case E_op_eq:
      //fall through
    case E_op_ne:
      expr->type = INTTYPE;
      break;
    case E_op_and:
      //fall through
    case E_op_or:
      expr->type = INTTYPE;
      break;
    default:
      fprintf(stderr, "unexpected operator\n");
      exit(1);
  }
}

static void check_castexpr(T_expr expr) {
fprintf(stderr, "check_castexpr\n");
check_expr(expr->castexpr.expr);
  //permit casting between any types (except functions, which expression can't be anyway)
  if(expr->castexpr.type->kind == E_functiontype){
    type_error("Expression cannot be a function");
  }
  expr->type = expr->castexpr.type;
}

/* type error */
static void type_error(char *msg) {
  fprintf(stderr, "%s\n", msg);
  exit(3);
}

/* type comparison */
bool compare_types(T_type type1, T_type type2) {
  if (NULL == type1 || NULL == type2) {
    fprintf(stderr, "FATAL: unexpected NULL values in compare_types\n");
    exit(1);
  }
  if (type1->kind == type2->kind) {
    switch (type1->kind) {
    case E_primitivetype:
      // the primitive type names should match
      return type1->primitivetype == type2->primitivetype;
      break;
    case E_pointertype:
      // the types the pointers point to should match
      return compare_types(type1->pointertype, type2->pointertype);
      break;
    case E_arraytype:
      // both the size and the type should match
      return type1->arraytype.size == type2->arraytype.size
        && compare_types(type1->arraytype.type, type2->arraytype.type);
      break;
    case E_functiontype:
      {
        // the parameter types, their number, and the return type should match
        T_typelist params1 = type1->functiontype.paramtypes;
        T_typelist params2 = type2->functiontype.paramtypes;
        while (NULL != params1 && NULL != params2) {
          if (! compare_types(params1->type, params2->type)) {
            // the parameter types do not match
            return false;
          }
          params1 = params1->tail;
          params2 = params2->tail;
        }
        if (NULL != params1 || NULL != params2) {
          // the number of parameters do not match
          return false;
        }
        return compare_types(type1->functiontype.returntype, type2->functiontype.returntype);
      }
      break;
    default:
      fprintf(stderr, "FATAL: unexpected kind in compare_types\n");
      exit(1);
    }
  } else {
    return false;
  }
}