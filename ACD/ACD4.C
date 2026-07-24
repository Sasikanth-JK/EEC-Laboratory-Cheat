#include<stdio.h>
#include<string.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char symbol)
{
    stack[++top] = symbol;
}

char pop()
{
    if (top == -1)
        return 'X'; /* special symbol for empty */
    return stack[top--];
}

int main()
{
    char input[MAX];
    int i, valid = 1;
    int stage = 0; /* 0: reading a's, 1: reading b's */

    printf("Enter a string (L = { a^n b^n }): ");
    scanf("%s", input);

    for (i = 0; i < strlen(input); i++)
    {
        if (input[i] == 'a' && stage == 0)
        {
            push('a');
        }
        else if (input[i] == 'b')
        {
            stage = 1;
            if (pop() != 'a')
            {
                valid = 0;
                break;
            }
        }
        else
        {
            valid = 0;
            break;
        }
    }

    /* Final condition: stack must be empty and valid transitions */
    if (valid && top == -1 && stage == 1)
        printf("String is ACCEPTED by the PDA.\n");
    else
        printf("String is REJECTED by the PDA.\n");

    return 0;
}
