%{
#include "cancer_lang.h"
#include "parser.h"

#include <string.h>
%}

%option outfile="lexer.c" header-file="lexer.h"

%option reentrant noyywrap never-interactive nounistd
%option bison-bridge

WS [ \r\t]+

NUMBER [0-9]
WORD   [a-zA-Z][a-zA-Z0-9]*
STRING \"(\\.|[^"\\])*\"

%%
{WS}                   ;
"int"                  { return TYPE_INT; }
"string"               { return TYPE_STRING; }
"bool"                 { return TYPE_BOOL; }
"print"                { return PRINT; }
"true"                 { return TRUE; }
"false"                { return FALSE; }
"if"                   { return IF; }
"{"                    { return L_CURL; }
"}"                    { return R_CURL; }
"else"                 { return ELSE; }
"=="                   { return EQUALS; }
"!"                    { return NOT; }
"&&"                   { return AND; }
"||"                   { return OR; }
"<="                   { return LTEQ; }
">="                   { return GTEQ; }
"<"                    { return LT; }
">"                    { return GT; }
"-"                    { return MINUS; }
"/"                    { return SLASH; }
"*"                    { return STAR; }
"+"                    { return PLUS; }
"("                    { return L_PAREN; }
")"                    { return R_PAREN; }
"="                    { return ASSIGNMENT; }
{STRING}               { yylval->string = strdup(yytext); return STRING_VAL; } 
{NUMBER}+              { yylval->value = atoi(yytext); return NUMBER; }
{WORD}                 { yylval->var_name = strdup(yytext); return VAR_NAME; }
\n                     { return ENDL; }
%%