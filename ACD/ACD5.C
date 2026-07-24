/* NOTE: This is a LEX source program (to be compiled with lex/flex + gcc),
   not a Turbo C program, since it uses LEX pattern-matching rules. */

%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int line = 1;
char *keywords[] = {"int", "float", "char", "return", "if", "else", "while", "for", "void"};
int isKeyword(char *str);
void addToSymbolTable(char *identifier);
%}

%option noyywrap

IDENT   [a-zA-Z_][a-zA-Z0-9_]*
NUMBER  [0-9]+
FLOAT   [0-9]*\.[0-9]+
OP      [+\-*/=<>!]=?
COMMENT ("//".*|"/*"([^*]|\*+[^*/])*\*+"/")

%%

{COMMENT}   { printf("Comment: %s\n", yytext); }
"("         { printf("Left Paren: %s\n", yytext); }
")"         { printf("Right Paren: %s\n", yytext); }
"{"         { printf("Left Brace: %s\n", yytext); }
"}"         { printf("Right Brace: %s\n", yytext); }
{OP}        { printf("Operator: %s\n", yytext); }
{FLOAT}     { printf("Float Constant: %s\n", yytext); }
{NUMBER}    { printf("Integer Constant: %s\n", yytext); }
{IDENT}     {
                if (isKeyword(yytext))
                    printf("Keyword: %s\n", yytext);
                else
                {
                    printf("Identifier: %s\n", yytext);
                    addToSymbolTable(yytext);
                }
            }
[\n]        { line++; }
[ \t]+      ; /* Ignore whitespace */
.           { printf("Unrecognized symbol: %s\n", yytext); }

%%

int isKeyword(char *str)
{
    int i;
    for (i = 0; i < sizeof(keywords)/sizeof(keywords[0]); i++)
    {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

/* --- Symbol Table Implementation --- */
#define SIZE 100
char *symbolTable[SIZE];
int symCount = 0;

void addToSymbolTable(char *identifier)
{
    int i;
    for (i = 0; i < symCount; i++)
    {
        if (strcmp(symbolTable[i], identifier) == 0)
            return; /* Already exists */
    }
    symbolTable[symCount++] = strdup(identifier);
}

/* Optional: Print Symbol Table at End */
int yywrap()
{
    int i;
    printf("\n--- Symbol Table ---\n");
    for (i = 0; i < symCount; i++)
        printf("%s\n", symbolTable[i]);
    return 1;
}

/*
Input (test.c):
int main() {
float a = 3.14;
int b = 10;
// This is a comment
a = a + b;
}

Execution Steps:
lex lexer.l
gcc lex.yy.c -o lexer
./lexer < test.c
*/
