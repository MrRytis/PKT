#ifndef __CANCER_LANG__
#define __CANCER_LANG__

#include <stdio.h>

typedef enum VariableTypeEnum
{
    INT,
    STRING,
    BOOL
} VariableType;

typedef enum IntExpressionTypeEnum
{
    IntLiteral,
    IntVariable,
    Addition,
    Subtraction,
    Multiplication,
    Division
} IntExpressionType;

typedef struct IntExpressionStruct IntExpression;
struct IntExpressionStruct
{
    IntExpressionType Type;
    IntExpression *Left;
    IntExpression *Right;
    char *Variable;
    char *Value;
};

typedef enum StringExpressionTypeEnum
{
    StringLiteral,
    StringVariable
} StringExpressionType;

typedef struct StringExpressionStruct StringExpression;
struct StringExpressionStruct
{
    StringExpressionType Type;
    StringExpression *left;
    StringExpression *right;
    char *Variable;
    char *Value;
};

typedef enum BoolExpressionTypeEnum
{
    BoolLiteral,
    BoolVariable,
    Equals,
    And,
    Or,
    Not,
    Less,
    More,
    LessEquals,
    MoreEquals
} BoolExpressionType;

typedef struct BoolExpressionStruct BoolExpression;
struct BoolExpressionStruct
{
    BoolExpressionType Type;
    BoolExpression *Left;
    BoolExpression *Right;
    IntExpression *IntLeft;
    IntExpression *IntRight;
    char *Variable;
    char *Value;
};

typedef enum StatementTypeEnum
{
    IntDeclaration,
    StringDeclaration,
    BoolDeclaration,
    IntAssignment,
    StringAssignment,
    BoolAssignment,
    Print,
    Sequence,
    Conditional,
    While,
    FunctionDeclaration,
    FunctionCall
} StatementType;

typedef enum PrintExpresssionTypeEnum
{
    PrintString,
    PrintVariable
} PrintExpresssionType;

typedef struct PrintExpressionStruct PrintExpression;
struct PrintExpressionStruct
{
    PrintExpresssionType Type;
    char *Variable;
    char *Value;
};

typedef struct ParameterStruct Parameter;
struct ParameterStruct
{
    BoolExpression *boole;
    IntExpression *inte;
    StringExpression *stringe;
    VariableType Type;
    Parameter *Next;
    char *Name;
    char *Value;
};

typedef struct StatementStruct Statement;
struct StatementStruct
{
    StatementType Type;
    Statement *Left;
    Statement *Right;
    IntExpression *IntValue;
    BoolExpression *BoolValue;
    StringExpression *StringValue;
    PrintExpression *PrintValue;
    Parameter *Params;
    char *Variable;
};

typedef struct FunctionStruct Function;
struct FunctionStruct
{
    Parameter *Params;
    char *FunctionName;
    Statement *Body;
    Function *Next;
};

Statement *BuildIntAssignment(char *variable, IntExpression *value);
Statement *BuildStringAssignment(char *variable, StringExpression *value);
Statement *BuildBoolAssignment(char *variable, BoolExpression *value);

Statement *BuildIntDeclaration(char *variable, IntExpression *value);
Statement *BuildStringDeclaration(char *variable, StringExpression *value);
Statement *BuildBoolDeclaration(char *variable, BoolExpression *value);

Statement *BuildPrint(PrintExpression *variable);
Statement *BuildStatementSequence(Statement *first, Statement *second);
Statement *BuildConditional(Statement *ifTrue, Statement *ifFalse, BoolExpression *condition);
Statement *BuildWhile(BoolExpression *condition, Statement *body);
Statement *BuildFunction(char *function_name, Parameter *params, Statement *body);
Statement *BuildFunctionCall(char *function_name, Parameter *values);

Parameter *BuildParam(char *name, VariableType type);
Parameter *BuildParameterList(Parameter *first, Parameter *second);

Parameter *BuildIntValueParam(IntExpression *expression);
Parameter *BuildStringValueParam(StringExpression *expression);
Parameter *BuildBoolValueParam(BoolExpression *expression);

PrintExpression *BuildPrintString(char *value);
PrintExpression *BuildPrintVariable(char *variable);

IntExpression *BuildNumber(int number);
IntExpression *BuildSum(IntExpression *left, IntExpression *right);
IntExpression *BuildDifference(IntExpression *left, IntExpression *right);
IntExpression *BuildMultiplication(IntExpression *left, IntExpression *right);
IntExpression *BuildDivision(IntExpression *left, IntExpression *right);
IntExpression *BuildIntVariable(char *variable);

StringExpression *BuildString(char *string);
StringExpression *BuildStringVariable(char *variable);

BoolExpression *BuildBool(int bool);
BoolExpression *BuildBoolVariable(char *variable);
BoolExpression *BuildEquals(IntExpression *left, IntExpression *right);
BoolExpression *BuildLessOrEquals(IntExpression *left, IntExpression *right);
BoolExpression *BuildMoreOrEquals(IntExpression *left, IntExpression *right);
BoolExpression *BuildLess(IntExpression *left, IntExpression *right);
BoolExpression *BuildMore(IntExpression *left, IntExpression *right);
BoolExpression *BuildNot(BoolExpression *value);
BoolExpression *BuildAnd(BoolExpression *left, BoolExpression *right);
BoolExpression *BuildOr(BoolExpression *left, BoolExpression *right);

void DeleteStatement(Statement *statement);
void DeleteArithmeticExpression(IntExpression *expression);

void FreeMemory();
void FreeFunctionMemory();

void EvaluateStatement(Statement *statement);

char *EvaluateIntExpression(IntExpression *expression);
char *EvaluateStringExpression(StringExpression *expression);
char *EvaluateBoolExpression(BoolExpression *expression);

#endif