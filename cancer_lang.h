#ifndef __CANCER_LANG__
#define __CANCER_LANG__

#include <stdio.h>

typedef enum VariableTypeEnum
{
    INT,
    STRING,
    BOOL
} VariableType;

typedef enum NumerableExpNumberType
{
    IntLiteral,
    IntVariable,
    Addition,
    Subtraction,
    Multiplication,
    Division
} IntExpressionType;

typedef struct expNumericStructure expNumber;
struct expNumericStructure
{
    IntExpressionType Type;
    expNumber *Left;
    expNumber *Right;
    char *Symbol;
    char *Value;
};

typedef enum NumerableExpWordType
{
    StringLiteral,
    StringVariable
} StringExpressionType;

typedef struct expWordStructure expWord;
struct expWordStructure
{
    StringExpressionType Type;
    expWord *left;
    expWord *right;
    char *Symbol;
    char *Value;
};

typedef enum NumerableExpFlagType
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

typedef struct expFlagStructure expFlag;
struct expFlagStructure
{
    BoolExpressionType Type;
    expFlag *Left;
    expFlag *Right;
    expNumber *IntLeft;
    expNumber *IntRight;
    char *Symbol;
    char *Value;
};

typedef enum LineTypes
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
} LineType;

typedef enum NumericExpWriteType
{
    PrintString,
    PrintVariable
} PrintExpresssionType;

typedef struct NumericExpWriteStructure expWrite;
struct NumericExpWriteStructure
{
    PrintExpresssionType Type;
    char *Symbol;
    char *Value;
};

typedef struct CharacteristicsStructure Characteristic;
struct CharacteristicsStructure
{
    expFlag *boole;
    expNumber *inte;
    expWord *stringe;
    VariableType Type;
    Characteristic *Upcoming;
    char *Name;
    char *Value;
};

typedef struct LineStructure Line;
struct LineStructure
{
    LineType Type;
    Line *Left;
    Line *Right;
    expNumber *NumericVal;
    expFlag *FlagVal;
    expWord *StringValue;
    expWrite *WriteText;
    Characteristic *Characteristics;
    char *Symbol;
};

typedef struct MagicStructure Magic;
struct MagicStructure
{
    Characteristic *Characteristics;
    char *MagicName;
    Line *Content;
    Magic *Upcoming;
};

Line *GenerateNumericDefinition(char *variable, expNumber *value);
Line *GenerateWordDefinition(char *variable, expWord *value);
Line *GenerateFlagDefinition(char *variable, expFlag *value);

Line *GenerateNumericCreation(char *variable, expNumber *value);
Line *GenerateWordCreation(char *variable, expWord *value);
Line *GenerateFlagCreation(char *variable, expFlag *value);

Line *Write(expWrite *variable);
Line *LineSeqGenerate(Line *first, Line *second);
Line *GeneratePositiveNegative(Line *ifTrue, Line *ifFalse, expFlag *condition);
Line *GenerateLoop(expFlag *condition, Line *body);
Line *NewMagic(char *function_name, Characteristic *params, Line *body);
Line *GenerateMagicShout(char *function_name, Characteristic *values);

Characteristic *GenerateCharacteristic(char *name, VariableType type);
Characteristic *GenerateCharacteristics(Characteristic *first, Characteristic *second);

Characteristic *GenerateNumericExpCharacteritic(expNumber *expression);
Characteristic *GenerateWordExpCharacteritic(expWord *expression);
Characteristic *GenerateFlagExpCharacteritic(expFlag *expression);

expWrite *GenerateWriteWord(char *value);
expWrite *GenerateWriteSymbol(char *variable);

expNumber *GenerateNumeric(int number);
expNumber *GenerateAddition(expNumber *left, expNumber *right);
expNumber *GenerateSubtraction(expNumber *left, expNumber *right);
expNumber *GenerateMulExpression(expNumber *left, expNumber *right);
expNumber *GenerateDivExpression(expNumber *left, expNumber *right);
expNumber *GenerateNumericSymbol(char *variable);

expWord *GenerateWord(char *string);
expWord *GenerateWordSymbol(char *variable);

expFlag *GenerateFlag(int bool);
expFlag *GenerateFlagSymbol(char *variable);
expFlag *GenerateNumericEven(expNumber *left, expNumber *right);
expFlag *GenerateNumericEvenLess(expNumber *left, expNumber *right);
expFlag *GenerateNumericEvenGreater(expNumber *left, expNumber *right);
expFlag *GenerateNumericLower(expNumber *left, expNumber *right);
expFlag *GenerateNumericGreater(expNumber *left, expNumber *right);
expFlag *GenerateNumericInvariant(expFlag *value);
expFlag *GenerateNumericWith(expFlag *left, expFlag *right);
expFlag *GenerateNumericEither(expFlag *left, expFlag *right);

void RemoveLine(Line *line);
void RemoveExpNumericMathematics(expNumber *expression);

void EmptyRAM();
void EmptyMagicRAM();

void ProcessLine(Line *line);

char *ProcessExpNumeric(expNumber *expression);
char *ProcessExpWord(expWord *expression);
char *ProcessExpFlag(expFlag *expression);

#endif