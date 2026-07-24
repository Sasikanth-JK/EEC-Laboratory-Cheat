/* NOTE: This is a LEX + YACC source program (to be compiled with lex/yacc + gcc),
   not a Turbo C program. It consists of two files: calc.l and calc.y */

/* ======================= calc.l - LEX Program ======================= */
%{
#include "y.tab.h"
#include <stdio.h>
%}

%%

[0-9]+      { yylval = atoi(yytext); return NUMBER; }
[+\-*/]     { return yytext[0]; }
[\n]        { return '\n'; }
[()]        { return yytext[0]; }
[ \t]       { /* Ignore whitespace */ }
.           { printf("Invalid character: %s\n", yytext); }

%%

int yywrap()
{
    return 1;
}


/* ======================= calc.y - YACC Program ======================= */
%{
#include <stdio.h>
#include <stdlib.h>
%}

%token NUMBER
%left '+' '-'
%left '*' '/'
%right UMINUS

%%

input:
      /* empty */
    | input line
    ;

line:
      '\n'
    | expr '\n'   { printf("Result = %d\n", $1); }
    ;

expr: NUMBER               { $$ = $1; }
    | expr '+' expr        { $$ = $1 + $3; }
    | expr '-' expr        { $$ = $1 - $3; }
    | expr '*' expr        { $$ = $1 * $3; }
    | expr '/' expr        {
                                if ($3 == 0)
                                {
                                    printf("Error: Division by zero\n");
                                    exit(1);
                                }
                                $$ = $1 / $3;
                            }
    | '-' expr %prec UMINUS { $$ = -$2; }
    | '(' expr ')'          { $$ = $2; }
    ;

%%

int main()
{
    printf("Enter arithmetic expressions (Ctrl+D to exit):\n");
    yyparse();
    return 0;
}

int yyerror(const char *s)
{
    fprintf(stderr, "Parse error: %s\n", s);
    return 1;
}

/*
How to Compile and Run
yacc -d calc.y        # Generates y.tab.c and y.tab.h
lex calc.l             # Generates lex.yy.c
gcc y.tab.c lex.yy.c -o calc -ll   # Compile and link LEX/YACC
./calc                 # Run the calculator

Sample Input and Output
5 + 3
7 * (2 + 3)
10 / 2 - 1
-4 + 6
10 / 0

Output:
Result = 8
Result = 35
Result = 4
Result = 2
Error: Division by zero
*/
