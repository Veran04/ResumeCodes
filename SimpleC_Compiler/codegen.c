#include <stdio.h>
#include "table.h"
#include "codegen.h"

#define PUSH(arg1) printf( "\tpush\t%s\n", arg1 )
#define POP(arg1) printf( "\tpop\t%s\n", arg1 )
#define MOV(arg1, arg2) printf("\tmov\t%s, %s\n", arg1, arg2)
#define MOV_FROM_IMMEDIATE(arg1, arg2) printf("\tmov\t$%d, %s\n", arg1, arg2)
#define MOV_FROM_OFFSET(offset, reg) printf("\tmov\t-%d(%%rbp), %s\n", offset, reg)
#define MOV_TO_OFFSET(reg, offset) printf("\tmov\t%s, -%d(%%rbp)\n", reg, offset)
#define MOV_FROM_GLOBAL(reg, global) printf("\tmov\t%s(%%rip), %s\n", global, reg)
#define MOV_TO_GLOBAL(reg, global) printf("\tmov\t%s, %s(%%rip)\n", reg, global)
#define ADD(arg1, arg2) printf("\tadd\t%s, %s\n", arg1, arg2)
#define SUB(arg1, arg2) printf("\tsub\t%s, %s\n", arg1, arg2)
#define SUBCONST(arg1, arg2) printf("\tsub\t$%d, %s\n", arg1, arg2)
#define IMUL(arg1, arg2) printf("\timul\t%s, %s\n", arg1, arg2)
#define CDQ() printf("\tcdq\n")
#define IDIV(reg) printf("\tidiv\t%s\n", reg)
#define CALL(arg1) printf("\tcall\t%s\n", arg1)
#define RET printf("\tret\n")
#define COMMENT(arg1) printf("\t# %s\n", arg1)
#define CMP(arg1, arg2) printf("\tcmp\t%s, %s\n", arg1, arg2)
#define JMP(arg1) printf("\tjmp\t.L%d\n", arg1)
#define JE(arg1) printf("\tje\t.L%d\n", arg1)
#define XX() printf(".L%d:\n", counter++)
int counter=0;

const string const param_registers[] = { "%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"}; // all const

static void codegen_main(T_main main);

static void codegen_decllist(T_decllist decllist);

static void codegen_stmtlist(T_stmtlist stmtlist);

static void codegen_funclist(T_funclist funclist);

static void codegen_func(T_func func);

static void codegen_stmtlist(T_stmtlist stmtlist);

static void codegen_stmt(T_stmt stmt);

static void codegen_assignstmt(T_stmt stmt);

static void codegen_ifstmt(T_stmt stmt);

static void codegen_ifelsestmt(T_stmt stmt);

static void codegen_whilestmt(T_stmt stmt);

static void codegen_compoundstmt(T_stmt stmt);

static void codegen_expr(T_expr expr);

static void codegen_identexpr(T_expr expr);

static void codegen_callexpr(T_expr expr);

static void codegen_intexpr(T_expr expr);

static void codegen_charexpr(T_expr expr);

static void codegen_strexpr(T_expr expr);

static void codegen_arrayexpr(T_expr expr);

static void codegen_unaryexpr(T_expr expr);

static void codegen_binaryexpr(T_expr expr);

static void codegen_castexpr(T_expr expr);

static void emit_prologue(int size);

static void emit_epilogue();

static int bitwidth(T_type type);

typedef struct S_offset_scope *T_offset_scope;

struct S_offset_scope {
  T_table table;
  int stack_size;
  int current_offset;
  T_offset_scope parent;
};

static T_offset_scope create_offset_scope(T_offset_scope parent) {
  T_offset_scope offset_scope = xmalloc(sizeof(*offset_scope));
  offset_scope->table = create_table();
  // start after the dynamic link to the caller's %rbp
  offset_scope->current_offset = 8;
  offset_scope->stack_size = 0;
  offset_scope->parent = parent;
  return offset_scope;
}

static T_offset_scope destroy_offset_scope(T_offset_scope offset_scope) {
  T_offset_scope parent_offset_scope = offset_scope->parent;
  destroy_table(offset_scope->table);
  free(offset_scope);
  return parent_offset_scope;
}

struct S_offset {
  int offset;
};

typedef struct S_offset * T_offset;

static T_table global_symbols;

static T_offset_scope current_offset_scope;

void insert_offset(T_offset_scope scope, string ident, int size) {
  T_offset entry = xmalloc(sizeof(*entry));
  entry->offset = scope->current_offset;
  insert(scope->table, ident, (void*) entry);
  scope->stack_size += size;
  scope->current_offset += size;
}

static int lookup_offset_in_scope(T_offset_scope offset_scope, string ident) {
  T_offset offset = (T_offset) lookup(offset_scope->table, ident);
  if (NULL == offset) {
    fprintf(stderr, "FATAL: symbol not in table.  double-check the code that inserts the symbol into the offset scope.");
  }
  return offset->offset;
}

static T_offset lookup_offset_in_all_offset_scopes(T_offset_scope offset_scope, string ident) {
  // loop over each offset_scope and check for a binding for ident
  while (NULL != offset_scope) {
    // check for a binding in this offset_scope
    T_offset offset = (T_offset) lookup(offset_scope->table, ident);
    if (NULL != offset) {
      return offset;
    }
    // no binding in this offset_scope, so check the parent
    offset_scope = offset_scope->parent;
  }
  // found no binding in any offset_scope
  return NULL;
}

void codegen(T_prog prog) {
  // no need to record symbols in the global offset_scope.  the assembler and linker handle them.
  current_offset_scope = NULL;
  
  // emit assembly header
  printf(".file \"stdin\"\n");
  
  // emit a .comm for global vars
  global_symbols = create_table();
  // loop over each global symbol.  emit .comm and add to global symtab
  T_decllist decllist = prog->decllist;
  while (NULL != decllist) {
    if (E_functiontype != decllist->decl->type->kind) {
      printf(".comm\t%s,%d\n", decllist->decl->ident, bitwidth(decllist->decl->type));
      insert(global_symbols, decllist->decl->ident, decllist->decl->ident);
    }
    decllist = decllist->tail;
  }

  // emit an .rodata section and label for strings
  fprintf(stderr, "TODO: collect string constants");

  // go through each function
  codegen_funclist(prog->funclist);

  // generate the code for main
  codegen_main(prog->main);

  // free the global symbol table
  free(global_symbols);
}

static void codegen_main(T_main main) {
  // create a new scope
  current_offset_scope = create_offset_scope(NULL);

  // emit the pseudo ops for the function definition
  printf(".text\n");
  printf(".globl %s\n", "main");
  printf(".type %s, @function\n", "main");

  // emit a label for the function
  printf("%s:\n", "main");

  // add local declarations to the scope
  codegen_decllist(main->decllist);

  COMMENT("stack space for argc and argv");
  insert_offset(current_offset_scope, "argc", 8);  // int argc
  insert_offset(current_offset_scope, "argv", 8);  // char **argv

  COMMENT("emit main's prologue");
  emit_prologue(current_offset_scope->stack_size);

  COMMENT("move argc and argv from parameter registers to the stack");
  int offset;
  offset = lookup_offset_in_scope(current_offset_scope, "argc");
  MOV_TO_OFFSET("%rdi", offset);
  offset = lookup_offset_in_scope(current_offset_scope, "argv");
  MOV_TO_OFFSET("%rsi", offset);
  
  COMMENT("generate code for the body");
  codegen_stmtlist(main->stmtlist);

  COMMENT("generate code for the return expression");
  codegen_expr(main->returnexpr);
  COMMENT("save the return expression into %rax per the abi");
  POP("%rax");

  COMMENT("emit main's epilogue");
  emit_epilogue();

  // exit the scope
  current_offset_scope = destroy_offset_scope(current_offset_scope);
}

static void codegen_funclist(T_funclist funclist) {
  while (NULL != funclist) {
    codegen_func(funclist->func);
    funclist = funclist->tail;
  }
}

static void codegen_func(T_func func) {
  fprintf(stderr, "TODO: codegen_func (remove this message when implemented).");
  //create a new scope for the function
  current_offset_scope = create_offset_scope(NULL);
  //emit the pseudo ops for the function definition
  printf(".text\n");
  printf(".globl %s\n", func->ident);
  printf(".type %s, @function\n", func->ident);
  //emit a label for the function, which is name followed by colon:
  printf("%s:\n", func->ident);
  //insert the parameter into the offset table. for this simplified project, you can always assume there is just one parameter in the parameter list
  insert_offset(current_offset_scope, func->paramlist->ident, 8);
  //add local declarations to the scope, by calling codegen_decllist
  codegen_decllist(func->decllist);
  //emit the function prologue by calling emit_prologue with the right size
  emit_prologue(current_offset_scope->stack_size);
  //move the one parameter onto the stack. look it up to find the offset, then move the parameter to that offset in the stack
  int offset;
  offset = lookup_offset_in_scope(current_offset_scope, func->paramlist->ident);
  MOV_TO_OFFSET("%rdi", offset);
  //generate code for the body of the function. recall that it's a statement list.
  codegen_stmtlist(func->stmtlist);
  //generate code for the return expression
  codegen_expr(func->returnexpr);
  //generate code to retrieve the value that the expression generator pushes onto the stack
  POP("%rax");
  //emit the epilogue
  emit_epilogue();
  //destroy the function's scope
  current_offset_scope = destroy_offset_scope(current_offset_scope);
}

static void codegen_decllist(T_decllist decllist) {
  fprintf(stderr, "TODO: codegen_decllist (remove this message when implemented).");
  //loop over each element in the decllist list.
  while (NULL != decllist) {
    //insert each element into the offset_scope
    insert_offset(current_offset_scope, decllist->decl->ident, 8);
    decllist = decllist->tail;
}
}

/* statements */
static void codegen_stmtlist(T_stmtlist stmtlist) {
  while (NULL != stmtlist) {
    codegen_stmt(stmtlist->stmt);
    stmtlist = stmtlist->tail;
  }
}

static void codegen_stmt(T_stmt stmt) {
  if (NULL == stmt) {
    fprintf(stderr, "FATAL: stmt is NULL in codegen_stmt\n");
    exit(1);
  }
  switch (stmt->kind) {
  case E_assignstmt: codegen_assignstmt(stmt); break;
  case E_ifstmt: codegen_ifstmt(stmt); break;
  case E_ifelsestmt: codegen_ifelsestmt(stmt); break;
  case E_whilestmt: codegen_whilestmt(stmt); break;
  case E_compoundstmt: codegen_compoundstmt(stmt); break;
  default: fprintf(stderr, "FATAL: unexpected stmt kind in codegen_stmt\n"); exit(1); break;
  }
}

static void codegen_assignstmt(T_stmt stmt) {
  fprintf(stderr, "TODO: codegen_assignstmt (remove this message when implemented).");
  //generate code for the right-hand side of the assignment and save the resulting value into a register
  codegen_expr(stmt->assignstmt.right);
  POP("%rax");
  //find the address of the left-hand side of the assignment.
  int offset = lookup_offset_in_scope(current_offset_scope, stmt->assignstmt.left->identexpr);
  MOV_TO_OFFSET("%rax", offset);
}

static void codegen_ifstmt(T_stmt stmt) {
  // pending project 4
  fprintf(stderr, "TODO: codegen_ifstmt (project 4)\n");
  codegen_expr(stmt->ifstmt.cond);
  POP("%rax");
  CMP("$0", "%rax");
  JE(counter);
  codegen_stmt(stmt->ifstmt.body);
  XX();
}

static void codegen_ifelsestmt(T_stmt stmt) {
  /*fprintf(stderr, "TODO: codegen_ifelsestmt (project 4)\n");
  codegen_expr(stmt->ifelsestmt.cond);
  POP("%rax");
  CMP("$0", "%rax");
  JE(counter);
  codegen_stmt(stmt->ifelsestmt.ifbranch);
  JMP(counter);
  XX();
  codegen_stmt(stmt->ifelsestmt.elsebranch);
  XX();*/
}

static void codegen_whilestmt(T_stmt stmt) {
  // pending project 4
  fprintf(stderr, "TODO: codegen_whilestmt (project 4)\n");
}

static void codegen_compoundstmt(T_stmt stmt) {
  fprintf(stderr, "TODO: codegen_compoundstmt (remove this message when implemented).");
  codegen_decllist(stmt->compoundstmt.decllist);
  codegen_stmtlist(stmt->compoundstmt.stmtlist);
}

/* expressions */
static void codegen_expr(T_expr expr) {
  if (NULL == expr) {
    fprintf(stderr, "FATAL: unexpected NULL in codegen_expr\n");
    exit(1);
  }
  switch (expr->kind) {
  case E_identexpr: codegen_identexpr(expr); break;
  case E_callexpr: codegen_callexpr(expr); break;
  case E_intexpr: codegen_intexpr(expr); break;
  case E_charexpr: codegen_charexpr(expr); break;
  case E_strexpr: codegen_strexpr(expr); break;
  case E_arrayexpr: codegen_arrayexpr(expr); break;
  case E_unaryexpr: codegen_unaryexpr(expr); break;
  case E_binaryexpr: codegen_binaryexpr(expr); break;
  case E_castexpr: codegen_castexpr(expr); break;
  default: fprintf(stderr, "FATAL: unexpected expr kind in codegen_expr\n"); exit(1); break;
  }
}

static void codegen_identexpr(T_expr expr) {
  // todo: given in class
  //look up the ident, then move it to an intermidate register
  int offset = lookup_offset_in_scope(current_offset_scope, expr->identexpr);
  MOV_FROM_OFFSET(offset, "%rax");
  PUSH("%rax");
}

static void codegen_callexpr(T_expr expr) {
  fprintf(stderr, "TODO: codegen_callexpr (remove this message when implemented).");
  //generate code for the parameter's expression. recall that this will be saved onto the stack
  codegen_expr(expr->callexpr.args->expr);
  POP("%rax");
  //pass the parameter to the callee via the %rdi register according to the intel abi
  MOV("%rax", "%rdi");
  //emit the call instruction to the function's identifier
  CALL(expr->callexpr.ident);
  //save the return value by pushing it onto the stack. the return value is passed via %rax according to the intel abi
  PUSH("%rax");
}

static void codegen_intexpr(T_expr expr) {
  fprintf(stderr, "TODO: codegen_intexpr (remove this message when implemented).");
  COMMENT("push the integer");
  MOV_FROM_IMMEDIATE((int) expr->intexpr, "%rax");
  PUSH("%rax");
}

static void codegen_charexpr(T_expr expr) {
  COMMENT("push the character");
  MOV_FROM_IMMEDIATE((int) expr->charexpr, "%rax");
  PUSH("%rax");
}

static void codegen_strexpr(T_expr expr) {
  /*fprintf(stderr, "TODO: codegen_strexpr\n");
  COMMENT("push the string");
  int x = atoi(expr->strexpr);
  MOV_FROM_IMMEDIATE((int) x, "%rax");
  PUSH("%rax");*/                                           //uncomment after other test cases are done for potential bonus
}

static void codegen_arrayexpr(T_expr expr) {
  // bonus exercise
}

static void codegen_unaryexpr(T_expr expr) {
  fprintf(stderr, "TODO: codegen_unaryexpr\n");
}

static void codegen_binaryexpr(T_expr expr) {
  fprintf(stderr, "TODO: codegen_binaryexpr (remove this message when implemented).");
  //generate code for the left and right operands of the current expression
  codegen_expr(expr->binaryexpr.left);
  codegen_expr(expr->binaryexpr.right);
  //pop the result of each operand (the right one will be first, since it was pushed last)
  POP("%rbx");
  POP("%rax");
  //compute the result of the current expression
   switch(expr->binaryexpr.op){
    case E_op_plus:
      ADD("%rbx", "%rax");
      PUSH("%rax");
      break;
    case E_op_minus:
      SUB("%rbx", "%rax");
      PUSH("%rax");
      break;
    case E_op_times:
      IMUL("%rbx", "%rax");
      PUSH("%rax");
      break;
    case E_op_divide:
      CDQ();
      IDIV("%rbx");
      PUSH("%rax");
      break;
    case E_op_mod:
      CDQ();
      IDIV("%rbx");
      PUSH("%rdx");
      break;
    default:
      fprintf(stderr, "unexpected operator\n");
      exit(1);
  }
  //push the result onto the stack
}

static void codegen_castexpr(T_expr expr) {
  // bonus: truncate or extend data between bitwidths depending on type  
}

/**
 * Emit a function prologue, given some size in bytes of the local
 * variables in the stack frame.
 */
static void emit_prologue(int size) {
	//save stack
	PUSH("%rbp");
	MOV("%rsp", "%rbp");
	if (size > 0) {
		SUBCONST(size, "%rsp");
	}
	PUSH("%rbx");
}

static void emit_epilogue() {
	POP("%rbx");
	MOV("%rbp", "%rsp");
	POP("%rbp");
	RET;
}

/**
 * This function returns the size of a type in bytes.
 */
static int bitwidth(T_type type) {
  switch (type->kind) {
  case E_primitivetype:
    switch (type->primitivetype) {
    case E_typename_int:
      // 32-bit integers
      return 4;
    case E_typename_char:
      // characters are 1 byte
      return 1;
    default:
      fprintf(stderr, "FATAL: unexpected kind in compare_types\n");
      exit(1);
    }
    break;
  case E_pointertype:
    // pointers are to 64-bit addresses
    return 8;
  case E_arraytype:
    // arrays are the size times the bitwidth of the type
    return type->arraytype.size * bitwidth(type->arraytype.type);
  case E_functiontype:
    fprintf(stderr, "FATAL: functions as values are not supported\n");
    exit(1);
    break;
  default:
    fprintf(stderr, "FATAL: unexpected kind in bitwidth\n");
    exit(1);
    break;
  }  
}