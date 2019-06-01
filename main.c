#include "cancer_lang.h"
#include "parser.h"
#include "lexer.h"

#include <stdio.h>

int yyparse(Statement **program, yyscan_t scanner);
Statement* ParseFile(FILE* file);

int main()
{
  FILE *myfile = fopen("code.cl", "r");
  if (!myfile) {
    printf ("Can't open!\n");
    return -1;
  }

  Statement *program = ParseFile(myfile);

  EvaluateStatement(program);
  FreeMemory();

  DeleteStatement(program);

  return 0;
}

Statement* ParseFile(FILE* file)
{
  Statement *statement;
  yyscan_t scanner;
  YY_BUFFER_STATE state;

  if (yylex_init(&scanner))
  {
    printf("Error: initalizing scanner \n");
    return NULL;
  }

  state = yy_create_buffer(file, YY_BUF_SIZE, scanner);
  yy_switch_to_buffer(state, scanner);

  if(yyparse(&statement, scanner))
  {
    printf("Error: encountered while parsing \n");
    return NULL;
  }

  yy_delete_buffer(state, scanner);
  yylex_destroy(scanner);

  return statement;
  
}