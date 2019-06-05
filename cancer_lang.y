%{
#include "cancer_lang.h"
#include "parser.h"
#include "lexer.h"
#include <stdbool.h>


int yyerror(Line **statement, yyscan_t scanner, const char *msg)
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
%parse-param  { Line **program }
%parse-param  { yyscan_t scanner }

%union {
  #include <stdbool.h>

  Line *statement;
  expNumber *int_expression;
  expFlag *bool_expression;
  expWord *string_expression;
  expWrite *print_expression;
  Characteristic *parameter;
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
  line body { $$ = LineSeqGenerate($1, $2); }
  | line { $$ = $1; }

line: END_LINE { $$ = NULL; }
  | INT_TYPE NAME ASSIGNMENT int_exp { $$ = GenerateNumericCreation($2, $4); }
  | NAME ASSIGNMENT int_exp { $$ = GenerateNumericDefinition($1, $3); }
  | STRING_TYPE NAME ASSIGNMENT string_exp { $$ = GenerateWordCreation($2, $4); }
  | NAME ASSIGNMENT string_exp { $$ = GenerateWordDefinition($1, $3); }
  | BOOL_TYPE NAME ASSIGNMENT bool_exp { $$ = GenerateFlagCreation($2, $4); }
  | NAME ASSIGNMENT bool_exp { $$ = GenerateFlagDefinition($1, $3); }
  | PRINT print_exp { $$ = Write($2); }
  | IF bool_exp CURL_LEFT body CURL_RIGHT END_LINE ELSE CURL_LEFT body CURL_RIGHT { $$ = GeneratePositiveNegative($4, $9, $2); }
  | WHILE bool_exp CURL_LEFT body CURL_RIGHT { $$ = GenerateLoop($2, $4); }
  | NAME BRACKET_LEFT prm_values BRACKET_RIGHT { $$ = GenerateMagicShout($1, $3); }
  | FUNCTION NAME BRACKET_LEFT params BRACKET_RIGHT CURL_LEFT body CURL_RIGHT { $$ = NewMagic($2, $4, $7); }

int_exp:
  NAME { $$ = GenerateNumericSymbol($1); }
  | NUMBER { $$ = GenerateNumeric($1); }
  | int_exp MIN int_exp { $$ = GenerateSubtraction($1, $3); }
  | int_exp ADD int_exp { $$ = GenerateAddition($1, $3); }
  | int_exp MULTIPLY int_exp { $$ = GenerateMulExpression($1, $3); }
  | int_exp DIVIDE int_exp { $$ = GenerateDivExpression($1, $3); }
  | BRACKET_LEFT int_exp BRACKET_RIGHT { $$ = $2; }

string_exp:
  NAME { $$ = GenerateWordSymbol($1); }
  | WORD { $$ = GenerateWord($1); }
  

print_exp:
  NAME { $$ = GenerateWriteSymbol($1); }
  | WORD { $$ = GenerateWriteWord($1); }

bool_exp:
  TRUE { $$ = GenerateFlag(1); }
  | FALSE { $$ = GenerateFlag(0); }
  | NAME { $$ = GenerateFlagSymbol($1); }
  | int_exp LT int_exp { $$ = GenerateNumericLower($1, $3); }
  | int_exp LTE int_exp { $$ = GenerateNumericEvenLess($1, $3); }
  | int_exp GT int_exp { $$ = GenerateNumericGreater($1, $3); }
  | int_exp GTE int_exp { $$ = GenerateNumericEvenGreater($1, $3); }
  | int_exp EQUALS int_exp { $$ = GenerateNumericEven($1, $3); }
  | NOT bool_exp { $$ = GenerateNumericInvariant($2); }
  | bool_exp AND bool_exp { $$ = GenerateNumericWith($1, $3); }
  | bool_exp OR bool_exp { $$ = GenerateNumericEither($1, $3); }
  | BRACKET_LEFT bool_exp BRACKET_RIGHT { $$ = $2; }

prm:
  STRING_TYPE NAME { $$ = GenerateCharacteristic($2, STRING); }
  | INT_TYPE NAME { $$ = GenerateCharacteristic($2, INT); }
  | BOOL_TYPE NAME { $$ = GenerateCharacteristic($2, BOOL); }

params:
  prm { $$ = $1; }
  | prm COMMA params { $$ = GenerateCharacteristics($1, $3); }

prm_value:
  string_exp { $$ = GenerateWordExpCharacteritic($1); }
  | int_exp { $$ = GenerateNumericExpCharacteritic($1); }
  | bool_exp { $$ = GenerateFlagExpCharacteritic($1); }

prm_values: 
  prm_value { $$ = $1; }
  | prm_value COMMA prm_values { $$ = GenerateCharacteristics($1, $3); }

%%