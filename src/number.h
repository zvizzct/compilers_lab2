#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NO_OF_STATES_NUMBER 2
#define NO_OF_SYMBOLS_NUMBER 2

int number_transitions[NO_OF_STATES_NUMBER][NO_OF_SYMBOLS_NUMBER];
char numbers[] = {'0','1','2','3','4','5','6','7','8','9'};

// 0 represents numbers and 1 ' ' the space character
void initNumberTransitionTable()
{
    number_transitions[0][0] = 1; // from state 0, with " it goes to state 1
    number_transitions[0][1] = -1; // from state 0, with any character of alphabet, it goes to state 3 (empty state)
    number_transitions[1][0] = 1; // from state 1, with " it goes to state 2, the final state
    number_transitions[1][1] = 2; // from state 1, with any character of alphabet, it stays to state 1
}

/**
 * Check whether an array al contain c
*/
int contains5(char al[], char c) {
    for (int i = 0; i < strlen(al); i++)
    {
        if (al[i] == c) return 1;
    }
    return 0;
}

int getNumberNextState(int currentState, char symbol)
{
    int symbolIndex;

    if (contains5(numbers, symbol))
    {
        symbolIndex = 0; // 1 represents any character from alphabet
    }
    else if (symbol == ' ' || symbol == '\n' || symbol == ';') {
        symbolIndex = 1;
    }
    else
    {
        return -1;
    }

    return number_transitions[currentState][symbolIndex];
}

/**
 * Check if the dfa is done, it means if the dfa is in the state 2
 * @param state the current state of the dfa
*/
int numberIsDone(int state) {
    if (state == 2) {
        return 1;
    }
    return 0;
}