#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NO_OF_STATES_OPERATOR 1
#define NO_OF_SYMBOLS_OPERATOR 1

int operator_transitions[NO_OF_STATES_OPERATOR][NO_OF_SYMBOLS_OPERATOR];
char operator_characters[] = {'=','>','<','+','*','-','/'};

void initOperatorTransitionTable()
{
    operator_transitions[0][0] = 1;
}

/**
 * Check whether an array al contain c
*/
int contains4(char al[], char c) {
    for (int i = 0; i < strlen(al); i++)
    {
        if (al[i] == c) return 1;
    }
    return 0;
}

int getOperatorNextState(int currentState, char symbol)
{
    int symbolIndex;

    if (contains4(operator_characters, symbol))
    {
        symbolIndex = 0;
    }
    else
    {
        return -1;
    }

    return operator_transitions[currentState][symbolIndex];
}

/**
 * Check if the dfa is done, it means if the dfa is in the state 1
 * @param state the current state of the dfa
*/
int operatorIsDone(int state) {
    if (state == 1) {
        return 1;
    }
    return 0;
}
