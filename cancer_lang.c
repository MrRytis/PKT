#include "cancer_lang.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct SymbolStructure Symbol;
struct SymbolStructure
{
  char *Name;
  char *Value;
  VariableType Type;
  Symbol *Upcoming;
  char *Scope;
};

char *currentScope = "global";
Symbol *RAM;
Magic *MagicRAM;

Magic *ReceiveMagic(char *magic_name)
{
  if (NULL == MagicRAM)
    return NULL;

  Magic *endpoint = MagicRAM;
  while (NULL != endpoint->Upcoming)
  {
    if (0 == strcmp(endpoint->MagicName, magic_name))
      return endpoint;

    endpoint = endpoint->Upcoming;
  }

  if (0 == strcmp(endpoint->MagicName, magic_name))
    return endpoint;
  return NULL;
}

void RemoveCharacteristic(Characteristic *characteristic)
{
  Characteristic *pointer = characteristic;
  while (NULL != pointer)
  {
    Characteristic *temp = pointer;
    pointer = pointer->Upcoming;

    free(temp->Name);
    free(temp->Value);
    free(temp);
  }
}

void EmptyMagicRAM()
{
  Magic *pointer = MagicRAM;
  while (NULL != pointer)
  {
    Magic *temp = pointer;
    pointer = pointer->Upcoming;

    free(temp);
  }
}

Magic *GenerateMagic(char *title, Characteristic *characteristics, Line *content)
{
  Magic *endpoint = (Magic *)malloc(sizeof(Magic));
  if (NULL == endpoint)
    exit(-1);

  endpoint->MagicName = title;
  endpoint->Upcoming = NULL;
  endpoint->Content = content;
  endpoint->Characteristics = characteristics;
}

void GenerateNewMagic(char *title, Characteristic *characteristics, Line *content)
{
  if (NULL == MagicRAM)
  {
    MagicRAM = GenerateMagic(title, characteristics, content);
  }
  else
  {
    Magic *endpoint = MagicRAM;
    while (NULL != endpoint->Upcoming)
    {
      if (0 == strcmp(endpoint->MagicName, title))
        break;

      endpoint = endpoint->Upcoming;
    }

    endpoint->Upcoming = GenerateMagic(title, characteristics, content);
  }
}

Line *Write(expWrite *symbol)
{
  Line *endpoint = (Line *)malloc(sizeof(Line));
  if (NULL == endpoint)
    exit(-1);

  endpoint->Type = Print;
  endpoint->WriteText = symbol;

  return endpoint;
}

Line *LineSeqGenerate(Line *primary, Line *secondary)
{
  Line *endpoint = (Line *)malloc(sizeof(Line));
  if (NULL == endpoint)
    exit(-1);

  endpoint->Type = Sequence;
  endpoint->Left = primary;
  endpoint->Right = secondary;

  return endpoint;
}

Line *GeneratePositiveNegative(Line *positive, Line *negative, expFlag *decider)
{
  Line *endpoint = (Line *)malloc(sizeof(Line));
  if (NULL == endpoint)
    exit(-1);

  endpoint->Type = Conditional;
  endpoint->Left = positive;
  endpoint->Right = negative;
  endpoint->FlagVal = decider;

  return endpoint;
}

Line *GenerateLoop(expFlag *decider, Line *content)
{
  Line *endpoint = (Line *)malloc(sizeof(Line));
  if (NULL == endpoint)
    exit(-1);

  endpoint->Type = While;
  endpoint->Left = content;
  endpoint->FlagVal = decider;

  return endpoint;
}

Line *GenerateNumericDefinition(char *symbol, expNumber *value)
{
  Line *endpoint = (Line *)malloc(sizeof(Line));
  if (NULL == endpoint)
    exit(-1);

  endpoint->Type = IntAssignment;
  endpoint->Symbol = symbol;
  endpoint->NumericVal = value;

  return endpoint;
}

Line *GenerateWordDefinition(char *symbol, expWord *value)
{
  Line *endpoint = (Line *)malloc(sizeof(Line));
  if (NULL == endpoint)
    exit(-1);

  endpoint->Type = StringAssignment;
  endpoint->Symbol = symbol;
  endpoint->StringValue = value;

  return endpoint;
}

Line *GenerateFlagDefinition(char *symbol, expFlag *value)
{
  Line *endpoint = (Line *)malloc(sizeof(Line));
  if (NULL == endpoint)
    exit(-1);

  endpoint->Type = BoolAssignment;
  endpoint->Symbol = symbol;
  endpoint->FlagVal = value;

  return endpoint;
}

Line *GenerateNumericCreation(char *symbol, expNumber *value)
{
  Line *endpoint = (Line *)malloc(sizeof(Line));
  if (NULL == endpoint)
    exit(-1);

  endpoint->Type = IntDeclaration;
  endpoint->Symbol = symbol;
  endpoint->NumericVal = value;

  return endpoint;
}

Line *GenerateWordCreation(char *symbol, expWord *value)
{
  Line *endpoint = (Line *)malloc(sizeof(Line));
  if (NULL == endpoint)
    exit(-1);

  endpoint->Type = StringDeclaration;
  endpoint->Symbol = symbol;
  endpoint->StringValue = value;

  return endpoint;
}

Line *GenerateFlagCreation(char *symbol, expFlag *value)
{
  Line *endpoint = (Line *)malloc(sizeof(Line));
  if (NULL == endpoint)
    exit(-1);

  endpoint->Type = BoolDeclaration;
  endpoint->Symbol = symbol;
  endpoint->FlagVal = value;

  return endpoint;
}

Characteristic *GenerateCharacteristic(char *title, VariableType type)
{
  Characteristic *endpoint = (Characteristic *)malloc(sizeof(Characteristic));
  if (NULL == endpoint)
    exit(-1);

  endpoint->Type = type;
  endpoint->Name = title;
  endpoint->Upcoming = NULL;

  return endpoint;
}

Characteristic *GenerateNumericExpCharacteritic(expNumber *exp)
{
  Characteristic *endpoint = (Characteristic *)malloc(sizeof(Characteristic));
  if (NULL == endpoint)
    exit(-1);

  endpoint->Type = INT;
  endpoint->inte = exp;
  endpoint->Upcoming = NULL;

  return endpoint;
}

Characteristic *GenerateWordExpCharacteritic(expWord *exp)
{
  Characteristic *endpoint = (Characteristic *)malloc(sizeof(Characteristic));
  if (NULL == endpoint)
    exit(-1);

  endpoint->Type = STRING;
  endpoint->stringe = exp;
  endpoint->Upcoming = NULL;

  return endpoint;
}

Characteristic *GenerateFlagExpCharacteritic(expFlag *exp)
{
  Characteristic *endpoint = (Characteristic *)malloc(sizeof(Characteristic));
  if (NULL == endpoint)
    exit(-1);

  endpoint->Type = BOOL;
  endpoint->boole = exp;
  endpoint->Upcoming = NULL;

  return endpoint;
}

Characteristic *GenerateCharacteristics(Characteristic *primary, Characteristic *secondary)
{
  if (NULL == primary || NULL == secondary)
    exit(-1);

  primary->Upcoming = secondary;
  return primary;
}

Line *NewMagic(char *magic_name, Characteristic *characteristics, Line *content)
{
  Line *endpoint = (Line *)malloc(sizeof(Line));
  if (NULL == endpoint)
    exit(-1);

  endpoint->Symbol = magic_name;
  endpoint->Type = FunctionDeclaration;
  endpoint->Left = content;
  endpoint->Characteristics = characteristics;

  return endpoint;
}

Line *GenerateMagicShout(char *magic_name, Characteristic *values)
{
  Line *endpoint = (Line *)malloc(sizeof(Line));
  if (NULL == endpoint)
    exit(-1);

  endpoint->Symbol = magic_name;
  endpoint->Type = FunctionCall;
  endpoint->Characteristics = values;

  return endpoint;
}

expNumber *GenerateNumeric(int number)
{
  expNumber *endpoint = (expNumber *)malloc(sizeof(expNumber));
  if (NULL == endpoint)
    exit(-1);

  char str[10];
  snprintf(str, 10, "%d", number);

  endpoint->Type = IntLiteral;
  endpoint->Value = strdup(str);

  return endpoint;
}

expNumber *GenerateNumericUniversal(expNumber *left, expNumber *right, IntExpressionType type)
{
  expNumber *endpoint = (expNumber *)malloc(sizeof(expNumber));
  if (NULL == endpoint)
    exit(-1);

  endpoint->Type = type;
  endpoint->Left = left;
  endpoint->Right = right;

  return endpoint;
}

expNumber *GenerateAddition(expNumber *left, expNumber *right)
{
  return GenerateNumericUniversal(left, right, Addition);
}

expNumber *GenerateSubtraction(expNumber *left, expNumber *right)
{
  return GenerateNumericUniversal(left, right, Subtraction);
}

expNumber *GenerateMulExpression(expNumber *left, expNumber *right)
{
  return GenerateNumericUniversal(left, right, Multiplication);
}

expNumber *GenerateDivExpression(expNumber *left, expNumber *right)
{
  return GenerateNumericUniversal(left, right, Division);
}

expWord *GenerateWord(char *xword)
{
  expWord *endpoint = (expWord *)malloc(sizeof(expWord));
  if (NULL == endpoint)
    exit(-1);

  char *p = xword;
  p++;
  p[strlen(p) - 1] = 0;

  endpoint->Type = StringLiteral;
  endpoint->Value = p;

  return endpoint;
}

expFlag *GenerateFlag(int flag)
{
  expFlag *endpoint = (expFlag *)malloc(sizeof(expFlag));
  if (NULL == endpoint)
    exit(-1);

  char *value;

  if (flag == 1)
  {
    value = "true";
  }
  else
  {
    value = "false";
  }

  endpoint->Type = BoolLiteral;
  endpoint->Value = value;

  return endpoint;
}

expFlag *GenerateNumericCmpUniversal(expNumber *left, expNumber *right, BoolExpressionType type)
{
  expFlag *endpoint = (expFlag *)malloc(sizeof(expFlag));
  if (NULL == endpoint)
    exit(-1);

  endpoint->Type = type;
  endpoint->IntLeft = left;
  endpoint->IntRight = right;

  return endpoint;
}

expFlag *GenerateNumericEven(expNumber *left, expNumber *right)
{
  return GenerateNumericCmpUniversal(left, right, Equals);
}

expFlag *GenerateNumericEvenLess(expNumber *left, expNumber *right)
{
  return GenerateNumericCmpUniversal(left, right, LessEquals);
}

expFlag *GenerateNumericEvenGreater(expNumber *left, expNumber *right)
{
  return GenerateNumericCmpUniversal(left, right, MoreEquals);
}

expFlag *GenerateNumericLower(expNumber *left, expNumber *right)
{
  return GenerateNumericCmpUniversal(left, right, Less);
}

expFlag *GenerateNumericGreater(expNumber *left, expNumber *right)
{
  return GenerateNumericCmpUniversal(left, right, More);
}

expFlag *GenerateNumericInvariant(expFlag *value)
{
  expFlag *endpoint = (expFlag *)malloc(sizeof(expFlag));
  if (NULL == endpoint)
    exit(-1);

  endpoint->Type = Not;
  endpoint->Left = value;

  return endpoint;
}

expFlag *GenerateNumericWith(expFlag *left, expFlag *right)
{
  expFlag *endpoint = (expFlag *)malloc(sizeof(expFlag));
  if (NULL == endpoint)
    exit(-1);

  endpoint->Type = And;
  endpoint->Left = left;
  endpoint->Right = right;

  return endpoint;
}

expFlag *GenerateNumericEither(expFlag *left, expFlag *right)
{
  expFlag *endpoint = (expFlag *)malloc(sizeof(expFlag));
  if (NULL == endpoint)
    exit(-1);

  endpoint->Type = Or;
  endpoint->Left = left;
  endpoint->Right = right;

  return endpoint;
}

expNumber *GenerateNumericSymbol(char *symbol)
{
  expNumber *endpoint = (expNumber *)malloc(sizeof(expNumber));
  if (NULL == endpoint)
    exit(-1);

  endpoint->Symbol = symbol;
  endpoint->Type = IntVariable;

  return endpoint;
}

expWord *GenerateWordSymbol(char *symbol)
{
  expWord *endpoint = (expWord *)malloc(sizeof(expWord));
  if (NULL == endpoint)
    exit(-1);

  endpoint->Symbol = symbol;
  endpoint->Type = StringVariable;

  return endpoint;
}

expFlag *GenerateFlagSymbol(char *symbol)
{
  expFlag *endpoint = (expFlag *)malloc(sizeof(expFlag));
  if (NULL == endpoint)
    exit(-1);

  endpoint->Symbol = symbol;
  endpoint->Type = BoolVariable;

  return endpoint;
}

expWrite *GenerateWriteWord(char *value)
{
  expWrite *endpoint = (expWrite *)malloc(sizeof(expWrite));
  if (NULL == endpoint)
    exit(-1);

  endpoint->Value = value;
  endpoint->Type = PrintString;

  return endpoint;
}

expWrite *GenerateWriteSymbol(char *symbol)
{
  expWrite *endpoint = (expWrite *)malloc(sizeof(expWrite));
  if (NULL == endpoint)
    exit(-1);

  endpoint->Symbol = symbol;
  endpoint->Type = PrintVariable;

  return endpoint;
}

void EmptyRAM()
{
  Symbol *pointer = RAM;
  while (NULL != pointer)
  {
    Symbol *temp = pointer;
    pointer = pointer->Upcoming;

    free(temp);
  }
}

Symbol *ReceiveSymbol(char *title)
{
  if (NULL == RAM)
    return NULL;

  Symbol *endpoint = RAM;
  while (NULL != endpoint->Upcoming)
  {
    if (0 == strcmp(endpoint->Name, title) && 0 == strcmp(endpoint->Scope, currentScope))
      return endpoint;

    endpoint = endpoint->Upcoming;
  }

  if (0 == strcmp(endpoint->Name, title) && 0 == strcmp(endpoint->Scope, currentScope))
    return endpoint;
  return NULL;
}

void InsertSymbol(char *title, char *value, VariableType type)
{
  if (NULL == RAM)
  {
    printf("Error: symbol %s does not exist", title);
    exit(-1);
  }

  Symbol *endpoint = RAM;
  while (NULL != endpoint->Upcoming)
  {
    if (0 == strcmp(endpoint->Name, title) && 0 == strcmp(endpoint->Scope, currentScope))
      break;

    endpoint = endpoint->Upcoming;
  }

  if (0 == strcmp(endpoint->Name, title) && 0 == strcmp(endpoint->Scope, currentScope))
  {
    endpoint->Value = value;
    return;
  }
}

Symbol *GenerateSymbol(char *title, char *value, VariableType type)
{
  Symbol *endpoint = (Symbol *)malloc(sizeof(Symbol));
  if (NULL == endpoint)
    exit(-1);

  endpoint->Name = title;
  endpoint->Value = value;
  endpoint->Upcoming = NULL;
  endpoint->Type = type;
  endpoint->Scope = currentScope;
}

void GenerateNewSymbol(char *title, char *value, VariableType type)
{
  if (NULL == RAM)
  {
    RAM = GenerateSymbol(title, value, type);
  }
  else
  {
    Symbol *endpoint = RAM;
    while (NULL != endpoint->Upcoming)
    {
      if (0 == strcmp(endpoint->Name, title) && 0 == strcmp(endpoint->Scope, currentScope))
        break;

      endpoint = endpoint->Upcoming;
    }

    endpoint->Upcoming = GenerateSymbol(title, value, type);
  }
}

char *ProcessExpNumeric(expNumber *exp)
{
  if (NULL == exp)
    return NULL;

  char *value;

  char temp[10];
  int left;
  int right;
  Symbol *symbol;

  switch (exp->Type)
  {
  case IntLiteral:
    value = exp->Value;
    break;
  case IntVariable:
    symbol = ReceiveSymbol(exp->Symbol);
    if (symbol == NULL)
    {
      printf("Error: symbol %s undeclared\n", exp->Symbol);
      exit(-1);
    }
    value = symbol->Value;
    break;
  case Multiplication:
    left = atoi(ProcessExpNumeric(exp->Left));
    right = atoi(ProcessExpNumeric(exp->Right));

    snprintf(temp, 10, "%d", left * right);
    value = strdup(temp);
    break;
  case Subtraction:
    left = atoi(ProcessExpNumeric(exp->Left));
    right = atoi(ProcessExpNumeric(exp->Right));

    snprintf(temp, 10, "%d", left - right);
    value = strdup(temp);
    break;
  case Division:
    left = atoi(ProcessExpNumeric(exp->Left));
    right = atoi(ProcessExpNumeric(exp->Right));
    if (right == 0)
    {
      printf("Error: divison by zero\n");
      exit(-1);
    }

    snprintf(temp, 10, "%d", left / right);
    value = strdup(temp);
    break;
  case Addition:
    left = atoi(ProcessExpNumeric(exp->Left));
    right = atoi(ProcessExpNumeric(exp->Right));

    snprintf(temp, 10, "%d", left + right);
    value = strdup(temp);
    break;
  }

  return value;
}

char *ProcessExpWord(expWord *exp)
{
  if (NULL == exp)
    return NULL;

  char *value;
  Symbol *symbol;
  switch (exp->Type)
  {
  case StringLiteral:
    value = exp->Value;
    break;
  case StringVariable:
    symbol = ReceiveSymbol(exp->Symbol);
    if (symbol == NULL)
    {
      printf("Error: symbol %s undeclared\n", exp->Symbol);
      exit(-1);
    }
    value = symbol->Value;
    break;
  }

  return value;
}

void ProcessExpWrite(expWrite *exp)
{
  if (NULL == exp)
    return;

  Symbol *symbol;
  char *p;
  switch (exp->Type)
  {
  case PrintString:
    p = exp->Value;
    p++;
    p[strlen(p) - 1] = 0;

    printf("%s\n", p);
    break;
  case PrintVariable:
    symbol = ReceiveSymbol(exp->Symbol);
    if (symbol == NULL)
    {
      printf("Error: symbol %s undeclared\n", exp->Symbol);
      exit(-1);
    }

    printf("%s\n", symbol->Value);
    break;
  }
}

int ReceiveFlagVal(char *value)
{
  if (value == "true")
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

char *ReceiveNumericFlagVal(int value)
{
  if (value == 1)
  {
    return "true";
  }
  else
  {
    return "false";
  }
}

char *ProcessExpFlag(expFlag *exp)
{
  if (NULL == exp)
    return NULL;

  char *value;
  int temp;
  Symbol *symbol;
  switch (exp->Type)
  {
  case BoolLiteral:
    value = exp->Value;
    break;
  case BoolVariable:
    symbol = ReceiveSymbol(exp->Symbol);
    if (symbol == NULL)
    {
      printf("Error: symbol %s undeclared\n", exp->Symbol);
      exit(-1);
    }
    value = symbol->Value;
    break;
  case Equals:
    temp = atoi(ProcessExpNumeric(exp->IntLeft)) == atoi(ProcessExpNumeric(exp->IntRight));

    value = ReceiveNumericFlagVal(temp);
    break;
  case And:
    temp = ReceiveFlagVal(ProcessExpFlag(exp->Left)) && ReceiveFlagVal(ProcessExpFlag(exp->Right));

    value = ReceiveNumericFlagVal(temp);
    break;
  case Not:
    temp = ReceiveFlagVal(ProcessExpFlag(exp->Left));

    if (temp == 1)
    {
      value = "false";
    }
    else
    {
      value = "true";
    }
    break;
  case Or:
    temp = ReceiveFlagVal(ProcessExpFlag(exp->Left)) || ReceiveFlagVal(ProcessExpFlag(exp->Right));

    value = ReceiveNumericFlagVal(temp);
    break;
  case Less:
    temp = atoi(ProcessExpNumeric(exp->IntLeft)) < atoi(ProcessExpNumeric(exp->IntRight));

    value = ReceiveNumericFlagVal(temp);
    break;
  case More:
    temp = atoi(ProcessExpNumeric(exp->IntLeft)) > atoi(ProcessExpNumeric(exp->IntRight));

    value = ReceiveNumericFlagVal(temp);
    break;
  case MoreEquals:
    temp = atoi(ProcessExpNumeric(exp->IntLeft)) >= atoi(ProcessExpNumeric(exp->IntRight));

    value = ReceiveNumericFlagVal(temp);
    break;
  case LessEquals:
    temp = atoi(ProcessExpNumeric(exp->IntLeft)) <= atoi(ProcessExpNumeric(exp->IntRight));

    value = ReceiveNumericFlagVal(temp);
    break;
  }

  return value;
}

void ProcessMagicShout(Magic *function, Line *function_call)
{
  Characteristic *param = function->Characteristics;
  Characteristic *value = function_call->Characteristics;
  char *valuestr;
  while (NULL != param)
  {
    if (param->Type != value->Type)
    {
      printf("Error: function param type is not accepted\n");
      exit(-1);
    }

    if (value->Type == 0)
    {
      valuestr = ProcessExpNumeric(value->inte);
    }
    else if (value->Type == 1)
    {
      valuestr = ProcessExpWord(value->stringe);
    }
    else if (value->Type == 2)
    {
      valuestr = ProcessExpFlag(value->boole);
    }

    currentScope = function->MagicName;
    param->Value = valuestr;
    Symbol *var = ReceiveSymbol(param->Name);
    if (var == NULL)
    {
      GenerateNewSymbol(param->Name, valuestr, param->Type);
    }
    else
    {
      InsertSymbol(param->Name, valuestr, param->Type);
    }

    currentScope = "global";

    value = value->Upcoming;
    param = param->Upcoming;
  }

  currentScope = function->MagicName;
  ProcessLine(function->Content);
  currentScope = "global";
}

void ProcessLine(Line *line)
{
  if (NULL == line)
    return;

  char *value;
  Symbol *exValue;
  Magic *function;
  switch (line->Type)
  {
  case BoolDeclaration:
    value = ProcessExpFlag(line->FlagVal);
    exValue = ReceiveSymbol(line->Symbol);
    if (exValue == NULL)
    {
      GenerateNewSymbol(line->Symbol, value, BOOL);
      break;
    }
    printf("Error: symbol %s already declared\n", line->Symbol);
    exit(-1);
    break;

  case IntDeclaration:
    value = ProcessExpNumeric(line->NumericVal);
    exValue = ReceiveSymbol(line->Symbol);
    if (exValue == NULL)
    {
      GenerateNewSymbol(line->Symbol, value, INT);
      break;
    }
    printf("Error: symbol %s already declared\n", line->Symbol);
    exit(-1);
    break;

  case StringDeclaration:
    value = ProcessExpWord(line->StringValue);
    exValue = ReceiveSymbol(line->Symbol);
    if (exValue == NULL)
    {
      GenerateNewSymbol(line->Symbol, value, STRING);
      break;
    }
    printf("Error: symbol %s already declared\n", line->Symbol);
    exit(-1);
    break;

  case BoolAssignment:
    value = ProcessExpFlag(line->FlagVal);
    exValue = ReceiveSymbol(line->Symbol);
    if (exValue == NULL)
    {
      printf("Error: symbol %s undeclared\n", line->Symbol);
      exit(-1);
    }
    InsertSymbol(line->Symbol, value, BOOL);
    break;

  case IntAssignment:
    value = ProcessExpNumeric(line->NumericVal);
    exValue = ReceiveSymbol(line->Symbol);
    if (exValue == NULL)
    {
      printf("Error: symbol %s undeclared\n", line->Symbol);
      exit(-1);
    }
    InsertSymbol(line->Symbol, value, INT);
    break;

  case StringAssignment:
    value = ProcessExpWord(line->StringValue);
    exValue = ReceiveSymbol(line->Symbol);
    if (exValue == NULL)
    {
      printf("Error: symbol %s undeclared\n", line->Symbol);
      exit(-1);
    }
    InsertSymbol(line->Symbol, value, INT);
    break;
  case Print:
    ProcessExpWrite(line->WriteText);
    break;
  case Sequence:
    ProcessLine(line->Left);
    ProcessLine(line->Right);
    break;
  case Conditional:
    value = ProcessExpFlag(line->FlagVal);
    if (ReceiveFlagVal(value) == 1)
    {
      ProcessLine(line->Left);
    }
    else
    {
      ProcessLine(line->Right);
    }
    break;
  case While:
    value = ProcessExpFlag(line->FlagVal);
    while (ReceiveFlagVal(value) == 1)
    {
      ProcessLine(line->Left);
      value = ProcessExpFlag(line->FlagVal);
    }
    break;
  case FunctionDeclaration:
    if (currentScope != "global")
    {
      printf("Error: declaring functions inside functions is not allowed\n");
      exit(-1);
    }

    function = ReceiveMagic(line->Symbol);
    if (function != NULL)
    {
      printf("Error: function %s is already declared\n", line->Symbol);
      exit(-1);
    }

    GenerateNewMagic(line->Symbol, line->Characteristics, line->Left);
    break;
  case FunctionCall:
    function = ReceiveMagic(line->Symbol);
    if (function == NULL)
    {
      printf("Error: function %s is undeclared\n", line->Symbol);
      exit(-1);
    }

    ProcessMagicShout(function, line);
    break;
  }
}

void RemoveExpNumeric(expNumber *exp)
{
  if (NULL == exp)
    return;

  switch (exp->Type)
  {
  case IntLiteral:
    free(exp->Value);
    break;
  case IntVariable:
    free(exp->Symbol);
    break;
  case Subtraction:
    RemoveExpNumeric(exp->Left);
    RemoveExpNumeric(exp->Right);
    break;
  case Division:
    RemoveExpNumeric(exp->Left);
    RemoveExpNumeric(exp->Right);
    break;
  case Addition:
    RemoveExpNumeric(exp->Left);
    RemoveExpNumeric(exp->Right);
    break;
  case Multiplication:
    RemoveExpNumeric(exp->Left);
    RemoveExpNumeric(exp->Right);
    break;
  }
  free(exp);
}

void RemoveExpWord(expWord *exp)
{
  if (NULL == exp)
    return;

  switch (exp->Type)
  {
  case StringLiteral:
    free(exp->Value);
    break;
  case StringVariable:
    free(exp->Symbol);
    break;
  }
  free(exp);
}

void RemoveExpFlag(expFlag *exp)
{
  if (NULL == exp)
    return;

  switch (exp->Type)
  {
  case BoolLiteral:
    free(exp->Value);
    break;
  case BoolVariable:
    free(exp->Symbol);
    break;
  case Or:
  case And:
    RemoveExpFlag(exp->Left);
    RemoveExpFlag(exp->Right);
    break;
  case Not:
    RemoveExpFlag(exp->Left);
    break;
  case Equals:
  case Less:
  case More:
  case MoreEquals:
  case LessEquals:
    RemoveExpNumeric(exp->IntLeft);
    RemoveExpNumeric(exp->IntRight);
    break;
  }
  free(exp);
}

void RemoveExpWrite(expWrite *exp)
{
  if (NULL == exp)
    return;

  switch (exp->Type)
  {
  case PrintString:
    free(exp->Value);
    break;
  case PrintVariable:
    free(exp->Symbol);
    break;
  }
  free(exp);
}

void RemoveLine(Line *line)
{
  if (NULL == line)
    return;

  switch (line->Type)
  {
  case StringAssignment:
  case StringDeclaration:
    RemoveExpWord(line->StringValue);
    if (NULL != line->Symbol)
      free(line->Symbol);
    break;

  case BoolAssignment:
  case BoolDeclaration:
    RemoveExpFlag(line->FlagVal);
    if (NULL != line->Symbol)
      free(line->Symbol);
    break;

  case IntAssignment:
  case IntDeclaration:
    RemoveExpNumeric(line->NumericVal);
    if (NULL != line->Symbol)
      free(line->Symbol);
    break;

  case Sequence:
    RemoveLine(line->Left);
    RemoveLine(line->Right);
    break;

  case Print:
    RemoveExpWrite(line->WriteText);
    break;
  case Conditional:
    RemoveExpFlag(line->FlagVal);
    RemoveLine(line->Left);
    RemoveLine(line->Right);
    break;
  case While:
    RemoveExpFlag(line->FlagVal);
    RemoveLine(line->Left);
    break;
  }

  free(line);
}
