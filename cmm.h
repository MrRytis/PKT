#ifndef __CMM__
#define __CMM__

#include <stdio.h>

typedef enum NumerableSymbolType
{
    numeric,
    word,
    flag
} SymbolicTp;

typedef enum NumerableExpNumberType
{
    numericData,
    numericSymbol,
    Plus,
    Minus,
    MathMul,
    MathSplitEvenGroup
} expNumericTp;

typedef struct expNumericStructure expNumber;
struct expNumericStructure
{
    expNumericTp kind;
    expNumber *Left;
    expNumber *Right;
    char *Symbol;
    char *Worth;
};

typedef enum NumerableExpWordType
{
    wordValue,
    wordSymbol
} expWordType;

typedef struct expWordStructure expWord;
struct expWordStructure
{
    expWordType kind;
    expWord *left;
    expWord *right;
    char *Symbol;
    char *Worth;
};

typedef enum NumerableExpFlagType
{
    flagData,
    flagSymbol,
    Even,
    Also,
    Either,
    Opposite ,
    Fewer,
    Greater,
    EvenOrFewer,
    GreaterOrEven
} expFlagTp;

typedef struct expFlagStructure expFlag;
struct expFlagStructure
{
    expFlagTp kind;
    expFlag *Left;
    expFlag *Right;
    expNumber *numericLeft;
    expNumber *numericRight;
    char *Symbol;
    char *Worth;
};

typedef enum LineTypes
{
    CreateNumeric,
    CreateWord,
    CreateFlag,
    NumericDefinition,
    WordDefinition,
    FlagDefinition,
    Print,
    Chain,
    Restrictive,
    Loop,
    MagicDefinition,
    MagicShout
} LineTp;

typedef enum NumericExpWriteType
{
    WriteText,
    WriteSymbol
} expWriteType;

typedef struct NumericExpWriteStructure expWrite;
struct NumericExpWriteStructure
{
    expWriteType kind;
    char *Symbol;
    char *Worth;
};

typedef struct CharacteristicsStructure Characteristic;
struct CharacteristicsStructure
{
    expFlag *boole;
    expNumber *inte;
    expWord *stringe;
    SymbolicTp kind;
    Characteristic *Upcoming;
    char *Name;
    char *Worth;
};

typedef struct LineStructure Line;
struct LineStructure
{
    LineTp kind;
    Line *Left;
    Line *Right;
    expNumber *NumericVal;
    expFlag *FlagVal;
    expWord *WordWorth;
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

Line *GenerateNumericDefinition(char *symbol, expNumber *data);
Line *GenerateWordDefinition(char *symbol, expWord *data);
Line *GenerateFlagDefinition(char *symbol, expFlag *data);

Line *GenerateNumericCreation(char *symbol, expNumber *data);
Line *GenerateWordCreation(char *symbol, expWord *data);
Line *GenerateFlagCreation(char *symbol, expFlag *data);

Line *Write(expWrite *symbol);
Line *LineChainGenerate(Line *primary, Line *secondary);
Line *GeneratePositiveNegative(Line *Positive, Line *Negative, expFlag *restriction);
Line *GenerateLoop(expFlag *restriction, Line *content);
Line *NewMagic(char *magic_name, Characteristic *params, Line *content);
Line *GenerateMagicShout(char *magic_name, Characteristic *worths);

Characteristic *GenerateCharacteristic(char *name, SymbolicTp type);
Characteristic *GenerateCharacteristics(Characteristic *primary, Characteristic *secondary);

Characteristic *GenerateNumericExpCharacteritic(expNumber *exp);
Characteristic *GenerateWordExpCharacteritic(expWord *exp);
Characteristic *GenerateFlagExpCharacteritic(expFlag *exp);

expWrite *GenerateWriteWord(char *data);
expWrite *GenerateWriteSymbol(char *symbol);

expNumber *GenerateNumeric(int number);
expNumber *GenerateAddition(expNumber *left, expNumber *right);
expNumber *GenerateSubtraction(expNumber *left, expNumber *right);
expNumber *GenerateMulExpression(expNumber *left, expNumber *right);
expNumber *GenerateDivExpression(expNumber *left, expNumber *right);
expNumber *GenerateNumericSymbol(char *symbol);

expWord *GenerateWord(char *word);
expWord *GenerateWordSymbol(char *symbol);

expFlag *GenerateFlag(int flag);
expFlag *GenerateFlagSymbol(char *symbol);
expFlag *GenerateNumericEven(expNumber *left, expNumber *right);
expFlag *GenerateNumericEvenLess(expNumber *left, expNumber *right);
expFlag *GenerateNumericEvenGreater(expNumber *left, expNumber *right);
expFlag *GenerateNumericLower(expNumber *left, expNumber *right);
expFlag *GenerateNumericGreater(expNumber *left, expNumber *right);
expFlag *GenerateNumericInvariant(expFlag *data);
expFlag *GenerateNumericWith(expFlag *left, expFlag *right);
expFlag *GenerateNumericEither(expFlag *left, expFlag *right);

void RemoveLine(Line *line);
void RemoveExpNumericMathematics(expNumber *exp);

void EmptyRAM();
void EmptyMagicRAM();

void ProcessLine(Line *line);

char *ProcessExpNumeric(expNumber *exp);
char *ProcessExpWord(expWord *exp);
char *ProcessExpFlag(expFlag *exp);

#endif
