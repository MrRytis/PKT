%{
#include <string.h>
#include "cmm.h"
#include "p.h"
%}

%option outfile="l.c" header-file="l.h"
%option reentrant noyywrap never-interactive nounistd
%option bison-bridge


%%

"-"                    { return MIN; }
"+"                    { return ADD; }
"/"                    { return DIVIDE; }
"*"                    { return MULTIPLY; }

"=="                   { return EQUALS; }
"!"                    { return NOT; }
"&&"                   { return AND; }
"||"                   { return OR; }
"<="                   { return LTE; }
">="                   { return GTE; }
"<"                    { return LT; }
">"                    { return GT; }

","                    { return COMMA; }
"("                    { return BRACKET_LEFT; }
")"                    { return BRACKET_RIGHT; }
"="                    { return ASSIGNMENT; }
"{"                    { return CURL_LEFT; }
"}"                    { return CURL_RIGHT; }

"true"                 { return TRUE; }
"false"                { return FALSE; }

"spit"                 { return PRINT; }
"maybe"                { return IF; }
"else"                 { return ELSE; }
"loop"                 { return WHILE; }
"magic"                { return FUNCTION; }

"number"               { return INT_TYPE; }
"word"                 { return STRING_TYPE; }
"check"                { return BOOL_TYPE; }

\"(\\.|[^"\\])*\"      { yylval->str = strdup(yytext); return WORD; } 
[0-9]+                 { yylval->data = atoi(yytext); return NUMBER; }
[a-zA-Z][a-zA-Z0-9]*   { yylval->variable_name = strdup(yytext); return NAME; }
\n                     { return END_LINE; }
%%