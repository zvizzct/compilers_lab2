#include "scanner.h"
#include "utilsFiles.h"
#include <unistd.h>
#include <fcntl.h>

void outputMessage(char *output_file_name)
{
    printf("\n");
    printf("-------------------------------------------------------------\n");
    printf("-------- scanned file saved in %s --------\n", output_file_name);
    printf("-------------------------------------------------------------\n");
}

void flagHelp()
{
    printf("\nScanner app usage:\n");
    printf("\t./scanner [filename]\n");
}

int main(int argc, char const *argv[]) {

    if (argc == 1 || argc > 2) flagHelp();
    else {
        // Setup file names
        char* input_file_name = malloc(30 * sizeof(char));
        sprintf(input_file_name, "%s", argv[1]);
        char* output_file_name = malloc(30 * sizeof(char));
        getOutputFileName(input_file_name, output_file_name);

        // Open files
        FILE *input_file = openFile(input_file_name, "r");
        if (input_file == NULL) return 1;
        FILE *output_file;
        if (DEBUG == ON) output_file = openFile(output_file_name, "w");
        else output_file = stdout;

        // process function
        process(input_file, output_file);

        outputMessage(output_file_name);

        // Free dynamic memory and close files
        free(input_file_name);
        free(output_file_name);
        fclose(input_file);
        fclose(output_file);
    }
    return 0;
}
