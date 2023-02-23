#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NO_OF_STATES_LITERAL 4
#define NO_OF_SYMBOLS_LITERAL 2

int literal_transitions[NO_OF_STATES_LITERAL][NO_OF_SYMBOLS_LITERAL];
char alphabet[] = {'a','b','c','d','f','g','h','j','k','l','n','o','p','q','s','t','u','v','x','y','z',
                    'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
                    '0','1','2','3','4','5','6','7','8','9','{','}', '[', ']',';',',','(',')','+','-','/','*','<','>'};

// 0 represents " and 1 any character from alphabet
void initLiteralTransitionTable()
{
    literal_transitions[0][0] = 1; // from state 0, with " it goes to state 1
    literal_transitions[0][1] = -1; // from state 0, with any character of alphabet, it goes to state 3 (empty state)
    literal_transitions[1][0] = 2; // from state 1, with " it goes to state 2, the final state
    literal_transitions[1][1] = 1; // from state 1, with any character of alphabet, it stays to state 1
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