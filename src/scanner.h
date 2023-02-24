/* 
    Scanner implementation. Note that in this file, the first dfas means that the dfas which need
    to process the next character to end. The second dfas are the others 
*/

#include "keyword.h"
#include "literal.h"
#include "especial_character.h"
#include "identifier.h"
#include "types.h"
#include "operator.h"
#include "number.h"
#include <unistd.h>
#include <fcntl.h>

#define RELEASE 0
#define DEBUG 1
#define OUTFORMAT DEBUG

int keywordIsDone(int state) {
    if (state == 22) {
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

int operatorIsDone(int state) {
    if (state == 1) {
        return 1;
    }
    return 0;
}

int numberIsDone(int state) {
    if (state == 2) {
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
    initOperatorTransitionTable();
    initNumberTransitionTable();
}
/**
 * reset all variables to their initial state
*/
void reset(char* token, int* state_keyword, int* state_literal, int* state_especial_character,
            int* state_identifier, int* state_type, int* state_operator, int* state_number,
            int* index_current_word, int* empty_line, int first_dfa_check) {
    if (first_dfa_check) {
        *state_keyword = -1;
        *state_identifier = -1;
        *state_number = -1;
    }
    else {
        *state_keyword = 0;
        *state_identifier = 0;
        state_number = 0;
    }
    *state_literal = 0;
    *state_especial_character = 0;
    *state_type = 0;
    *state_operator = 0;
    free(token);
    token = malloc(100 * sizeof(char));
    *index_current_word = 0;
    *empty_line = 0;
}
/**
 *@return the dfa's index if a dfa is done, else -1
*/
int dfasDone(int dfas[][1], int first_dfa_check) {
    if (first_dfa_check) {
        for (int i = 0; i < 3; i++)
        {
            if (i == 0 && numberIsDone(dfas[i][0])) return i;
            else if (i == 1 && identifierIsDone(dfas[i][0])) return i;
            else if (i == 2 && keywordIsDone(dfas[i][0])) return i;
        }
        return -1;
    }
    else {
        for (int i = 0; i < 4; i++)
        {
            if (i == 0 && literalIsDone(dfas[i][0])) return i;
            else if (i == 1 && especialCharacterIsDone(dfas[i][0])) return i;
            else if (i == 2 && typeIsDone(dfas[i][0])) return i;
            else if (i == 3 && operatorIsDone(dfas[i][0])) return i;
        }
        return -1;
    }
}

char* getCategory(int dfa_index, int first_dfa_check) {
    if (first_dfa_check) {
        if (dfa_index == 0) return "CAT_NUMBER";
        else if (dfa_index == 1) return "CAT_IDENTIFIER";
        else return "CAT_KEYWORD";
    }
    else {
        if (dfa_index == 0) return "CAT_LITERAL";
        else if (dfa_index == 1) return "CAT_ESPECIAL_CHARACTER";
        else if (dfa_index == 2) return "CAT_TYPE";
        else return "CAT_OPERATOR";
    }
}

void process(FILE* input_file, FILE* output_file) {
    // Initialize variables
    char buff;
    int first_dfas[3][1] = {{0}, {0}, {0}}; // 0 -> numbers, 1 -> identifiers, 2 -> keywords
    int second_dfas[4][1] = {{0}, {0}, {0}}; // 0 -> literals, 1 -> especial characters, 2 -> types, 3 -> operators 
    char* token = malloc(100 * sizeof(char));
    char current_word[80] = ""; // store the word we are processing
    char previous_buff = 'a';
#if (OUTFORMAT == DEBUG)
    int count_line = 1;
    int count_is_printed = 0; // boolean
#endif
    int empty_line = 1; // boolean
    int dfa_done_index = -1;
    
    initTransitionTables();

    int i = 0;
    while (fread(&buff, 1, 1,input_file) > 0)
    {
        // Process next state of each first dfas
        if (first_dfas[0][0] != -1) first_dfas[0][0] = getNumberNextState(first_dfas[0][0], buff);
        if (first_dfas[1][0] != -1) first_dfas[1][0] = getIdentifierNextState(first_dfas[1][0], buff);
        if (first_dfas[2][0] != -1) first_dfas[2][0] = getKeyWordNextState(first_dfas[2][0], buff);

        // Check if one of the first dfas is done and fill the output file
        dfa_done_index = dfasDone(first_dfas, 1);
        if (dfa_done_index != -1)
        {
            current_word[i] = '\0';
            buildToken(token, current_word, getCategory(dfa_done_index, 1));
        #if (OUTFORMAT == DEBUG)
            printDebugMode(output_file, &count_is_printed, count_line, token);
        #endif
            fprintf(output_file, "%s ", token);
            reset(token, &first_dfas[0][0], &second_dfas[0][0], &second_dfas[1][0],
                &first_dfas[1][0], &second_dfas[2][0], &second_dfas[3][0], &first_dfas[2][0],
                &i, &empty_line, 1);
        }
        
        // If all the dfas failed and the current character is ';', reset the current word and 
        // the especial character state to process the ';'
        if (buff == ';' || first_dfas[0][0] == -1 && second_dfas[0][0] == -1 && second_dfas[1][0] == -1 
            && first_dfas[1][0] == -1 && second_dfas[2][0] == -1 && second_dfas[3][0] == -1
            && first_dfas[2][0] == -1) {
            i = 0;
            second_dfas[1][0] = 0;
        }

        // Store each characters in a buffer in order to get the lexeme token
        current_word[i] = buff;
        i++;
        
        // Process next state of each second dfas
        if (second_dfas[0][0] != -1) second_dfas[0][0] = getLiteralNextState(second_dfas[0][0], buff);
        if (second_dfas[1][0] != -1) second_dfas[1][0] = getEspecialCharacterNextState(second_dfas[1][0], buff);
        if (second_dfas[2][0]!= -1) second_dfas[2][0] = getTypeNextState(second_dfas[2][0], buff);
        if (second_dfas[3][0] != -1) second_dfas[3][0] = getOperatorNextState(second_dfas[3][0], buff);

        // If all the dfas failed and the current character is '\n' or ' ', reset the current word,
        // the empty line variable and all the states. In addition, print the '\n' if the current 
        // character is '\n', the previous one different of '\n' and there is at least one token on
        // the current line that we are processing,to avoid empty lines in the output file. Allow one
        // empty line between each line of tokens if debug mode is activated
        if (first_dfas[0][0] == -1 && second_dfas[0][0] == -1 && second_dfas[1][0] == -1 
            && first_dfas[1][0] == -1 && second_dfas[2][0] == -1 && second_dfas[3][0] == -1
            && first_dfas[2][0] == -1 && (buff == ' ' || buff == '\n')) 
        {
            for (int j = 0; j < 3; j++) first_dfas[j][0] = 0;
            for (int j = 0; j < 4; j++) second_dfas[j][0] = 0;

            if (buff == '\n' && previous_buff != '\n' && !empty_line) {
                fprintf(output_file,"\n");
            #if (OUTFORMAT == DEBUG)
                fprintf(output_file,"\n");
                printf("\n");
                printf("\n");
            #endif
                empty_line = 1;
            }
            i = 0; // Skip unregonize for now
        }

        // Check if one of the second dfas is done and fill the output file 
        dfa_done_index = dfasDone(second_dfas, 0);
        if (dfa_done_index != -1)
        {
            current_word[i] = '\0';
            buildToken(token, current_word, getCategory(dfa_done_index, 0));
        #if (OUTFORMAT == DEBUG)
            printDebugMode(output_file, &count_is_printed, count_line, token);
        #endif
            fprintf(output_file, "%s ", token);
            reset(token, &first_dfas[0][0], &second_dfas[0][0], &second_dfas[1][0],
                &first_dfas[1][0], &second_dfas[2][0], &second_dfas[3][0], &first_dfas[2][0],
                &i, &empty_line, 0);
        }

        // Keep a track of the previous character to avoid printing too much '\n' in the output file if the
        // input file has 3 empty lines for example
        previous_buff = buff;

        // if the debug mode is activated, increment the current line number each time the buffer is equal to '\n'
        // and set the count_is_printed to false (0)
    #if (OUTFORMAT == DEBUG)
        if (buff == '\n') {
            count_line++;
            count_is_printed = 0;
        }
    #endif
    }

    // For the last word of the file
    buff = '\n';
    if (first_dfas[0][0] != -1) first_dfas[0][0] = getNumberNextState(first_dfas[0][0], buff);
    if (first_dfas[1][0] != -1) first_dfas[1][0] = getIdentifierNextState(first_dfas[1][0], buff);
    if (first_dfas[2][0] != -1) first_dfas[2][0] = getKeyWordNextState(first_dfas[2][0], buff);
    dfa_done_index = dfasDone(first_dfas, 1);
    if (dfa_done_index != -1)
    {
        current_word[i] = '\0';
        buildToken(token, current_word, getCategory(dfa_done_index, 1));
    #if (OUTFORMAT == DEBUG)
        printDebugMode(output_file, &count_is_printed, count_line, token);
    #endif
        fprintf(output_file, "%s ", token);
        reset(token, &first_dfas[0][0], &second_dfas[0][0], &second_dfas[1][0],
            &first_dfas[1][0], &second_dfas[2][0], &second_dfas[3][0], &first_dfas[2][0],
            &i, &empty_line, 1);
    }
}