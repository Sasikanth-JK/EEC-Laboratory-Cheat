#include<stdio.h>
#include<string.h>

int main()
{
    /* Transition table: rows = states, cols = input symbols (0 for 'a', 1 for 'b') */
    int transition[3][2] = {
        {1, 2}, /* q0: a->q1, b->q2 */
        {1, 1}, /* q1: a->q1, b->q1 */
        {2, 2}  /* q2: a->q2, b->q2 (trap) */
    };
    char input[100];
    int state = 0; /* start from q0 */
    int i, symbol;

    printf("Enter a string over {a, b}: ");
    scanf("%s", input);

    for (i = 0; i < strlen(input); i++)
    {
        if (input[i] == 'a')
            symbol = 0;
        else if (input[i] == 'b')
            symbol = 1;
        else
        {
            printf("Invalid input character '%c'.\n", input[i]);
            return 1;
        }
        state = transition[state][symbol]; /* state transition */
    }

    if (state == 1)
        printf("String is ACCEPTED by the DFA.\n");
    else
        printf("String is REJECTED by the DFA.\n");

    return 0;
}
