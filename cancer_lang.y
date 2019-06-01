%{
#include "cancer_lang.h"
#include "parser.h"
#include "lexer.h"
#include <stdbool.h>

int yyerror(Statement **statement, yyscan_t scanner, const char *msg)
{
  printf("Error: %s\n", msg);
  return 0;
}
%}

%output  "parser.c"
%defines "parser.h"

%code requires {
#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
  
typedef void* yyscan_t;

#endif
}

%define api.pure

%lex-param    { yyscan_t scanner }
%parse-param  { Statement **program }
%parse-param  { yyscan_t scanner }

%union {
  #include <stdbool.h>

  Statement *statement;
  IntExpression *int_expression;
  BoolExpression *bool_expression;
  StringExpression *string_expression;
  char* var_name;
  char* string;
  int value;
  bool bval;
}

%type <statement> block statement
%type <int_expression> int_expression
%type <bool_expression> bool_expression
%type <string_expression> string_expression

%token TRUE FALSE
%token TYPE_INT TYPE_STRING TYPE_BOOL
%token PRINT IF L_CURL R_CURL ELSE
%token WHILE FUNCTION
%token LTEQ GTEQ LT GT EQUALS NOT AND OR
%token L_PAREN R_PAREN STAR PLUS MINUS SLASH ASSIGNMENT ENDL
%token <value> NUMBER
%token <var_name> VAR_NAME
%token <string> STRING_VAL

%%
program: block { *program = $1; }

block:
  statement block { $$ = BuildStatementSequence($1, $2); }
  | statement { $$ = $1; }

statement: ENDL { $$ = NULL; }
  | TYPE_INT VAR_NAME ASSIGNMENT int_expression { $$ = BuildIntDeclaration($2, $4); }
  | TYPE_STRING VAR_NAME ASSIGNMENT string_expression { $$ = BuildStringDeclaration($2, $4); }
  | TYPE_BOOL VAR_NAME ASSIGNMENT bool_expression { $$ = BuildBoolDeclaration($2, $4); }
  | VAR_NAME ASSIGNMENT int_expression { $$ = BuildIntAssignment($1, $3); }
  | VAR_NAME ASSIGNMENT string_expression { $$ = BuildStringAssignment($1, $3); }
  | VAR_NAME ASSIGNMENT bool_expression { $$ = BuildBoolAssignment($1, $3); }
  | IF bool_expression L_CURL block R_CURL ENDL ELSE L_CURL block R_CURL { $$ = BuildConditional($4, $9, $2); }
  | WHILE bool_expression L_CURL block R_CURL ENDL { $$ = BuildConditional($4, $2)}
  | PRINT VAR_NAME { $$ = BuildPrint($2); }

int_expression:
  NUMBER { $$ = BuildNumber($1); }
  | VAR_NAME { $$ = BuildIntVariable($1); }
  | int_expression STAR int_expression { $$ = BuildMultiplication($1, $3); }
  | int_expression SLASH int_expression { $$ = BuildDivision($1, $3); }
  | int_expression MINUS int_expression { $$ = BuildDifference($1, $3); }
  | int_expression PLUS int_expression { $$ = BuildSum($1, $3); }
  | L_PAREN int_expression R_PAREN { $$ = $2; }

string_expression:
  STRING_VAL { $$ = BuildString($1); }
  | VAR_NAME { $$ = BuildStringVariable($1); }

bool_expression:
  TRUE { $$ = BuildBool(1); }
  | FALSE { $$ = BuildBool(0); }
  | VAR_NAME { $$ = BuildBoolVariable($1); }
  | int_expression EQUALS int_expression { $$ = BuildEquals($1, $3); }
  | int_expression LTEQ int_expression { $$ = BuildLessOrEquals($1, $3); }
  | int_expression GTEQ int_expression { $$ = BuildMoreOrEquals($1, $3); }
  | int_expression LT int_expression { $$ = BuildLess($1, $3); }
  | int_expression GT int_expression { $$ = BuildMore($1, $3); }
  | NOT bool_expression { $$ = BuildNot($2); }
  | bool_expression AND bool_expression { $$ = BuildAnd($1, $3); }
  | bool_expression OR bool_expression { $$ = BuildOr($1, $3); }
  | L_PAREN bool_expression R_PAREN { $$ = $2; }

%%