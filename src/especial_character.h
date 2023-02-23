#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NO_OF_STATES_ESPECIAL 1
#define NO_OF_SYMBOLS_ESPECIAL 1
#define ALPHABET_SIZE 8

int especial_character_transitions[NO_OF_STATES_ESPECIAL][NO_OF_SYMBOLS_ESPECIAL];
char especial_characters[] = {'(',')','{','}','[',']',';',','};

void initEspecialCharacterTransitionTable()
{
    especial_character_transitions[0][0] = 1;
}

/**
 * Check whether an array al contain c
*/
int contains2(char al[], char c, int length_al) {
    for (int i = 0; i < length_al; i++)
    {
        if (al[i] == c) return 1;
    }
    return 0;
}

int getEspecialCharacterNextState(int currentState, char symbol)
{
    int symbolIndex;

    if (contains2(especial_characters, symbol, ALPHABET_SIZE))
    {
        symbolIndex = 0;
    }
    else
    {
        return -1;
    }

    return especial_character_transitions[currentState][symbolIndex];
}
