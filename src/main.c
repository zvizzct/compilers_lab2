#include "scanner.h"
#include <unistd.h>
#include <fcntl.h>

#define RELEASE 0
#define DEBUG 1
#define OUTFORMAT DEBUG


int main(int argc, char const *argv[]) {
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
        else if(EspecialCharacterIsDone(current_state_especial_character)) {
            current_word[i] = '\0';
            buildToken(token, current_word, "CAT_ESPECIAL_CHARACTER");
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
