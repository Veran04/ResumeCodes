give your command to main.c which will put it through the pipeline of our simplified C compiler as follows

the SimpleC language using the Bison parser generator. The parser.tab.c file is created from a grammar file, typically written in the .y format (e.g., parser.y). This parser is responsible for parsing SimpleC source code and generating an abstract syntax tree (AST) representation of the program. The file contains the functions, tables, and data structures necessary for the parser to recognize and process language tokens and their corresponding grammar rules, allowing the parser to construct the appropriate AST structures as it processes the SimpleC source code.

AST) representation of a SimpleC program. The main function, check_prog(), takes a T_prog object representing the program structure and traverses the AST, checking for type inconsistencies and errors.

The file includes several utility functions for handling global declarations (check_decllist()), function definitions (check_funclist()), statements (check_stmtlist()), and expressions (check_expr()). Specific types of statements and expressions have their corresponding type checking functions, such as check_assignstmt(), check_ifstmt(), check_whilestmt(), and more.

These type checking functions ensure that variables are used with the correct types, assignments have matching types on both sides, conditional expressions are of the correct type, and function calls have the right number and types of arguments. In case of type errors, the type_error() function is called to report an error. The typecheck.c file also manages scoping rules by creating and destroying symbol tables (create_scope(), destroy_scope()) as it traverses through the program.

The codegen.c file is responsible for generating assembly code from an abstract syntax tree (AST) representation of a SimpleC program. The primary function, codegen(), accepts a T_prog object representing the program structure and produces the corresponding x86-64 assembly code.

The file includes several utility functions for handling function declarations (codegen_func()), local variable declarations (codegen_decllist()), statements (codegen_stmtlist()), and expressions (codegen_expr()).

Different types of statements and expressions have their own corresponding code generation functions, such as codegen_assignstmt(), codegen_ifstmt(), codegen_whilestmt(), and codegen_binaryexpr().