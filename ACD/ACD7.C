#include<stdio.h>
#include<string.h>

char stack[50];
char input[50];
int top = -1, i = 0;

/* Function to print stack and input */
void printStackInput(int j)
{
    int k;
    printf("\nStack: ");
    for (k = 0; k <= top; k++)
        printf("%c", stack[k]);
    printf("\tInput: ");
    for (k = j; k < strlen(input); k++)
        printf("%c", input[k]);
}

/* Function to reduce stack content */
int reduce()
{
    /* Try reducing id (represented as 'i') to E */
    if (top >= 0 && stack[top] == 'i')
    {
        stack[top] = 'E';
        printf(" => Reduced: E -> id");
        return 1;
    }
    /* Try reducing E+E -> E */
    if (top >= 2 && stack[top] == 'E' && stack[top-1] == '+' && stack[top-2] == 'E')
    {
        stack[top-2] = 'E';
        top -= 2;
        printf(" => Reduced: E -> E+E");
        return 1;
    }
    /* Try reducing E*E -> E */
    if (top >= 2 && stack[top] == 'E' && stack[top-1] == '*' && stack[top-2] == 'E')
    {
        stack[top-2] = 'E';
        top -= 2;
        printf(" => Reduced: E -> E*E");
        return 1;
    }
    /* Try reducing (E) -> E */
    if (top >= 2 && stack[top] == ')' && stack[top-1] == 'E' && stack[top-2] == '(')
    {
        stack[top-2] = 'E';
        top -= 2;
        printf(" => Reduced: E -> (E)");
        return 1;
    }
    return 0; /* No reduction possible */
}

int main()
{
    printf("Enter the input string (like i+i*i): ");
    scanf("%s", input);

    printf("\nShift-Reduce Parsing Steps:\n");
    while (i <= strlen(input))
    {
        printStackInput(i);
        if (i < strlen(input))
        {
            /* Shift */
            stack[++top] = input[i++];
            printf(" => Shift");
        }
        /* Keep reducing until not possible */
        while (reduce());
    }

    /* Final acceptance check */
    if (top == 0 && stack[0] == 'E')
    {
        printf("\n\nInput string ACCEPTED.\n");
    }
    else
    {
        printf("\n\nInput string REJECTED.\n");
    }

    return 0;
}
