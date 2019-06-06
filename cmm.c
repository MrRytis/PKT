#include "cmm.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct SymbolStructure Symbol;
struct SymbolStructure
{
  char *Name;
  char *Worth;
  SymbolicTp kind;
  Symbol *Upcoming;
  char *Range;
};

char *crntRange = "global";
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
    free(temp->Worth);
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

  endpoint->kind = Print;
  endpoint->WriteText = symbol;

  return endpoint;
}

Line *LineChainGenerate(Line *primary, Line *secondary)
{
  Line *endpoint = (Line *)malloc(sizeof(Line));
  if (NULL == endpoint)
    exit(-1);

  endpoint->kind = Chain;
  endpoint->Left = primary;
  endpoint->Right = secondary;

  return endpoint;
}

Line *GeneratePositiveNegative(Line *positive, Line *negative, expFlag *decider)
{
  Line *endpoint = (Line *)malloc(sizeof(Line));
  if (NULL == endpoint)
    exit(-1);

  endpoint->kind = Restrictive;
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

  endpoint->kind = Loop;
  endpoint->Left = content;
  endpoint->FlagVal = decider;

  return endpoint;
}

Line *GenerateNumericDefinition(char *symbol, expNumber *data)
{
  Line *endpoint = (Line *)malloc(sizeof(Line));
  if (NULL == endpoint)
    exit(-1);

  endpoint->kind = NumericDefinition;
  endpoint->Symbol = symbol;
  endpoint->NumericVal = data;

  return endpoint;
}

Line *GenerateWordDefinition(char *symbol, expWord *data)
{
  Line *endpoint = (Line *)malloc(sizeof(Line));
  if (NULL == endpoint)
    exit(-1);

  endpoint->kind = WordDefinition;
  endpoint->Symbol = symbol;
  endpoint->WordWorth = data;

  return endpoint;
}

Line *GenerateFlagDefinition(char *symbol, expFlag *data)
{
  Line *endpoint = (Line *)malloc(sizeof(Line));
  if (NULL == endpoint)
    exit(-1);

  endpoint->kind = FlagDefinition;
  endpoint->Symbol = symbol;
  endpoint->FlagVal = data;

  return endpoint;
}

Line *GenerateNumericCreation(char *symbol, expNumber *data)
{
  Line *endpoint = (Line *)malloc(sizeof(Line));
  if (NULL == endpoint)
    exit(-1);

  endpoint->kind = CreateNumeric;
  endpoint->Symbol = symbol;
  endpoint->NumericVal = data;

  return endpoint;
}

Line *GenerateWordCreation(char *symbol, expWord *data)
{
  Line *endpoint = (Line *)malloc(sizeof(Line));
  if (NULL == endpoint)
    exit(-1);

  endpoint->kind = CreateWord;
  endpoint->Symbol = symbol;
  endpoint->WordWorth = data;

  return endpoint;
}

Line *GenerateFlagCreation(char *symbol, expFlag *data)
{
  Line *endpoint = (Line *)malloc(sizeof(Line));
  if (NULL == endpoint)
    exit(-1);

  endpoint->kind = CreateFlag;
  endpoint->Symbol = symbol;
  endpoint->FlagVal = data;

  return endpoint;
}

Characteristic *GenerateCharacteristic(char *title, SymbolicTp kind)
{
  Characteristic *endpoint = (Characteristic *)malloc(sizeof(Characteristic));
  if (NULL == endpoint)
    exit(-1);

  endpoint->kind = kind;
  endpoint->Name = title;
  endpoint->Upcoming = NULL;

  return endpoint;
}

Characteristic *GenerateNumericExpCharacteritic(expNumber *exp)
{
  Characteristic *endpoint = (Characteristic *)malloc(sizeof(Characteristic));
  if (NULL == endpoint)
    exit(-1);

  endpoint->kind = numeric;
  endpoint->inte = exp;
  endpoint->Upcoming = NULL;

  return endpoint;
}

Characteristic *GenerateWordExpCharacteritic(expWord *exp)
{
  Characteristic *endpoint = (Characteristic *)malloc(sizeof(Characteristic));
  if (NULL == endpoint)
    exit(-1);

  endpoint->kind = word;
  endpoint->stringe = exp;
  endpoint->Upcoming = NULL;

  return endpoint;
}

Characteristic *GenerateFlagExpCharacteritic(expFlag *exp)
{
  Characteristic *endpoint = (Characteristic *)malloc(sizeof(Characteristic));
  if (NULL == endpoint)
    exit(-1);

  endpoint->kind = flag;
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
  endpoint->kind = MagicDefinition;
  endpoint->Left = content;
  endpoint->Characteristics = characteristics;

  return endpoint;
}

Line *GenerateMagicShout(char *magic_name, Characteristic *worths)
{
  Line *endpoint = (Line *)malloc(sizeof(Line));
  if (NULL == endpoint)
    exit(-1);

  endpoint->Symbol = magic_name;
  endpoint->kind = MagicShout;
  endpoint->Characteristics = worths;

  return endpoint;
}

expNumber *GenerateNumeric(int number)
{
  expNumber *endpoint = (expNumber *)malloc(sizeof(expNumber));
  if (NULL == endpoint)
    exit(-1);

  char wrd[10];
  snprintf(wrd, 10, "%d", number);

  endpoint->kind = numericData;
  endpoint->Worth = strdup(wrd);

  return endpoint;
}

expNumber *GenerateNumericUniversal(expNumber *left, expNumber *right, expNumericTp kind)
{
  expNumber *endpoint = (expNumber *)malloc(sizeof(expNumber));
  if (NULL == endpoint)
    exit(-1);

  endpoint->kind = kind;
  endpoint->Left = left;
  endpoint->Right = right;

  return endpoint;
}

expNumber *GenerateAddition(expNumber *left, expNumber *right)
{
  return GenerateNumericUniversal(left, right, Plus);
}

expNumber *GenerateSubtraction(expNumber *left, expNumber *right)
{
  return GenerateNumericUniversal(left, right, Minus);
}

expNumber *GenerateMulExpression(expNumber *left, expNumber *right)
{
  return GenerateNumericUniversal(left, right, MathMul);
}

expNumber *GenerateDivExpression(expNumber *left, expNumber *right)
{
  return GenerateNumericUniversal(left, right, MathSplitEvenGroup);
}

expWord *GenerateWord(char *xword)
{
  expWord *endpoint = (expWord *)malloc(sizeof(expWord));
  if (NULL == endpoint)
    exit(-1);

  char *p = xword;
  p++;
  p[strlen(p) - 1] = 0;

  endpoint->kind = wordValue;
  endpoint->Worth = p;

  return endpoint;
}

expFlag *GenerateFlag(int flag)
{
  expFlag *endpoint = (expFlag *)malloc(sizeof(expFlag));
  if (NULL == endpoint)
    exit(-1);

  char *data;

  if (flag == 1)
  {
    data = "true";
  }
  else
  {
    data = "false";
  }

  endpoint->kind = flagData;
  endpoint->Worth = data;

  return endpoint;
}

expFlag *GenerateNumericCmpUniversal(expNumber *left, expNumber *right, expFlagTp kind)
{
  expFlag *endpoint = (expFlag *)malloc(sizeof(expFlag));
  if (NULL == endpoint)
    exit(-1);

  endpoint->kind = kind;
  endpoint->numericLeft = left;
  endpoint->numericRight = right;

  return endpoint;
}

expFlag *GenerateNumericEven(expNumber *left, expNumber *right)
{
  return GenerateNumericCmpUniversal(left, right, Even);
}

expFlag *GenerateNumericEvenLess(expNumber *left, expNumber *right)
{
  return GenerateNumericCmpUniversal(left, right, EvenOrFewer);
}

expFlag *GenerateNumericEvenGreater(expNumber *left, expNumber *right)
{
  return GenerateNumericCmpUniversal(left, right, GreaterOrEven);
}

expFlag *GenerateNumericLower(expNumber *left, expNumber *right)
{
  return GenerateNumericCmpUniversal(left, right, Fewer);
}

expFlag *GenerateNumericGreater(expNumber *left, expNumber *right)
{
  return GenerateNumericCmpUniversal(left, right, Greater);
}

expFlag *GenerateNumericInvariant(expFlag *data)
{
  expFlag *endpoint = (expFlag *)malloc(sizeof(expFlag));
  if (NULL == endpoint)
    exit(-1);

  endpoint->kind = Opposite ;
  endpoint->Left = data;

  return endpoint;
}

expFlag *GenerateNumericWith(expFlag *left, expFlag *right)
{
  expFlag *endpoint = (expFlag *)malloc(sizeof(expFlag));
  if (NULL == endpoint)
    exit(-1);

  endpoint->kind = Also;
  endpoint->Left = left;
  endpoint->Right = right;

  return endpoint;
}

expFlag *GenerateNumericEither(expFlag *left, expFlag *right)
{
  expFlag *endpoint = (expFlag *)malloc(sizeof(expFlag));
  if (NULL == endpoint)
    exit(-1);

  endpoint->kind = Either;
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
  endpoint->kind = numericSymbol;

  return endpoint;
}

expWord *GenerateWordSymbol(char *symbol)
{
  expWord *endpoint = (expWord *)malloc(sizeof(expWord));
  if (NULL == endpoint)
    exit(-1);

  endpoint->Symbol = symbol;
  endpoint->kind = wordSymbol;

  return endpoint;
}

expFlag *GenerateFlagSymbol(char *symbol)
{
  expFlag *endpoint = (expFlag *)malloc(sizeof(expFlag));
  if (NULL == endpoint)
    exit(-1);

  endpoint->Symbol = symbol;
  endpoint->kind = flagSymbol;

  return endpoint;
}

expWrite *GenerateWriteWord(char *data)
{
  expWrite *endpoint = (expWrite *)malloc(sizeof(expWrite));
  if (NULL == endpoint)
    exit(-1);

  endpoint->Worth = data;
  endpoint->kind = WriteText;

  return endpoint;
}

expWrite *GenerateWriteSymbol(char *symbol)
{
  expWrite *endpoint = (expWrite *)malloc(sizeof(expWrite));
  if (NULL == endpoint)
    exit(-1);

  endpoint->Symbol = symbol;
  endpoint->kind = WriteSymbol;

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
    if (0 == strcmp(endpoint->Name, title) && 0 == strcmp(endpoint->Range, crntRange))
      return endpoint;

    endpoint = endpoint->Upcoming;
  }

  if (0 == strcmp(endpoint->Name, title) && 0 == strcmp(endpoint->Range, crntRange))
    return endpoint;
  return NULL;
}

void InsertSymbol(char *title, char *data, SymbolicTp kind)
{
  if (NULL == RAM)
  {
    printf("Error: symbol %s does not exist", title);
    exit(-1);
  }

  Symbol *endpoint = RAM;
  while (NULL != endpoint->Upcoming)
  {
    if (0 == strcmp(endpoint->Name, title) && 0 == strcmp(endpoint->Range, crntRange))
      break;

    endpoint = endpoint->Upcoming;
  }

  if (0 == strcmp(endpoint->Name, title) && 0 == strcmp(endpoint->Range, crntRange))
  {
    endpoint->Worth = data;
    return;
  }
}

Symbol *GenerateSymbol(char *title, char *data, SymbolicTp kind)
{
  Symbol *endpoint = (Symbol *)malloc(sizeof(Symbol));
  if (NULL == endpoint)
    exit(-1);

  endpoint->Name = title;
  endpoint->Worth = data;
  endpoint->Upcoming = NULL;
  endpoint->kind = kind;
  endpoint->Range = crntRange;
}

void GenerateNewSymbol(char *title, char *data, SymbolicTp kind)
{
  if (NULL == RAM)
  {
    RAM = GenerateSymbol(title, data, kind);
  }
  else
  {
    Symbol *endpoint = RAM;
    while (NULL != endpoint->Upcoming)
    {
      if (0 == strcmp(endpoint->Name, title) && 0 == strcmp(endpoint->Range, crntRange))
        break;

      endpoint = endpoint->Upcoming;
    }

    endpoint->Upcoming = GenerateSymbol(title, data, kind);
  }
}

char *ProcessExpNumeric(expNumber *exp)
{
  if (NULL == exp)
    return NULL;

  char *data;

  char temp[10];
  int left;
  int right;
  Symbol *symbol;

  switch (exp->kind)
  {
  case numericData:
    data = exp->Worth;
    break;
  case numericSymbol:
    symbol = ReceiveSymbol(exp->Symbol);
    if (symbol == NULL)
    {
      printf("Error: symbol %s undeclared\n", exp->Symbol);
      exit(-1);
    }
    data = symbol->Worth;
    break;
  case MathMul:
    left = atoi(ProcessExpNumeric(exp->Left));
    right = atoi(ProcessExpNumeric(exp->Right));

    snprintf(temp, 10, "%d", left * right);
    data = strdup(temp);
    break;
  case Minus:
    left = atoi(ProcessExpNumeric(exp->Left));
    right = atoi(ProcessExpNumeric(exp->Right));

    snprintf(temp, 10, "%d", left - right);
    data = strdup(temp);
    break;
  case MathSplitEvenGroup:
    left = atoi(ProcessExpNumeric(exp->Left));
    right = atoi(ProcessExpNumeric(exp->Right));
    if (right == 0)
    {
      printf("Error: divison by zero\n");
      exit(-1);
    }

    snprintf(temp, 10, "%d", left / right);
    data = strdup(temp);
    break;
  case Plus:
    left = atoi(ProcessExpNumeric(exp->Left));
    right = atoi(ProcessExpNumeric(exp->Right));

    snprintf(temp, 10, "%d", left + right);
    data = strdup(temp);
    break;
  }

  return data;
}

char *ProcessExpWord(expWord *exp)
{
  if (NULL == exp)
    return NULL;

  char *data;
  Symbol *symbol;
  switch (exp->kind)
  {
  case wordValue:
    data = exp->Worth;
    break;
  case wordSymbol:
    symbol = ReceiveSymbol(exp->Symbol);
    if (symbol == NULL)
    {
      printf("Error: symbol %s undeclared\n", exp->Symbol);
      exit(-1);
    }
    data = symbol->Worth;
    break;
  }

  return data;
}

void ProcessExpWrite(expWrite *exp)
{
  if (NULL == exp)
    return;

  Symbol *symbol;
  char *p;
  switch (exp->kind)
  {
  case WriteText:
    p = exp->Worth;
    p++;
    p[strlen(p) - 1] = 0;

    printf("%s\n", p);
    break;
  case WriteSymbol:
    symbol = ReceiveSymbol(exp->Symbol);
    if (symbol == NULL)
    {
      printf("Error: symbol %s undeclared\n", exp->Symbol);
      exit(-1);
    }

    printf("%s\n", symbol->Worth);
    break;
  }
}

int ReceiveFlagVal(char *data)
{
  if (data == "true")
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

char *ReceiveNumericFlagVal(int data)
{
  if (data == 1)
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

  char *data;
  int temp;
  Symbol *symbol;
  switch (exp->kind)
  {
  case flagData:
    data = exp->Worth;
    break;
  case flagSymbol:
    symbol = ReceiveSymbol(exp->Symbol);
    if (symbol == NULL)
    {
      printf("Error: symbol %s undeclared\n", exp->Symbol);
      exit(-1);
    }
    data = symbol->Worth;
    break;
  case Even:
    temp = atoi(ProcessExpNumeric(exp->numericLeft)) == atoi(ProcessExpNumeric(exp->numericRight));

    data = ReceiveNumericFlagVal(temp);
    break;
  case Also:
    temp = ReceiveFlagVal(ProcessExpFlag(exp->Left)) && ReceiveFlagVal(ProcessExpFlag(exp->Right));

    data = ReceiveNumericFlagVal(temp);
    break;
  case Opposite :
    temp = ReceiveFlagVal(ProcessExpFlag(exp->Left));

    if (temp == 1)
    {
      data = "false";
    }
    else
    {
      data = "true";
    }
    break;
  case Either:
    temp = ReceiveFlagVal(ProcessExpFlag(exp->Left)) || ReceiveFlagVal(ProcessExpFlag(exp->Right));

    data = ReceiveNumericFlagVal(temp);
    break;
  case Fewer:
    temp = atoi(ProcessExpNumeric(exp->numericLeft)) < atoi(ProcessExpNumeric(exp->numericRight));

    data = ReceiveNumericFlagVal(temp);
    break;
  case Greater:
    temp = atoi(ProcessExpNumeric(exp->numericLeft)) > atoi(ProcessExpNumeric(exp->numericRight));

    data = ReceiveNumericFlagVal(temp);
    break;
  case GreaterOrEven:
    temp = atoi(ProcessExpNumeric(exp->numericLeft)) >= atoi(ProcessExpNumeric(exp->numericRight));

    data = ReceiveNumericFlagVal(temp);
    break;
  case EvenOrFewer:
    temp = atoi(ProcessExpNumeric(exp->numericLeft)) <= atoi(ProcessExpNumeric(exp->numericRight));

    data = ReceiveNumericFlagVal(temp);
    break;
  }

  return data;
}

void ProcessMagicShout(Magic *magic, Line *function_call)
{
  Characteristic *param = magic->Characteristics;
  Characteristic *data = function_call->Characteristics;
  char *valuestr;
  while (NULL != param)
  {
    if (param->kind != data->kind)
    {
      printf("Error: magic param kind is not accepted\n");
      exit(-1);
    }

    if (data->kind == 0)
    {
      valuestr = ProcessExpNumeric(data->inte);
    }
    else if (data->kind == 1)
    {
      valuestr = ProcessExpWord(data->stringe);
    }
    else if (data->kind == 2)
    {
      valuestr = ProcessExpFlag(data->boole);
    }

    crntRange = magic->MagicName;
    param->Worth = valuestr;
    Symbol *var = ReceiveSymbol(param->Name);
    if (var == NULL)
    {
      GenerateNewSymbol(param->Name, valuestr, param->kind);
    }
    else
    {
      InsertSymbol(param->Name, valuestr, param->kind);
    }

    crntRange = "global";

    data = data->Upcoming;
    param = param->Upcoming;
  }

  crntRange = magic->MagicName;
  ProcessLine(magic->Content);
  crntRange = "global";
}

void ProcessLine(Line *line)
{
  if (NULL == line)
    return;

  char *data;
  Symbol *exValue;
  Magic *magic;
  switch (line->kind)
  {
  case CreateFlag:
    data = ProcessExpFlag(line->FlagVal);
    exValue = ReceiveSymbol(line->Symbol);
    if (exValue == NULL)
    {
      GenerateNewSymbol(line->Symbol, data, flag);
      break;
    }
    printf("Error: symbol %s already declared\n", line->Symbol);
    exit(-1);
    break;

  case CreateNumeric:
    data = ProcessExpNumeric(line->NumericVal);
    exValue = ReceiveSymbol(line->Symbol);
    if (exValue == NULL)
    {
      GenerateNewSymbol(line->Symbol, data, numeric);
      break;
    }
    printf("Error: symbol %s already declared\n", line->Symbol);
    exit(-1);
    break;

  case CreateWord:
    data = ProcessExpWord(line->WordWorth);
    exValue = ReceiveSymbol(line->Symbol);
    if (exValue == NULL)
    {
      GenerateNewSymbol(line->Symbol, data, word);
      break;
    }
    printf("Error: symbol %s already declared\n", line->Symbol);
    exit(-1);
    break;

  case FlagDefinition:
    data = ProcessExpFlag(line->FlagVal);
    exValue = ReceiveSymbol(line->Symbol);
    if (exValue == NULL)
    {
      printf("Error: symbol %s undeclared\n", line->Symbol);
      exit(-1);
    }
    InsertSymbol(line->Symbol, data, flag);
    break;

  case NumericDefinition:
    data = ProcessExpNumeric(line->NumericVal);
    exValue = ReceiveSymbol(line->Symbol);
    if (exValue == NULL)
    {
      printf("Error: symbol %s undeclared\n", line->Symbol);
      exit(-1);
    }
    InsertSymbol(line->Symbol, data, numeric);
    break;

  case WordDefinition:
    data = ProcessExpWord(line->WordWorth);
    exValue = ReceiveSymbol(line->Symbol);
    if (exValue == NULL)
    {
      printf("Error: symbol %s undeclared\n", line->Symbol);
      exit(-1);
    }
    InsertSymbol(line->Symbol, data, numeric);
    break;
  case Print:
    ProcessExpWrite(line->WriteText);
    break;
  case Chain:
    ProcessLine(line->Left);
    ProcessLine(line->Right);
    break;
  case Restrictive:
    data = ProcessExpFlag(line->FlagVal);
    if (ReceiveFlagVal(data) == 1)
    {
      ProcessLine(line->Left);
    }
    else
    {
      ProcessLine(line->Right);
    }
    break;
  case Loop:
    data = ProcessExpFlag(line->FlagVal);
    while (ReceiveFlagVal(data) == 1)
    {
      ProcessLine(line->Left);
      data = ProcessExpFlag(line->FlagVal);
    }
    break;
  case MagicDefinition:
    if (crntRange != "global")
    {
      printf("Error: declaring functions inside functions is not allowed\n");
      exit(-1);
    }

    magic = ReceiveMagic(line->Symbol);
    if (magic != NULL)
    {
      printf("Error: magic %s is already declared\n", line->Symbol);
      exit(-1);
    }

    GenerateNewMagic(line->Symbol, line->Characteristics, line->Left);
    break;
  case MagicShout:
    magic = ReceiveMagic(line->Symbol);
    if (magic == NULL)
    {
      printf("Error: magic %s is undeclared\n", line->Symbol);
      exit(-1);
    }

    ProcessMagicShout(magic, line);
    break;
  }
}

void RemoveExpNumeric(expNumber *exp)
{
  if (NULL == exp)
    return;

  switch (exp->kind)
  {
  case numericData:
    free(exp->Worth);
    break;
  case numericSymbol:
    free(exp->Symbol);
    break;
  case Minus:
    RemoveExpNumeric(exp->Left);
    RemoveExpNumeric(exp->Right);
    break;
  case MathSplitEvenGroup:
    RemoveExpNumeric(exp->Left);
    RemoveExpNumeric(exp->Right);
    break;
  case Plus:
    RemoveExpNumeric(exp->Left);
    RemoveExpNumeric(exp->Right);
    break;
  case MathMul:
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

  switch (exp->kind)
  {
  case wordValue:
    free(exp->Worth);
    break;
  case wordSymbol:
    free(exp->Symbol);
    break;
  }
  free(exp);
}

void RemoveExpFlag(expFlag *exp)
{
  if (NULL == exp)
    return;

  switch (exp->kind)
  {
  case flagData:
    free(exp->Worth);
    break;
  case flagSymbol:
    free(exp->Symbol);
    break;
  case Either:
  case Also:
    RemoveExpFlag(exp->Left);
    RemoveExpFlag(exp->Right);
    break;
  case Opposite :
    RemoveExpFlag(exp->Left);
    break;
  case Even:
  case Fewer:
  case Greater:
  case GreaterOrEven:
  case EvenOrFewer:
    RemoveExpNumeric(exp->numericLeft);
    RemoveExpNumeric(exp->numericRight);
    break;
  }
  free(exp);
}

void RemoveExpWrite(expWrite *exp)
{
  if (NULL == exp)
    return;

  switch (exp->kind)
  {
  case WriteText:
    free(exp->Worth);
    break;
  case WriteSymbol:
    free(exp->Symbol);
    break;
  }
  free(exp);
}

void RemoveLine(Line *line)
{
  if (NULL == line)
    return;

  switch (line->kind)
  {
  case WordDefinition:
  case CreateWord:
    RemoveExpWord(line->WordWorth);
    if (NULL != line->Symbol)
      free(line->Symbol);
    break;

  case FlagDefinition:
  case CreateFlag:
    RemoveExpFlag(line->FlagVal);
    if (NULL != line->Symbol)
      free(line->Symbol);
    break;

  case NumericDefinition:
  case CreateNumeric:
    RemoveExpNumeric(line->NumericVal);
    if (NULL != line->Symbol)
      free(line->Symbol);
    break;

  case Chain:
    RemoveLine(line->Left);
    RemoveLine(line->Right);
    break;

  case Print:
    RemoveExpWrite(line->WriteText);
    break;
  case Restrictive:
    RemoveExpFlag(line->FlagVal);
    RemoveLine(line->Left);
    RemoveLine(line->Right);
    break;
  case Loop:
    RemoveExpFlag(line->FlagVal);
    RemoveLine(line->Left);
    break;
  }
  free(line);
}

  void GenerateMagicCat(expWord *params)
  {
      char *joinedString = malloc(100);
      char *pt;
      pt = strtok (params->Worth,",");
      while (pt != NULL)
      {
        strcat(joinedString, pt);
        pt = strtok (NULL, ",");
      }

      printf("Joined string:");
      printf(joinedString);
      printf("\n");
  }

  void GenerateMagicCat2(expWord *params, expWord *params2)
  {
      char *joinedString = malloc(100);
      char *pt;
      pt = strtok (params->Worth,",");
      while (pt != NULL)
      {
        strcat(joinedString, pt);
        pt = strtok (NULL, ",");
      }

      pt = strtok (params2->Worth,",");
      while (pt != NULL)
      {
        strcat(joinedString, pt);
        pt = strtok (NULL, ",");
      }

      printf("Joined string:");
      printf(joinedString);
      printf("\n");
  }

  void GenerateMagicCat3(expWord *params, expWord *params2, expWord *params3)
  {
      char *joinedString = malloc(100);
      char *pt;
      pt = strtok (params->Worth,",");
      while (pt != NULL)
      {
        strcat(joinedString, pt);
        pt = strtok (NULL, ",");
      }

      pt = strtok (params2->Worth,",");
      while (pt != NULL)
      {
        strcat(joinedString, pt);
        pt = strtok (NULL, ",");
      }

      pt = strtok (params3->Worth,",");
      while (pt != NULL)
      {
        strcat(joinedString, pt);
        pt = strtok (NULL, ",");
      }

      printf("Joined string:");
      printf(joinedString);
      printf("\n");
    
  }

  void GenerateMagicCat4(expWord *params,expWord *params2,expWord *params3,expWord *params4)
  {
      char *joinedString = malloc(100);
      char *pt;
      pt = strtok (params->Worth,",");
      while (pt != NULL)
      {
        strcat(joinedString, pt);
        pt = strtok (NULL, ",");
      }

      pt = strtok (params2->Worth,",");
      while (pt != NULL)
      {
        strcat(joinedString, pt);
        pt = strtok (NULL, ",");
      }

      pt = strtok (params3->Worth,",");
      while (pt != NULL)
      {
        strcat(joinedString, pt);
        pt = strtok (NULL, ",");
      }

      pt = strtok (params4->Worth,",");
      while (pt != NULL)
      {
        strcat(joinedString, pt);
        pt = strtok (NULL, ",");
      }

      printf("Joined string:");
      printf(joinedString);
      printf("\n");
  }