/* NOTE: This is a LEX source program (to be compiled with lex/flex + gcc),
   not a Turbo C program, since it uses LEX pattern-matching rules. */

%{
#include <stdio.h>
%}

KEYWORD     int|float|if|else|while|return
IDENTIFIER  [a-zA-Z_][a-zA-Z0-9_]*
NUMBER      [0-9]+(\.[0-9]+)?
OPERATOR    \+|\-|\*|\/|\=|\<|\>|\<=|\>=|\==

%%

{KEYWORD}       { printf("Keyword: %s\n", yytext); }
{IDENTIFIER}    { printf("Identifier: %s\n", yytext); }
{NUMBER}        { printf("Number: %s\n", yytext); }
{OPERATOR}      { printf("Operator: %s\n", yytext); }
[ \t\n]+        { /* Ignore whitespace */ }
.               { printf("Unknown token: %s\n", yytext); }

%%

/* Main function */
int main()
{
    printf("Enter the code (Ctrl+D to end input):\n");
    yylex();
    return 0;
}

/* Function to signal end of input */
int yywrap()
{
    return 1;
}

/*
Steps to Compile and Run
1. Save the above code in a file named lexer.l.
2. Open terminal and run:
   lex lexer.l          # Generates lex.yy.c
   gcc lex.yy.c -ll -o lexer   # Compiles the code
   ./lexer              # Run the program

Sample Input (entered after running ./lexer):
int num = 25;
float value = 3.14;
if (num > 10) return value;

Sample Output:
Keyword: int
Identifier: num
Operator: =
Number: 25
Operator: ;
Keyword: float
Identifier: value
Operator: =
Number: 3.14
Operator: ;
Keyword: if
Operator: (
Identifier: num
Operator: >
Number: 10
Operator: )
Keyword: return
Identifier: value
Operator: ;
*/
