#include "keyword.h"
#include "literal.h"
#include "especial_character.h"
#include "identifier.h"
#include "types.h"
#include <unistd.h>
#include <fcntl.h>

#define RELEASE 0
#define DEBUG 1
#define OUTFORMAT DEBUG

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

int especialCharacterIsDone(int state) {
    if (state == 1) {
        return 1;
    }
    return 0;
}

int identifierIsDone(int state) {
    if (state == 2) {
        return 1;
    }
    return 0;
}

int typeIsDone(int state) {
    if (state == 3 || state == 9 || state == 13 || state == 17) {
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

void initTransitionTables() {
    initKeyWordTransitionTable();
    initLiteralTransitionTable();
    initEspecialCharacterTransitionTable();
    initIdentifierTransitionTable();
    initTypeTransitionTable();
}

void process(FILE* input_file, FILE* output_file) {
    char buff;
    int current_state_keyword = 0;
    int current_state_literal = 0;
    int current_state_especial_character = 0;
    int current_state_identifier = 0;
    int current_state_type = 0;
    char* token = malloc(100 * sizeof(char));
    char current_word[80] = "";
    int reset = 0; // boolean
    char previous_buff = 'a';
#if (OUTFORMAT == DEBUG)
    int count_line = 1;
    int count_is_printed = 0; // boolean
#endif
    
    initTransitionTables();

    int i = 0;
    while (fread(&buff, 1, 1,input_file) > 0)
    {
        if (buff == '\n' && previous_buff != '\n') {
            fprintf(output_file, "\n");
        #if (OUTFORMAT == DEBUG)
            fprintf(output_file, "\n");
            printf("\n");
            printf("\n");
        #endif
        }
        else if (buff != ' ') {
            current_word[i] = buff;
            i++;
        }
    #if (OUTFORMAT == DEBUG)
        if (buff == '\n') {
            count_line++;
            count_is_printed = 0;
        }
    #endif   
        if (current_state_keyword != -1) current_state_keyword = getKeyWordNextState(current_state_keyword, buff);
        if (current_state_literal != -1) current_state_literal = getLiteralNextState(current_state_literal, buff);
        if (current_state_especial_character != -1) current_state_especial_character = getEspecialCharacterNextState(current_state_especial_character, buff);
        if (current_state_identifier != -1) current_state_identifier = getIdentifierNextState(current_state_identifier, buff);
        if (current_state_type != -1) current_state_type = getTypeNextState(current_state_type, buff);
        if (current_state_keyword == -1 && current_state_literal == -1 && current_state_especial_character == -1 
            && current_state_identifier == -1 && (buff == ' ' || buff == '\n')) {
            current_state_keyword = 0;
            current_state_literal = 0;
            current_state_especial_character = 0;
            current_state_identifier = 0;
            current_state_type = 0;
            i = 0; // Skip unregonize for now
        }

        // Check if one dfa is done, if yes build the corresponding token and write it in the file
        if(keywordIsDone(current_state_keyword)) {
            current_word[i] = '\0';
            buildToken(token, current_word, "CAT_KEYWORD");
        #if (OUTFORMAT == DEBUG)
            printDebugMode(output_file, &count_is_printed, count_line, token);
        #endif
            fprintf(output_file, "%s ", token);
            reset = 1;
        }
        else if(literalIsDone(current_state_literal)) {
            current_word[i] = '\0';
            buildToken(token, current_word, "CAT_LITERAL");
        #if (OUTFORMAT == DEBUG)
            printDebugMode(output_file, &count_is_printed, count_line, token);
        #endif
            fprintf(output_file, "%s ", token);
            reset = 1;
        }
        else if(especialCharacterIsDone(current_state_especial_character)) {
            current_word[i] = '\0';
            buildToken(token, current_word, "CAT_ESPECIAL_CHARACTER");
        #if (OUTFORMAT == DEBUG)
            printDebugMode(output_file, &count_is_printed, count_line, token);
        #endif
            fprintf(output_file, "%s ", token);
            reset = 1;
        }
        else if(identifierIsDone(current_state_identifier)) {
            current_word[i] = '\0';
            buildToken(token, current_word, "CAT_IDENTIFIER");
        #if (OUTFORMAT == DEBUG)
            printDebugMode(output_file, &count_is_printed, count_line, token);
        #endif
            fprintf(output_file, "%s ", token);
            reset = 1;
        }
        else if(typeIsDone(current_state_type)) {
            current_word[i] = '\0';
            buildToken(token, current_word, "CAT_TYPE");
        #if (OUTFORMAT == DEBUG)
            printDebugMode(output_file, &count_is_printed, count_line, token);
        #endif
            fprintf(output_file, "%s ", token);
            reset = 1;
        }

        // if a dfa is done, we reset all variables we need to process the next word/token
        if (reset) {
            free(token);
            current_state_keyword = 0;
            current_state_literal = 0;
            current_state_especial_character = 0;
            current_state_identifier = 0;
            current_state_type = 0;
            token = malloc(100 * sizeof(char));
            i = 0;
            reset = 0;
        }
        previous_buff = buff;
    }
    free(token);
}