#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define SIZE 100

char stack[SIZE];
int top = -1;

/* Push operation */
void push(char c)
{
    stack[++top] = c;
}

/* Pop operation */
char pop()
{
    return stack[top--];
}

/* Stack top */
char peek()
{
    return stack[top];
}

/* Check if operator */
int isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

/* Precedence of operators */
int precedence(char op)
{
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

/* Infix to Postfix */
void infixToPostfix(char infix[], char postfix[])
{
    int i, j = 0;
    char c;

    for (i = 0; i < strlen(infix); i++)
    {
        c = infix[i];
        if (isspace(c)) continue;
        if (isalnum(c))
        {
            postfix[j++] = c;
        }
        else if (c == '(')
        {
            push(c);
        }
        else if (c == ')')
        {
            while (top != -1 && peek() != '(')
                postfix[j++] = pop();
            pop(); /* remove '(' */
        }
        else if (isOperator(c))
        {
            while (top != -1 && precedence(peek()) >= precedence(c))
                postfix[j++] = pop();
            push(c);
        }
    }
    while (top != -1) postfix[j++] = pop();
    postfix[j] = '\0';
}

/* Reverse string */
void reverse(char str[])
{
    int n = strlen(str);
    int i;
    char tmp;

    for (i = 0; i < n / 2; i++)
    {
        tmp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = tmp;
    }
}

/* Swap ( and ) */
void swapParentheses(char expr[])
{
    int i;
    for (i = 0; i < strlen(expr); i++)
    {
        if (expr[i] == '(') expr[i] = ')';
        else if (expr[i] == ')') expr[i] = '(';
    }
}

/* Infix to Prefix */
void infixToPrefix(char infix[], char prefix[])
{
    char revInfix[SIZE], postfix[SIZE];

    strcpy(revInfix, infix);
    reverse(revInfix);
    swapParentheses(revInfix);
    top = -1;
    infixToPostfix(revInfix, postfix);
    reverse(postfix);
    strcpy(prefix, postfix);
}

/* MAIN FUNCTION */
int main()
{
    char infix[SIZE], postfix[SIZE], prefix[SIZE];

    printf("Enter Infix Expression: ");
    fgets(infix, SIZE, stdin);
    infix[strcspn(infix, "\n")] = '\0'; /* remove newline */

    infixToPostfix(infix, postfix);
    infixToPrefix(infix, prefix);

    printf("\nPostfix Expression: %s\n", postfix);
    printf("Prefix Expression : %s\n", prefix);

    return 0;
}
