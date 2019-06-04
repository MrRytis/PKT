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
  PrintExpression *print_expression;
  Parameter *parameter;
  char* var_name;
  char* string;
  int value;
  bool bval;
}

%type <statement> body line
%type <int_expression> int_exp
%type <bool_expression> bool_exp
%type <string_expression> string_exp
%type <print_expression> print_exp
%type <parameter> params prm prm_value prm_values

%token TRUE FALSE
%token INT_TYPE STRING_TYPE BOOL_TYPE
%token PRINT IF CURL_LEFT CURL_RIGHT ELSE WHILE FUNCTION COMMA
%token LTE GTE LT GT EQUALS NOT AND OR
%token BRACKET_LEFT BRACKET_RIGHT MULTIPLY ADD MIN DIVIDE ASSIGNMENT END_LINE

%token <value> NUMBER
%token <var_name> NAME
%token <string> WORD

%%
program: body { *program = $1; }

body:
  line body { $$ = BuildStatementSequence($1, $2); }
  | line { $$ = $1; }

line: END_LINE { $$ = NULL; }
  | INT_TYPE NAME ASSIGNMENT int_exp { $$ = BuildIntDeclaration($2, $4); }
  | NAME ASSIGNMENT int_exp { $$ = BuildIntAssignment($1, $3); }
  | STRING_TYPE NAME ASSIGNMENT string_exp { $$ = BuildStringDeclaration($2, $4); }
  | NAME ASSIGNMENT string_exp { $$ = BuildStringAssignment($1, $3); }
  | BOOL_TYPE NAME ASSIGNMENT bool_exp { $$ = BuildBoolDeclaration($2, $4); }
  | NAME ASSIGNMENT bool_exp { $$ = BuildBoolAssignment($1, $3); }
  | PRINT print_exp { $$ = BuildPrint($2); }
  | IF bool_exp CURL_LEFT body CURL_RIGHT END_LINE ELSE CURL_LEFT body CURL_RIGHT { $$ = BuildConditional($4, $9, $2); }
  | WHILE bool_exp CURL_LEFT body CURL_RIGHT { $$ = BuildWhile($2, $4); }
  | NAME BRACKET_LEFT prm_values BRACKET_RIGHT { $$ = BuildFunctionCall($1, $3); }
  | FUNCTION NAME BRACKET_LEFT params BRACKET_RIGHT CURL_LEFT body CURL_RIGHT { $$ = BuildFunction($2, $4, $7); }

int_exp:
  NAME { $$ = BuildIntVariable($1); }
  | NUMBER { $$ = BuildNumber($1); }
  | int_exp MIN int_exp { $$ = BuildDifference($1, $3); }
  | int_exp ADD int_exp { $$ = BuildSum($1, $3); }
  | int_exp MULTIPLY int_exp { $$ = BuildMultiplication($1, $3); }
  | int_exp DIVIDE int_exp { $$ = BuildDivision($1, $3); }
  | BRACKET_LEFT int_exp BRACKET_RIGHT { $$ = $2; }

string_exp:
  NAME { $$ = BuildStringVariable($1); }
  | WORD { $$ = BuildString($1); }
  

print_exp:
  NAME { $$ = BuildPrintVariable($1); }
  | WORD { $$ = BuildPrintString($1); }

bool_exp:
  TRUE { $$ = BuildBool(1); }
  | FALSE { $$ = BuildBool(0); }
  | NAME { $$ = BuildBoolVariable($1); }
  | int_exp LT int_exp { $$ = BuildLess($1, $3); }
  | int_exp LTE int_exp { $$ = BuildLessOrEquals($1, $3); }
  | int_exp GT int_exp { $$ = BuildMore($1, $3); }
  | int_exp GTE int_exp { $$ = BuildMoreOrEquals($1, $3); }
  | int_exp EQUALS int_exp { $$ = BuildEquals($1, $3); }
  | NOT bool_exp { $$ = BuildNot($2); }
  | bool_exp AND bool_exp { $$ = BuildAnd($1, $3); }
  | bool_exp OR bool_exp { $$ = BuildOr($1, $3); }
  | BRACKET_LEFT bool_exp BRACKET_RIGHT { $$ = $2; }

prm:
  STRING_TYPE NAME { $$ = BuildParam($2, STRING); }
  | INT_TYPE NAME { $$ = BuildParam($2, INT); }
  | BOOL_TYPE NAME { $$ = BuildParam($2, BOOL); }

params:
  prm { $$ = $1; }
  | prm COMMA params { $$ = BuildParameterList($1, $3); }

prm_value:
  string_exp { $$ = BuildStringValueParam($1); }
  | int_exp { $$ = BuildIntValueParam($1); }
  | bool_exp { $$ = BuildBoolValueParam($1); }

prm_values: 
  prm_value { $$ = $1; }
  | prm_value COMMA prm_values { $$ = BuildParameterList($1, $3); }

%%