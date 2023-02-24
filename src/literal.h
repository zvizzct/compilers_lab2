#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NO_OF_STATES_LITERAL 4
#define NO_OF_SYMBOLS_LITERAL 2

int literal_transitions[NO_OF_STATES_LITERAL][NO_OF_SYMBOLS_LITERAL];
char alphabet[] = {'a','b','c','d','f','g','h','j','k','l','n','o','p','q','s','t','u','v','x','y','z',
                    'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
                    '0','1','2','3','4','5','6','7','8','9','{','}', '[', ']',';',',','(',')','+','-','/','*','<','>'};

/**
 * Initialize the transition table for literals
*/
void initLiteralTransitionTable()
{
    // 0 represents " and 1 any character from alphabet
    literal_transitions[0][0] = 1; // from state 0, with " it goes to state 1
    literal_transitions[0][1] = -1; // from state 0, with any character of the alphabet, it goes to state -1 (empty state)
    literal_transitions[1][0] = 2; // from state 1, with " it goes to state 2, the final state
    literal_transitions[1][1] = 1; // from state 1, with any character of alphabet, it stays to state 1
}

/**
 * Check whether an array al contain c
 * @param al the array
 * @param c the character to be checked
*/
int contains(char al[], char c) {
    for (int i = 0; i < strlen(al); i++)
    {
        if (al[i] == c) return 1;
    }
    return 0;
}

/**
 * Process the dfa
 * @param currentState the current state index of the dfa
 * @param symbol the next symbol
 * @return the next state index
*/
int getLiteralNextState(int currentState, char symbol)
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

    return literal_transitions[currentState][symbolIndex];
}

/**
 * Check if the dfa is done, it means if the dfa is in the state 2
 * @param state the current state of the dfa
*/
int literalIsDone(int state) {
    if (state == 2) {
        return 1;
    }
    return 0;
}