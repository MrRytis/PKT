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
  char *Scope;
};

char *currentScope = "global";
Variable *Memory;
Function *FuncMemory;

Function *GetFunction(char *function_name)
{
  if (NULL == FuncMemory)
    return NULL;

  Function *result = FuncMemory;
  while (NULL != result->Next)
  {
    if (0 == strcmp(result->FunctionName, function_name))
      return result;

    result = result->Next;
  }

  if (0 == strcmp(result->FunctionName, function_name))
    return result;
  return NULL;
}

void DeleteParameter(Parameter *parameter)
{
  Parameter *iterator = parameter;
  while (NULL != iterator)
  {
    Parameter *temp = iterator;
    iterator = iterator->Next;

    free(temp->Name);
    free(temp->Value);
    free(temp);
  }
}

void FreeFunctionMemory()
{
  Function *iterator = FuncMemory;
  while (NULL != iterator)
  {
    Function *temp = iterator;
    iterator = iterator->Next;

    free(temp);
  }
}

Function *CreateFunction(char *name, Parameter *params, Statement *body)
{
  Function *result = (Function *)malloc(sizeof(Function));
  if (NULL == result)
    exit(-1);

  result->FunctionName = name;
  result->Next = NULL;
  result->Body = body;
  result->Params = params;
}

void CreateNewFunction(char *name, Parameter *params, Statement *body)
{
  if (NULL == FuncMemory)
  {
    FuncMemory = CreateFunction(name, params, body);
  }
  else
  {
    Function *result = FuncMemory;
    while (NULL != result->Next)
    {
      if (0 == strcmp(result->FunctionName, name))
        break;

      result = result->Next;
    }

    result->Next = CreateFunction(name, params, body);
  }
}

Statement *BuildPrint(PrintExpression *variable)
{
  Statement *result = (Statement *)malloc(sizeof(Statement));
  if (NULL == result)
    exit(-1);

  result->Type = Print;
  result->PrintValue = variable;

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

Statement *BuildWhile(BoolExpression *condition, Statement *body)
{
  Statement *result = (Statement *)malloc(sizeof(Statement));
  if (NULL == result)
    exit(-1);

  result->Type = While;
  result->Left = body;
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

Parameter *BuildParam(char *name, VariableType type)
{
  Parameter *result = (Parameter *)malloc(sizeof(Parameter));
  if (NULL == result)
    exit(-1);

  result->Type = type;
  result->Name = name;
  result->Next = NULL;

  return result;
}

Parameter *BuildIntValueParam(IntExpression *expression)
{
  Parameter *result = (Parameter *)malloc(sizeof(Parameter));
  if (NULL == result)
    exit(-1);

  result->Type = INT;
  result->inte = expression;
  result->Next = NULL;

  return result;
}

Parameter *BuildStringValueParam(StringExpression *expression)
{
  Parameter *result = (Parameter *)malloc(sizeof(Parameter));
  if (NULL == result)
    exit(-1);

  result->Type = STRING;
  result->stringe = expression;
  result->Next = NULL;

  return result;
}

Parameter *BuildBoolValueParam(BoolExpression *expression)
{
  Parameter *result = (Parameter *)malloc(sizeof(Parameter));
  if (NULL == result)
    exit(-1);

  result->Type = BOOL;
  result->boole = expression;
  result->Next = NULL;

  return result;
}

Parameter *BuildParameterList(Parameter *first, Parameter *second)
{
  if (NULL == first || NULL == second)
    exit(-1);

  first->Next = second;
  return first;
}

Statement *BuildFunction(char *function_name, Parameter *params, Statement *body)
{
  Statement *result = (Statement *)malloc(sizeof(Statement));
  if (NULL == result)
    exit(-1);

  result->Variable = function_name;
  result->Type = FunctionDeclaration;
  result->Left = body;
  result->Params = params;

  return result;
}

Statement *BuildFunctionCall(char *function_name, Parameter *values)
{
  Statement *result = (Statement *)malloc(sizeof(Statement));
  if (NULL == result)
    exit(-1);

  result->Variable = function_name;
  result->Type = FunctionCall;
  result->Params = values;

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

PrintExpression *BuildPrintString(char *value)
{
  PrintExpression *result = (PrintExpression *)malloc(sizeof(PrintExpression));
  if (NULL == result)
    exit(-1);

  result->Value = value;
  result->Type = PrintString;

  return result;
}

PrintExpression *BuildPrintVariable(char *variable)
{
  PrintExpression *result = (PrintExpression *)malloc(sizeof(PrintExpression));
  if (NULL == result)
    exit(-1);

  result->Variable = variable;
  result->Type = PrintVariable;

  return result;
}

void FreeMemory()
{
  Variable *iterator = Memory;
  while (NULL != iterator)
  {
    Variable *temp = iterator;
    iterator = iterator->Next;

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
    if (0 == strcmp(result->Name, name) && 0 == strcmp(result->Scope, currentScope))
      return result;

    result = result->Next;
  }

  if (0 == strcmp(result->Name, name) && 0 == strcmp(result->Scope, currentScope))
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
    if (0 == strcmp(result->Name, name) && 0 == strcmp(result->Scope, currentScope))
      break;

    result = result->Next;
  }

  if (0 == strcmp(result->Name, name) && 0 == strcmp(result->Scope, currentScope))
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
  result->Scope = currentScope;
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
      if (0 == strcmp(result->Name, name) && 0 == strcmp(result->Scope, currentScope))
        break;

      result = result->Next;
    }

    result->Next = CreateVariable(name, value, type);
  }
}

char *EvaluateIntExpression(IntExpression *expression)
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

void EvaluatePrintExpression(PrintExpression *expression)
{
  if (NULL == expression)
    return;

  Variable *variable;
  char *p;
  switch (expression->Type)
  {
  case PrintString:
    p = expression->Value;
    p++;
    p[strlen(p) - 1] = 0;

    printf("%s\n", p);
    break;
  case PrintVariable:
    variable = GetVariable(expression->Variable);
    if (variable == NULL)
    {
      printf("Error: variable %s undeclared\n", expression->Variable);
      exit(-1);
    }

    printf("%s\n", variable->Value);
    break;
  }
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

char *EvaluateBoolExpression(BoolExpression *expression)
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

void EvaluateFunctionCall(Function *function, Statement *function_call)
{
  Parameter *param = function->Params;
  Parameter *value = function_call->Params;
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
      valuestr = EvaluateIntExpression(value->inte);
    }
    else if (value->Type == 1)
    {
      valuestr = EvaluateStringExpression(value->stringe);
    }
    else if (value->Type == 2)
    {
      valuestr = EvaluateBoolExpression(value->boole);
    }

    currentScope = function->FunctionName;
    param->Value = valuestr;
    Variable *var = GetVariable(param->Name);
    if (var == NULL)
    {
      CreateNewVariable(param->Name, valuestr, param->Type);
    }
    else
    {
      SetVariable(param->Name, valuestr, param->Type);
    }

    currentScope = "global";

    value = value->Next;
    param = param->Next;
  }

  currentScope = function->FunctionName;
  EvaluateStatement(function->Body);
  currentScope = "global";
}

void EvaluateStatement(Statement *statement)
{
  if (NULL == statement)
    return;

  char *value;
  Variable *exValue;
  Function *function;
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
    EvaluatePrintExpression(statement->PrintValue);
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
  case While:
    value = EvaluateBoolExpression(statement->BoolValue);
    while (GetBoolValue(value) == 1)
    {
      EvaluateStatement(statement->Left);
      value = EvaluateBoolExpression(statement->BoolValue);
    }
    break;
  case FunctionDeclaration:
    if (currentScope != "global")
    {
      printf("Error: declaring functions inside functions is not allowed\n");
      exit(-1);
    }

    function = GetFunction(statement->Variable);
    if (function != NULL)
    {
      printf("Error: function %s is already declared\n", statement->Variable);
      exit(-1);
    }

    CreateNewFunction(statement->Variable, statement->Params, statement->Left);
    break;
  case FunctionCall:
    function = GetFunction(statement->Variable);
    if (function == NULL)
    {
      printf("Error: function %s is undeclared\n", statement->Variable);
      exit(-1);
    }

    EvaluateFunctionCall(function, statement);
    break;
  }
}

void DeleteIntExpression(IntExpression *expression)
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

void DeletePrintExpression(PrintExpression *expression)
{
  if (NULL == expression)
    return;

  switch (expression->Type)
  {
  case PrintString:
    free(expression->Value);
    break;
  case PrintVariable:
    free(expression->Variable);
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
    DeletePrintExpression(statement->PrintValue);
    break;
  case Conditional:
    DeleteBoolExpression(statement->BoolValue);
    DeleteStatement(statement->Left);
    DeleteStatement(statement->Right);
    break;
  case While:
    DeleteBoolExpression(statement->BoolValue);
    DeleteStatement(statement->Left);
    break;
  }

  free(statement);
}
