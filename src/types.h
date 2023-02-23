#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NO_OF_STATES_TYPE 18
#define NO_OF_SYMBOLS_TYPE 14

int type_transitions[NO_OF_STATES_TYPE][NO_OF_SYMBOLS_TYPE];
char type_letters[] = {'h','i','e','l','a','n','r','t','u','d','o','b','c','v'};

// i =0, f = 1, e = 2,h=3,l = 4, s =5,m=6,a=7,n=8,r=9,t=10,u=11,w=12
void initTypeTransitionTable()
{
    for (int i = 0; i < NO_OF_STATES_TYPE; i++)
    {
        for (int j = 0; j < NO_OF_SYMBOLS_TYPE; j++)
        {
            if (i == 0)
            {
                if (type_letters[j] == 'i') type_transitions[i][j] = 1;
                else if (type_letters[j] == 'd') type_transitions[i][j] = 4;
                else if (type_letters[j] == 'c') type_transitions[i][j] = 10;
                else if (type_letters[j] == 'v') type_transitions[i][j] = 14;
                else type_transitions[i][j] = -1;
            }
            else if (i == 1)
            {
                if (type_letters[j] == 'n') type_transitions[i][j] = 2;
                else type_transitions[i][j] = -1;
            }if (i == 2)
            {
                if (type_letters[j] == 't') type_transitions[i][j] = 3;
                else type_transitions[i][j] = -1;
            }if (i == 3)
            {
                type_transitions[i][j] = -1;
            }if (i == 4)
            {
                if (type_letters[j] == 'o') type_transitions[i][j] = 5;
                else type_transitions[i][j] = -1;
            }if (i == 5)
            {
                if (type_letters[j] == 'u') type_transitions[i][j] =6;
                else type_transitions[i][j] = -1;
            }if (i == 6)
            {
                if (type_letters[j] == 'b') type_transitions[i][j] = 7;
                else type_transitions[i][j] = -1;
            }if (i == 7)
            {
                if (type_letters[j] == 'l') type_transitions[i][j] = 8;
                else type_transitions[i][j] = -1;
            }if (i == 8)
            {
                if (type_letters[j] == 'e') type_transitions[i][j] = 9;
                else type_transitions[i][j] = -1;
            }if (i == 9)
            {
                type_transitions[i][j] = -1;
            }if (i == 10)
            {
                if (type_letters[j] == 'h') type_transitions[i][j] = 11;
                else type_transitions[i][j] = -1;
            }if (i == 11)
            {
                if (type_letters[j] == 'a') type_transitions[i][j] = 12;
                else type_transitions[i][j] = -1;
            }if (i == 12)
            {
                if (type_letters[j] == 'r') type_transitions[i][j] = 13;
                else type_transitions[i][j] = -1;
            }if (i == 13)
            {
                type_transitions[i][j] = -1;
            }if (i == 14)
            {
                if (type_letters[j] == 'o') type_transitions[i][j] = 15;
                else type_transitions[i][j] = -1;
            }if (i == 15)
            {
                if (type_letters[j] == 'i') type_transitions[i][j] = 16;
                else type_transitions[i][j] = -1;
            }if (i == 16)
            {
                if (type_letters[j] == 'd') type_transitions[i][j] = 17;
                else type_transitions[i][j] = -1;
            }if (i == 17)
            {
                type_transitions[i][j] = -1;
            }
        }
    }
}

int getTypeNextState(int currentState, char symbol)
{
    int symbolIndex;
    if (symbol == 'h')
    {
        symbolIndex = 0; // 0 represents "
    }
    else if (symbol == 'i')
    {
        symbolIndex = 1; // 0 represents "
    }
    else if (symbol == 'e')
    {
        symbolIndex = 2; // 0 represents "
    }
    else if (symbol == 'l')
    {
        symbolIndex = 3; // 0 represents "
    }
    else if (symbol == 'a')
    {
        symbolIndex = 4; // 0 represents "
    }
    else if (symbol == 'n')
    {
        symbolIndex = 5; // 0 represents "
    }
    else if (symbol == 'r')
    {
        symbolIndex = 6; // 0 represents "
    }
    else if (symbol == 't')
    {
        symbolIndex = 7; // 0 represents "
    }
    else if (symbol == 'u')
    {
        symbolIndex = 8; // 0 represents "
    }
    else if (symbol == 'd')
    {
        symbolIndex = 9; // 0 represents "
    }
    else if (symbol == 'o')
    {
        symbolIndex = 10; // 0 represents "
    }
    else if (symbol == 'b')
    {
        symbolIndex = 11; // 0 represents "
    }
    else if (symbol == 'c')
    {
        symbolIndex = 12; // 0 represents "
    }
    else if (symbol == 'v')
    {
        symbolIndex = 13; // 0 represents "
    }
    else
    {
        return -1;
    }

    return type_transitions[currentState][symbolIndex];
}
