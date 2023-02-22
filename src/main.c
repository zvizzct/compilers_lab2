#include "keyword.h"
#include "literal.h"
#include <unistd.h>
#include <fcntl.h>

int keywordIsDone(int state) {
    if (state == 17 || state == 18 || state == 19 || state == 20 || state == 21) {
        return 1; // 2 is the final state, it's done
    }
    return 0;
}

int literalIsDone(int state) {
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
    for (j = 1; category[j-1] != '\0'; j++)
    {
        token[i+j] = category[j-1];
    }
    token[i+j] = '>';
    token[i+j+1] = '\0';
}

int main(int argc, char const *argv[]) {
    char token_buffer[1000];
    int fd = open("test.c",O_RDWR, 0644);
    char buff;
    int current_state_keyword = 0;
    int current_state_literal = 0;
    char* token = malloc(sizeof(char));
    char current_word[80] = "";
    
    initKeyWordTransitionTable();
    initLiteralTransitionTable();

    int i = 0;
    while (read(fd, &buff, 1) > 0)
    {
        if (buff != ' ') {
            current_word[i] = buff;
            i++;
        }
        current_state_keyword = getKeyWordNextState(current_state_keyword, buff);
        current_state_literal = getLiteralNextState(current_state_literal, buff);
        if (current_state_keyword == -1 && current_state_literal == -1) i = 0; // Skip unregonize for now
        if (current_state_keyword == -1) current_state_keyword = 0;
        if (current_state_literal == -1) current_state_literal = 0;
        if(keywordIsDone(current_state_keyword)) {
            current_word[i] = '\0';
            buildToken(token, current_word, "CAT_KEYWORD");
            printf("token = %s\n", token);

            // Reinitialize variables
            free(token);
            current_state_keyword = 0;
            current_state_literal = 0;
            token = malloc(sizeof(char));
            i = 0;
        }
        else if(literalIsDone(current_state_literal)) {
            current_word[i] = '\0';
            buildToken(token, current_word, "CAT_LITERAL");
            printf("token = %s\n", token);

            // Reinitialize variables
            free(token);
            current_state_keyword = 0;
            current_state_literal = 0;
            token = malloc(sizeof(char));
            i = 0;
        }
    }
    free(token);
    close(fd);
    return 0;
}
