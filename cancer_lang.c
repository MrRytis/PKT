#include "cancer_lang.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct VariableStruct Variable;

struct VariableStruct
{
  char *Name;
  char *Value;
  VariableType Type;
  Variable *Next;
};

Variable *Memory;

Statement *BuildPrint(char *variable)
{
  Statement *result = (Statement *)malloc(sizeof(Statement));
  if (NULL == result)
    exit(-1);

  result->Type = Print;
  result->Variable = variable;

  return result;
}

Statement *BuildStatementSequence(Statement *first, Statement *second)
{
  Statement *result = (Statement *)malloc(sizeof(Statement));
  if (NULL == result)
    exit(-1);

  result->Type = Sequence;
  result->Left = first;
  result->Right = second;

  return result;
}

Statement *BuildConditional(Statement *ifTrue, Statement *ifFalse, BoolExpression *condition)
{
  Statement *result = (Statement *)malloc(sizeof(Statement));
  if (NULL == result)
    exit(-1);

  result->Type = Conditional;
  result->Left = ifTrue;
  result->Right = ifFalse;
  result->BoolValue = condition;

  return result;
}

Statement *BuildIntAssignment(char *variable, IntExpression *value)
{
  Statement *result = (Statement *)malloc(sizeof(Statement));
  if (NULL == result)
    exit(-1);

  result->Type = IntAssignment;
  result->Variable = variable;
  result->IntValue = value;

  return result;
}

Statement *BuildStringAssignment(char *variable, StringExpression *value)
{
  Statement *result = (Statement *)malloc(sizeof(Statement));
  if (NULL == result)
    exit(-1);

  result->Type = StringAssignment;
  result->Variable = variable;
  result->StringValue = value;

  return result;
}

Statement *BuildBoolAssignment(char *variable, BoolExpression *value)
{
  Statement *result = (Statement *)malloc(sizeof(Statement));
  if (NULL == result)
    exit(-1);

  result->Type = BoolAssignment;
  result->Variable = variable;
  result->BoolValue = value;

  return result;
}

Statement *BuildIntDeclaration(char *variable, IntExpression *value)
{
  Statement *result = (Statement *)malloc(sizeof(Statement));
  if (NULL == result)
    exit(-1);

  result->Type = IntDeclaration;
  result->Variable = variable;
  result->IntValue = value;

  return result;
}

Statement *BuildStringDeclaration(char *variable, StringExpression *value)
{
  Statement *result = (Statement *)malloc(sizeof(Statement));
  if (NULL == result)
    exit(-1);

  result->Type = StringDeclaration;
  result->Variable = variable;
  result->StringValue = value;

  return result;
}

Statement *BuildBoolDeclaration(char *variable, BoolExpression *value)
{
  Statement *result = (Statement *)malloc(sizeof(Statement));
  if (NULL == result)
    exit(-1);

  result->Type = BoolDeclaration;
  result->Variable = variable;
  result->BoolValue = value;

  return result;
}

IntExpression *BuildNumber(int number)
{
  IntExpression *result = (IntExpression *)malloc(sizeof(IntExpression));
  if (NULL == result)
    exit(-1);

  char str[10];
  snprintf(str, 10, "%d", number);

  result->Type = IntLiteral;
  result->Value = strdup(str);

  return result;
}

IntExpression *BuildInfixArithmeticOp(IntExpression *left, IntExpression *right, IntExpressionType type)
{
  IntExpression *result = (IntExpression *)malloc(sizeof(IntExpression));
  if (NULL == result)
    exit(-1);

  result->Type = type;
  result->Left = left;
  result->Right = right;

  return result;
}

IntExpression *BuildSum(IntExpression *left, IntExpression *right)
{
  return BuildInfixArithmeticOp(left, right, Addition);
}

IntExpression *BuildDifference(IntExpression *left, IntExpression *right)
{
  return BuildInfixArithmeticOp(left, right, Subtraction);
}

IntExpression *BuildMultiplication(IntExpression *left, IntExpression *right)
{
  return BuildInfixArithmeticOp(left, right, Multiplication);
}

IntExpression *BuildDivision(IntExpression *left, IntExpression *right)
{
  return BuildInfixArithmeticOp(left, right, Division);
}

StringExpression *BuildString(char *string)
{
  StringExpression *result = (StringExpression *)malloc(sizeof(StringExpression));
  if (NULL == result)
    exit(-1);

  char *p = string;
  p++;
  p[strlen(p) - 1] = 0;

  result->Type = StringLiteral;
  result->Value = p;

  return result;
}

BoolExpression *BuildBool(int bool)
{
  BoolExpression *result = (BoolExpression *)malloc(sizeof(BoolExpression));
  if (NULL == result)
    exit(-1);

  char *value;

  if (bool == 1)
  {
    value = "true";
  }
  else
  {
    value = "false";
  }

  result->Type = BoolLiteral;
  result->Value = value;

  return result;
}

BoolExpression *BuildArithmeticComparison(IntExpression *left, IntExpression *right, BoolExpressionType type)
{
  BoolExpression *result = (BoolExpression *)malloc(sizeof(BoolExpression));
  if (NULL == result)
    exit(-1);

  result->Type = type;
  result->IntLeft = left;
  result->IntRight = right;

  return result;
}

BoolExpression *BuildEquals(IntExpression *left, IntExpression *right)
{
  return BuildArithmeticComparison(left, right, Equals);
}

BoolExpression *BuildLessOrEquals(IntExpression *left, IntExpression *right)
{
  return BuildArithmeticComparison(left, right, LessEquals);
}

BoolExpression *BuildMoreOrEquals(IntExpression *left, IntExpression *right)
{
  return BuildArithmeticComparison(left, right, MoreEquals);
}

BoolExpression *BuildLess(IntExpression *left, IntExpression *right)
{
  return BuildArithmeticComparison(left, right, Less);
}

BoolExpression *BuildMore(IntExpression *left, IntExpression *right)
{
  return BuildArithmeticComparison(left, right, More);
}

BoolExpression *BuildNot(BoolExpression *value)
{
  BoolExpression *result = (BoolExpression *)malloc(sizeof(BoolExpression));
  if (NULL == result)
    exit(-1);

  result->Type = Not;
  result->Left = value;

  return result;
}

BoolExpression *BuildAnd(BoolExpression *left, BoolExpression *right)
{
  BoolExpression *result = (BoolExpression *)malloc(sizeof(BoolExpression));
  if (NULL == result)
    exit(-1);

  result->Type = And;
  result->Left = left;
  result->Right = right;

  return result;
}

BoolExpression *BuildOr(BoolExpression *left, BoolExpression *right)
{
  BoolExpression *result = (BoolExpression *)malloc(sizeof(BoolExpression));
  if (NULL == result)
    exit(-1);

  result->Type = Or;
  result->Left = left;
  result->Right = right;

  return result;
}

IntExpression *BuildIntVariable(char *variable)
{
  IntExpression *result = (IntExpression *)malloc(sizeof(IntExpression));
  if (NULL == result)
    exit(-1);

  result->Variable = variable;
  result->Type = IntVariable;

  return result;
}

StringExpression *BuildStringVariable(char *variable)
{
  StringExpression *result = (StringExpression *)malloc(sizeof(StringExpression));
  if (NULL == result)
    exit(-1);

  result->Variable = variable;
  result->Type = StringVariable;

  return result;
}

BoolExpression *BuildBoolVariable(char *variable)
{
  BoolExpression *result = (BoolExpression *)malloc(sizeof(BoolExpression));
  if (NULL == result)
    exit(-1);

  result->Variable = variable;
  result->Type = BoolVariable;

  return result;
}

void FreeMemory()
{
  Variable *iterator = Memory;
  while (NULL != iterator)
  {
    Variable *temp = iterator;
    iterator = iterator->Next;

    free(temp->Value);
    free(temp);
  }
}

Variable *GetVariable(char *name)
{
  if (NULL == Memory)
    return NULL;

  Variable *result = Memory;
  while (NULL != result->Next)
  {
    if (0 == strcmp(result->Name, name))
      return result;

    result = result->Next;
  }

  if (0 == strcmp(result->Name, name))
    return result;
  return NULL;
}

void SetVariable(char *name, char *value, VariableType type)
{
  if (NULL == Memory)
  {
    printf("Error: variable %s does not exist", name);
    exit(-1);
  }

  Variable *result = Memory;
  while (NULL != result->Next)
  {
    if (0 == strcmp(result->Name, name))
      break;

    result = result->Next;
  }

  if (0 == strcmp(result->Name, name))
  {
    result->Value = value;
    return;
  }
}

Variable *CreateVariable(char *name, char *value, VariableType type)
{
  Variable *result = (Variable *)malloc(sizeof(Variable));
  if (NULL == result)
    exit(-1);

  result->Name = name;
  result->Value = value;
  result->Next = NULL;
  result->Type = type;
}

void CreateNewVariable(char *name, char *value, VariableType type)
{
  if (NULL == Memory)
  {
    Memory = CreateVariable(name, value, type);
  }
  else
  {
    Variable *result = Memory;
    while (NULL != result->Next)
    {
      if (0 == strcmp(result->Name, name))
        break;

      result = result->Next;
    }

    result->Next = CreateVariable(name, value, type);
  }
}

char *EvaluateIntExpression(IntExpression *expression)//čia kažkas rimto vyksta. Tipo visi vieksmai su int ?
{
  if (NULL == expression)
    return NULL;

  char *value;

  char temp[10];
  int left;
  int right;
  Variable *variable;

  switch (expression->Type)
  {
  case IntLiteral:
    value = expression->Value;
    break;
  case IntVariable:
    variable = GetVariable(expression->Variable);
    if (variable == NULL)
    {
      printf("Error: variable %s undeclared\n", expression->Variable);
      exit(-1);
    }
    value = variable->Value;
    break;
  case Multiplication:
    left = atoi(EvaluateIntExpression(expression->Left));
    right = atoi(EvaluateIntExpression(expression->Right));

    snprintf(temp, 10, "%d", left * right);
    value = strdup(temp);
    break;
  case Subtraction:
    left = atoi(EvaluateIntExpression(expression->Left));
    right = atoi(EvaluateIntExpression(expression->Right));

    snprintf(temp, 10, "%d", left - right);
    value = strdup(temp);
    break;
  case Division:
    left = atoi(EvaluateIntExpression(expression->Left));
    right = atoi(EvaluateIntExpression(expression->Right));
    if (right == 0)
    {
      printf("Error: divison by zero\n");
      exit(-1);
    }

    snprintf(temp, 10, "%d", left / right);
    value = strdup(temp);
    break;
  case Addition:
    left = atoi(EvaluateIntExpression(expression->Left));
    right = atoi(EvaluateIntExpression(expression->Right));

    snprintf(temp, 10, "%d", left + right);
    value = strdup(temp);
    break;
  }

  return value;
}

char *EvaluateStringExpression(StringExpression *expression)
{
  if (NULL == expression)
    return NULL;

  char *value;
  Variable *variable;
  switch (expression->Type)
  {
  case StringLiteral:
    value = expression->Value;
    break;
  case StringVariable:
    variable = GetVariable(expression->Variable);
    if (variable == NULL)
    {
      printf("Error: variable %s undeclared\n", expression->Variable);
      exit(-1);
    }
    value = variable->Value;
    break;
  }

  return value;
}

int GetBoolValue(char *value)
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

char *GetBoolValueInt(int value)
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

char *EvaluateBoolExpression(BoolExpression *expression)//cia tipo tas viduj ifo. returnina reiksme true ar false? 570 - 581 čia įrodo kad gražina tik true arba false
{
  if (NULL == expression)
    return NULL;

  char *value;
  int temp;
  Variable *variable;
  switch (expression->Type)
  {
  case BoolLiteral:
    value = expression->Value;
    break;
  case BoolVariable:
    variable = GetVariable(expression->Variable);
    if (variable == NULL)
    {
      printf("Error: variable %s undeclared\n", expression->Variable);
      exit(-1);
    }
    value = variable->Value;
    break;
  case Equals:
    temp = atoi(EvaluateIntExpression(expression->IntLeft)) == atoi(EvaluateIntExpression(expression->IntRight));

    value = GetBoolValueInt(temp);
    break;
  case And:
    temp = GetBoolValue(EvaluateBoolExpression(expression->Left)) && GetBoolValue(EvaluateBoolExpression(expression->Right));

    value = GetBoolValueInt(temp);
    break;
  case Not:
    temp = GetBoolValue(EvaluateBoolExpression(expression->Left));

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
    temp = GetBoolValue(EvaluateBoolExpression(expression->Left)) || GetBoolValue(EvaluateBoolExpression(expression->Right));

    value = GetBoolValueInt(temp);
    break;
  case Less:
    temp = atoi(EvaluateIntExpression(expression->IntLeft)) < atoi(EvaluateIntExpression(expression->IntRight));

    value = GetBoolValueInt(temp);
    break;
  case More:
    temp = atoi(EvaluateIntExpression(expression->IntLeft)) > atoi(EvaluateIntExpression(expression->IntRight));

    value = GetBoolValueInt(temp);
    break;
  case MoreEquals:
    temp = atoi(EvaluateIntExpression(expression->IntLeft)) >= atoi(EvaluateIntExpression(expression->IntRight));

    value = GetBoolValueInt(temp);
    break;
  case LessEquals:
    temp = atoi(EvaluateIntExpression(expression->IntLeft)) <= atoi(EvaluateIntExpression(expression->IntRight));

    value = GetBoolValueInt(temp);
    break;
  }

  return value;
}

void EvaluateStatement(Statement *statement)//tikrina kas per statement ir žiūri ką daryt kur siust toliau vykdyt
{
  if (NULL == statement)
    return;

  char *value;
  Variable *exValue;
  switch (statement->Type)
  {
  case BoolDeclaration:
    value = EvaluateBoolExpression(statement->BoolValue);
    exValue = GetVariable(statement->Variable);
    if (exValue == NULL)
    {
      CreateNewVariable(statement->Variable, value, BOOL);
      break;
    }
    printf("Error: variable %s already declared\n", statement->Variable);
    exit(-1);
    break;

  case IntDeclaration:
    value = EvaluateIntExpression(statement->IntValue);
    exValue = GetVariable(statement->Variable);
    if (exValue == NULL)
    {
      CreateNewVariable(statement->Variable, value, INT);
      break;
    }
    printf("Error: variable %s already declared\n", statement->Variable);
    exit(-1);
    break;

  case StringDeclaration:
    value = EvaluateStringExpression(statement->StringValue);
    exValue = GetVariable(statement->Variable);
    if (exValue == NULL)
    {
      CreateNewVariable(statement->Variable, value, STRING);
      break;
    }
    printf("Error: variable %s already declared\n", statement->Variable);
    exit(-1);
    break;

  case BoolAssignment:
    value = EvaluateBoolExpression(statement->BoolValue);
    exValue = GetVariable(statement->Variable);
    if (exValue == NULL)
    {
      printf("Error: variable %s undeclared\n", statement->Variable);
      exit(-1);
    }
    SetVariable(statement->Variable, value, BOOL);
    break;

  case IntAssignment:
    value = EvaluateIntExpression(statement->IntValue);
    exValue = GetVariable(statement->Variable);
    if (exValue == NULL)
    {
      printf("Error: variable %s undeclared\n", statement->Variable);
      exit(-1);
    }
    SetVariable(statement->Variable, value, INT);
    break;

  case StringAssignment:
    value = EvaluateStringExpression(statement->StringValue);
    exValue = GetVariable(statement->Variable);
    if (exValue == NULL)
    {
      printf("Error: variable %s undeclared\n", statement->Variable);
      exit(-1);
    }
    SetVariable(statement->Variable, value, INT);
    break;
  case Print:
    exValue = GetVariable(statement->Variable);
    if (exValue == NULL)
    {
      printf("Error: variable %s undeclared\n", statement->Variable);
      exit(-1);
    }

    printf("%s\n", exValue->Value);
    break;
  case Sequence:
    EvaluateStatement(statement->Left);
    EvaluateStatement(statement->Right);
    break;
  case Conditional:
    value = EvaluateBoolExpression(statement->BoolValue);
    if (GetBoolValue(value) == 1)
    {
      EvaluateStatement(statement->Left);
    }
    else
    {
      EvaluateStatement(statement->Right);
    }
    break;
  }
}

void DeleteIntExpression(IntExpression *expression)//atlaisvina atminti?
{
  if (NULL == expression)
    return;

  switch (expression->Type)
  {
  case IntLiteral:
    free(expression->Value);
    break;
  case IntVariable:
    free(expression->Variable);
    break;
  case Subtraction:
    DeleteIntExpression(expression->Left);
    DeleteIntExpression(expression->Right);
    break;
  case Division:
    DeleteIntExpression(expression->Left);
    DeleteIntExpression(expression->Right);
    break;
  case Addition:
    DeleteIntExpression(expression->Left);
    DeleteIntExpression(expression->Right);
    break;
  case Multiplication:
    DeleteIntExpression(expression->Left);
    DeleteIntExpression(expression->Right);
    break;
  }
  free(expression);
}

void DeleteStringExpression(StringExpression *expression)
{
  if (NULL == expression)
    return;

  switch (expression->Type)
  {
  case StringLiteral:
    free(expression->Value);
    break;
  case StringVariable:
    free(expression->Variable);
    break;
  }
  free(expression);
}

void DeleteBoolExpression(BoolExpression *expression)
{
  if (NULL == expression)
    return;

  switch (expression->Type)
  {
  case BoolLiteral:
    free(expression->Value);
    break;
  case BoolVariable:
    free(expression->Variable);
    break;
  case Or:
  case And:
    DeleteBoolExpression(expression->Left);
    DeleteBoolExpression(expression->Right);
    break;
  case Not:
    DeleteBoolExpression(expression->Left);
    break;
  case Equals:
  case Less:
  case More:
  case MoreEquals:
  case LessEquals:
    DeleteIntExpression(expression->IntLeft);
    DeleteIntExpression(expression->IntRight);
    break;
  }
  free(expression);
}

void DeleteStatement(Statement *statement)
{
  if (NULL == statement)
    return;

  switch (statement->Type)
  {
  case StringAssignment:
  case StringDeclaration:
    DeleteStringExpression(statement->StringValue);
    if (NULL != statement->Variable)
      free(statement->Variable);
    break;

  case BoolAssignment:
  case BoolDeclaration:
    DeleteBoolExpression(statement->BoolValue);
    if (NULL != statement->Variable)
      free(statement->Variable);
    break;

  case IntAssignment:
  case IntDeclaration:
    DeleteIntExpression(statement->IntValue);
    if (NULL != statement->Variable)
      free(statement->Variable);
    break;

  case Sequence:
    DeleteStatement(statement->Left);
    DeleteStatement(statement->Right);
    break;

  case Print:
    free(statement->Variable);
    break;
  }

  free(statement);
}
