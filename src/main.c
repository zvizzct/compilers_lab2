#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 100
#define NO_OF_STATES 4
#define NO_OF_SYMBOLS 2

int transition[NO_OF_STATES][NO_OF_SYMBOLS];
char alphabet[] = {'a', 'b', 'c', 'd', 'A', 'B', 'C', 'D'};

// 0 represents " and 1 any character from alphabet
void initTransitionTable()
{
    transition[0][0] = 1; // from state 0, with " it goes to state 1
    transition[0][1] = 3; // from state 0, with any character of alphabet, it goes to state 3 (empty state)
    transition[1][0] = 2; // from state 1, with " it goes to state 2, the final state
    transition[1][1] = 1; // from state 1, with any character of alphabet, it stays to state 1
}

/**
 * Check whether an array al contain c
*/
int contains(char al[], char c) {
    for (int i = 0; i < strlen(al); i++)
    {
        if (al[i] == c) return 1;
    }
    return 0;
}

int getNextState(int currentState, char symbol)
{
    int symbolIndex;

    if (contains(alphabet, symbol))
    {
        symbolIndex = 1; // 1 represents any character from alphabet
    }
    else if (symbol == '"')
    {
        symbolIndex = 0; // 0 represents "
    }
    else
    {
        return -1;
    }

    return transition[currentState][symbolIndex];
}

int processString(char str[])
{
    int i, currentState, nextState;

    currentState = 0;

    for (i = 0; i < strlen(str); i++)
    {
        nextState = getNextState(currentState, str[i]);

        if (nextState == -1)
        {
            return 0;
        }
        else if (nextState == 2) {
            return 1; // 2 is the final state, it's done
        }

        currentState = nextState;
    }

    return 0;
}

int main()
{
    char str[MAX_LEN];

    initTransitionTable();

    printf("Enter a string: ");
    scanf("%s", str);

    if (processString(str))
    {
        printf("Accept\n");
    }
    else
    {
        printf("Reject\n");
    }
    

    return 0;
}