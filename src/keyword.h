#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 100
#define NO_OF_STATES_KEYWORD 21
#define NO_OF_SYMBOLS_KEYWORD 14

int keyword_transitions[NO_OF_STATES_KEYWORD][NO_OF_SYMBOLS_KEYWORD];
char keyword_letters[] = {'w','h','i','e','f','l','s','m','a','n','r','t','u'};

// 0 represents " and 1 any character from alphabet
// i =0, f = 1, e = 2,h=3,l = 4, s =5,m=6,a=7,n=8,r=9,t=10,u=11,w=12
void initKeyWordTransitionTable()
{
    for (int i = 0; i < NO_OF_STATES_KEYWORD; i++)
    {
        for (int j = 0; j < NO_OF_SYMBOLS_KEYWORD; j++)
        {
            if (i == 0)
            {
                if (keyword_letters[j] == 'i') keyword_transitions[i][j] = 1;
                else if (keyword_letters[j] == 'e') keyword_transitions[i][j] = 2;
                else if (keyword_letters[j] == 'm') keyword_transitions[i][j] = 5;
                else if (keyword_letters[j] == 'r') keyword_transitions[i][j] = 8;
                else if (keyword_letters[j] == 'w') keyword_transitions[i][j] = 13;
                else keyword_transitions[i][j] = -1;
            }
            else if (i == 1)
            {
                if (keyword_letters[j] == 'f') keyword_transitions[i][j] = 17;
                else keyword_transitions[i][j] = -1;
            }if (i == 2)
            {
                if (keyword_letters[j] == 'l') keyword_transitions[i][j] = 3;
                else keyword_transitions[i][j] = -1;
            }if (i == 3)
            {
                if (keyword_letters[j] == 's') keyword_transitions[i][j] = 4;
                else keyword_transitions[i][j] = -1;
            }if (i == 4)
            {
                if (keyword_letters[j] == 'e') keyword_transitions[i][j] = 18;
                else keyword_transitions[i][j] = -1;
            }if (i == 5)
            {
                if (keyword_letters[j] == 'a') keyword_transitions[i][j] =6;
                else keyword_transitions[i][j] = -1;
            }if (i == 6)
            {
                if (keyword_letters[j] == 'i') keyword_transitions[i][j] = 7;
                else keyword_transitions[i][j] = -1;
            }if (i == 7)
            {
                if (keyword_letters[j] == 'n') keyword_transitions[i][j] = 19;
                else keyword_transitions[i][j] = -1;
            }if (i == 8)
            {
                if (keyword_letters[j] == 'e') keyword_transitions[i][j] = 9;
                else keyword_transitions[i][j] = -1;
            }if (i == 9)
            {
                if (keyword_letters[j] == 't') keyword_transitions[i][j] = 10;
                else keyword_transitions[i][j] = -1;
            }if (i == 10)
            {
                if (keyword_letters[j] == 'u') keyword_transitions[i][j] = 11;
                else keyword_transitions[i][j] = -1;
            }if (i == 11)
            {
                if (keyword_letters[j] == 'r') keyword_transitions[i][j] = 12;
                else keyword_transitions[i][j] = -1;
            }if (i == 12)
            {
                if (keyword_letters[j] == 'n') keyword_transitions[i][j] = 20;
                else keyword_transitions[i][j] = -1;
            }if (i == 13)
            {
                if (keyword_letters[j] == 'h') keyword_transitions[i][j] = 14;
                else keyword_transitions[i][j] = -1;
            }if (i == 14)
            {
                if (keyword_letters[j] == 'i') keyword_transitions[i][j] = 15;
                else keyword_transitions[i][j] = -1;
            }if (i == 15)
            {
                if (keyword_letters[j] == 'l') keyword_transitions[i][j] = 16;
                else keyword_transitions[i][j] = -1;
            }if (i == 16)
            {
                if (keyword_letters[j] == 'e') keyword_transitions[i][j] = 21;
                else keyword_transitions[i][j] = -1;
            }if (i == 17 || i == 18 || i == 19 || i == 20 || i == 21)
            {
                if (j == 13) keyword_transitions[i][j] = 22;
                else keyword_transitions[i][j] = -1;
            }
        }
    }
}

int getKeyWordNextState(int currentState, char symbol)
{
    int symbolIndex;

    if (symbol == 'w')
    {
        symbolIndex = 0; // 0 represents "
    }
    else if (symbol == 'h')
    {
        symbolIndex = 1; // 0 represents "
    }
    else if (symbol == 'i')
    {
        symbolIndex = 2; // 0 represents "
    }
    else if (symbol == 'e')
    {
        symbolIndex = 3; // 0 represents "
    }
    else if (symbol == 'f')
    {
        symbolIndex = 4; // 0 represents "
    }
    else if (symbol == 'l')
    {
        symbolIndex = 5; // 0 represents "
    }
    else if (symbol == 's')
    {
        symbolIndex = 6; // 0 represents "
    }
    else if (symbol == 'm')
    {
        symbolIndex = 7; // 0 represents "
    }
    else if (symbol == 'a')
    {
        symbolIndex = 8; // 0 represents "
    }
    else if (symbol == 'n')
    {
        symbolIndex = 9; // 0 represents "
    }
    else if (symbol == 'r')
    {
        symbolIndex = 10; // 0 represents "
    }
    else if (symbol == 't')
    {
        symbolIndex = 11; // 0 represents "
    }
    else if (symbol == 'u')
    {
        symbolIndex = 12; // 0 represents "
    }
    else if (symbol == ' ' || symbol == '\n' || symbol == ';')
    {
        symbolIndex = 13; // 0 represents "
    }
    else
    {
        return -1;
    }

    return keyword_transitions[currentState][symbolIndex];
}
