#include "keyword.h"
#include "literal.h"
#include "especial_character.h"
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

int main(int argc, char const *argv[]) {
    char token_buffer[1000];
    int fd = open("test.c",O_RDWR, 0644);
    FILE *output_file = fopen("output.c", "w");
    char buff;
    int current_state_keyword = 0;
    int current_state_literal = 0;
    int current_state_especial_character = 0;
    char* token = malloc(100 * sizeof(char));
    char current_word[80] = "";
    int reset = 0; // boolean
    char previous_buff = 'a';
#if (OUTFORMAT == DEBUG)
    int count_line = 1;
    int count_is_printed = 0;
#endif
    
    initKeyWordTransitionTable();
    initLiteralTransitionTable();
    initEspecialCharacterTransitionTable();

    int i = 0;
    while (read(fd, &buff, 1) > 0)
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
        current_state_keyword = getKeyWordNextState(current_state_keyword, buff);
        current_state_literal = getLiteralNextState(current_state_literal, buff);
        current_state_especial_character = getEspecialCharacterNextState(current_state_especial_character, buff);
        if (current_state_keyword == -1 && current_state_literal == -1 && current_state_especial_character == -1
            && (buff == ' ' || buff == '\n')) {
            current_state_keyword = 0;
            current_state_literal = 0;
            current_state_especial_character = 0;
            i = 0; // Skip unregonize for now
        }

        // Check if one dfa is done, if yes build the corresponding token and write it in the file
        if(keywordIsDone(current_state_keyword)) {
            current_word[i] = '\0';
            buildToken(token, current_word, "CAT_KEYWORD");
        #if (OUTFORMAT == DEBUG)
            if (!count_is_printed) {
                fprintf(output_file, "%d ", count_line);
                printf("%d ", count_line);
                count_is_printed = 1; 
            }
            printf("%s ", token);
        #endif
            fprintf(output_file, "%s ", token);
            reset = 1;
        }
        else if(literalIsDone(current_state_literal)) {
            current_word[i] = '\0';
            buildToken(token, current_word, "CAT_LITERAL");
        #if (OUTFORMAT == DEBUG)
            if (!count_is_printed) {
                fprintf(output_file, "%d ", count_line);
                printf("%d ", count_line);
                count_is_printed = 1; 
            }
            printf("%s ", token);
        #endif
            fprintf(output_file, "%s ", token);
            reset = 1;
        }
        else if(EspecialCharacterIsDone(current_state_especial_character)) {
            current_word[i] = '\0';
            buildToken(token, current_word, "CAT_ESPECIAL_CHARACTER");
        #if (OUTFORMAT == DEBUG)
            if (!count_is_printed) {
                fprintf(output_file, "%d ", count_line);
                printf("%d ", count_line);
                count_is_printed = 1; 
            }
            printf("%s ", token);
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
            token = malloc(100 * sizeof(char));
            i = 0;
            reset = 0;
        }
        previous_buff = buff;
    }
    free(token);
    close(fd);
    fclose(output_file);
    return 0;
}
