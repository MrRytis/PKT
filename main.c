#include "cmm.h"
#include "p.h"
#include "l.h"

#include <stdio.h>

int yyparse(Line **program, yyscan_t scanner);
Line* ParseFile(FILE* file);

int main()
{
  FILE *myfile = fopen("code.cmm", "r");
  if (!myfile) {
    printf ("Can't open!\n");
    return -1;
  }

  Line *program = ParseFile(myfile);
  ProcessLine(program);

  EmptyRAM();
  EmptyMagicRAM();
  RemoveLine(program);

  return 0;
}

Line* ParseFile(FILE* file)
{
  Line *statement;
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
