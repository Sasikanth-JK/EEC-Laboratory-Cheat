#include<stdio.h>
#include<string.h>

#define MAX 20

int nfa[10][2][10]; /* nfa[state][input][list of next states] */
int dfa[100][2];    /* dfa[state][input] = next DFA state */
int dfa_states[100][10]; /* stores NFA states in each DFA state */
int dfa_state_count = 0;

int is_same_set(int *a, int *b)
{
    int i;
    for (i = 0; i < 10; i++)
        if (a[i] != b[i]) return 0;
    return 1;
}

int is_new_state(int *set)
{
    int i;
    for (i = 0; i < dfa_state_count; i++)
    {
        if (is_same_set(dfa_states[i], set)) return i;
    }
    return -1;
}

void print_set(int *set)
{
    int i;
    printf("{");
    for (i = 0; i < 10; i++)
    {
        if (set[i] == 1)
            printf("q%d ", i);
    }
    printf("}");
}

int main()
{
    int nfa_state_count, trans, state, input, dest, i, j, k;
    int queue[100], front = 0, rear = 0;
    int visited[100] = {0};
    int initial[10] = {0};
    int current, index;
    int new_state[10];

    printf("Enter number of NFA states: ");
    scanf("%d", &nfa_state_count);

    /* Initialize NFA transitions */
    for (i = 0; i < nfa_state_count; i++)
    {
        for (j = 0; j < 2; j++)
        {
            printf("Enter number of transitions from q%d on input %d: ", i, j);
            scanf("%d", &trans);
            printf("Enter destination states: ");
            for (k = 0; k < trans; k++)
            {
                scanf("%d", &dest);
                nfa[i][j][k] = dest;
            }
            nfa[i][j][trans] = -1; /* end of list */
        }
    }

    /* Start subset construction */
    /* Start with state {0} */
    initial[0] = 1; /* q0 */
    memcpy(dfa_states[0], initial, sizeof(initial));
    queue[rear++] = 0;
    dfa_state_count = 1;

    while (front < rear)
    {
        current = queue[front++];
        for (input = 0; input < 2; input++)
        {
            for (i = 0; i < 10; i++) new_state[i] = 0;

            for (i = 0; i < nfa_state_count; i++)
            {
                if (dfa_states[current][i] == 1)
                {
                    for (j = 0; nfa[i][input][j] != -1; j++)
                    {
                        new_state[nfa[i][input][j]] = 1;
                    }
                }
            }
            index = is_new_state(new_state);
            if (index == -1)
            {
                memcpy(dfa_states[dfa_state_count], new_state, sizeof(new_state));
                dfa[current][input] = dfa_state_count;
                queue[rear++] = dfa_state_count;
                dfa_state_count++;
            }
            else
            {
                dfa[current][input] = index;
            }
        }
    }

    /* Print DFA transition table */
    printf("\nDFA Transition Table:\n");
    printf("State\t0\t1\n");
    for (i = 0; i < dfa_state_count; i++)
    {
        print_set(dfa_states[i]);
        printf("\t%d\t%d\n", dfa[i][0], dfa[i][1]);
    }

    return 0;
}
