/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 17 "cancer_lang.y" /* yacc.c:1909  */

#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
  
typedef void* yyscan_t;

#endif

#line 53 "parser.h" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TRUE = 258,
    FALSE = 259,
    TYPE_INT = 260,
    TYPE_STRING = 261,
    TYPE_BOOL = 262,
    PRINT = 263,
    IF = 264,
    WHILE = 265,
    L_CURL = 266,
    R_CURL = 267,
    ELSE = 268,
    LTEQ = 269,
    GTEQ = 270,
    LT = 271,
    GT = 272,
    EQUALS = 273,
    NOT = 274,
    AND = 275,
    OR = 276,
    L_PAREN = 277,
    R_PAREN = 278,
    STAR = 279,
    PLUS = 280,
    MINUS = 281,
    SLASH = 282,
    ASSIGNMENT = 283,
    ENDL = 284,
    NUMBER = 285,
    VAR_NAME = 286,
    STRING_VAL = 287
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 32 "cancer_lang.y" /* yacc.c:1909  */

  #include <stdbool.h>

  Statement *statement;
  IntExpression *int_expression;
  BoolExpression *bool_expression;
  StringExpression *string_expression;
  char* var_name;
  char* string;
  int value;
  bool bval;

#line 111 "parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (Statement **program, yyscan_t scanner);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
