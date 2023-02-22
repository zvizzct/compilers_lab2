#include "keyword.h"
#include "literal.h"
#include "especial_character.h"
#include <unistd.h>
#include <fcntl.h>

int keywordIsDone(int state) {
    if (state == 17 || state == 18 || state == 19 || state == 20 || state == 21) {
        return 1;
    }
    return 0;
}

int literalIsDone(int state) {
    if (state == 2) {
        return 1;
    }
    return 0;
}

int EspecialCharacterIsDone(int state) {
    if (state == 1) {
        return 1;
    }
    return 0;
}

void buildToken(char* token, char token_lexeme[], char category[]) {
    int i,j;
    token[0] = '<';
    for (i = 0; token_lexeme[i] != '\0'; i++)
    {
        token[i+1] = token_lexeme[i];
    }
    i++;
    token[i] = ',';
    for (j = 0; category[j] != '\0'; j++)
    {
        token[i+j+1] = category[j];
    }
    j++;
    token[i+j] = '>';
    token[i+j+1] = '\0';
}

void printDebugMode(FILE* output_file, int* count_is_printed, int count_line, char* token) {
    if (!*count_is_printed) {
        fprintf(output_file, "%d ", count_line);
        printf("%d ", count_line);
        *count_is_printed = 1; 
    }
    printf("%s ", token);
}