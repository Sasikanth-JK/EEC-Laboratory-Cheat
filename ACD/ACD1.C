#include<stdio.h>
#include<string.h>

int main()
{
    char str[100];
    int state = 0; /* q0 */
    int i;
    char ch;

    printf("Enter a string over {a, b}: ");
    scanf("%s", str);

    for (i = 0; i < strlen(str); i++)
    {
        ch = str[i];
        switch (state)
        {
            case 0: /* q0 */
                if (ch == 'a')
                    state = 1; /* move to q1 */
                else
                    state = 2; /* move to trap q2 */
                break;
            case 1: /* q1 */
                if (ch == 'a' || ch == 'b')
                    state = 1; /* stay in q1 */
                break;
            case 2: /* trap state q2 */
                state = 2; /* remain in q2 */
                break;
        }
    }

    if (state == 1)
        printf("String is accepted by the DFA.\n");
    else
        printf("String isrejected by the DFA.\n");

    return 0;
}
