#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX 100

/* Stack implementation */
char stack[MAX];
int top = -1;

void push(char c)
{
    if (top < MAX-1) stack[++top] = c;
}

char pop()
{
    if (top >= 0) return stack[top--];
    return '\0';
}

char peek()
{
    if (top >= 0) return stack[top];
    return '\0';
}

/* Parsing Table for grammar:
   E  -> T E'
   E' -> + T E' | e
   T  -> F T'
   T' -> * F T' | e
   F  -> (E) | i (we use 'i' for id)
*/
const char* table[5][6];
/* Non-terminals: E=0, Q(E')=1, T=2, R(T')=3, F=4 */
/* Terminals: i=0, +=1, *=2, (=3, )=4, $=5 */

int getNonTerminalIndex(char nt)
{
    switch (nt)
    {
        case 'E': return 0;
        case 'Q': return 1; /* we use Q for E' */
        case 'T': return 2;
        case 'R': return 3; /* we use R for T' */
        case 'F': return 4;
    }
    return -1;
}

int getTerminalIndex(char t)
{
    switch (t)
    {
        case 'i': return 0;
        case '+': return 1;
        case '*': return 2;
        case '(': return 3;
        case ')': return 4;
        case '$': return 5;
    }
    return -1;
}

int main()
{
    char input[MAX];
    int ip;
    char X, a;
    int i, row, col;
    const char *prod;

    /* Fill parsing table */
    /* Using Q instead of E' and R instead of T' (to avoid confusion with prime symbol) */
    /* E */
    table[0][0] = "TQ"; /* E -> TQ for i */
    table[0][3] = "TQ"; /* E -> TQ for ( */
    /* Q (E') */
    table[1][1] = "+TQ"; /* Q -> +TQ */
    table[1][4] = "e";   /* Q -> e */
    table[1][5] = "e";   /* Q -> e */
    /* T */
    table[2][0] = "FR"; /* T -> FR */
    table[2][3] = "FR"; /* T -> FR */
    /* R (T') */
    table[3][1] = "e";   /* R -> e */
    table[3][2] = "*FR"; /* R -> *FR */
    table[3][4] = "e";   /* R -> e */
    table[3][5] = "e";   /* R -> e */
    /* F */
    table[4][0] = "i";   /* F -> i */
    table[4][3] = "(E)"; /* F -> (E) */

    printf("Enter input string (use i for id): ");
    scanf("%s", input);
    strcat(input, "$");

    /* Initialize stack */
    push('$');
    push('E');
    ip = 0;

    printf("\n%-20s %-20s %-20s\n", "Stack", "Input", "Action");

    while (top >= 0)
    {
        X = peek();
        a = input[ip];

        /* Print current config */
        for (i = 0; i <= top; i++) printf("%c", stack[i]);
        printf("%-20s ", "");
        printf("%-20s ", input+ip);

        if (X == a && X == '$')
        {
            printf("Accept\n");
            break;
        }
        else if (X == a)
        {
            pop();
            ip++;
            printf("Match %c\n", a);
        }
        else if (X=='E' || X=='Q' || X=='T' || X=='R' || X=='F')
        {
            row = getNonTerminalIndex(X);
            col = getTerminalIndex(a);
            prod = table[row][col];
            if (prod == NULL)
            {
                printf("Error: no rule\n");
                break;
            }
            pop();
            if (strcmp(prod,"e") != 0)
            {
                for (i = strlen(prod)-1; i >= 0; i--) push(prod[i]);
            }
            printf("%c -> %s\n", X, prod);
        }
        else
        {
            printf("Error\n");
            break;
        }
    }

    return 0;
}
