

#include <stdio.h>
#include <stdlib.h>
#include "src/utilsFiles.h"

FILE *file;
char *fileContent;

char *setUpfileContent(char *fileName)
{

    // Open file
    file = openFile(fileName);

    // Check if file was successfully opened
    if (file == NULL)
    {
        return "error";
    }

    // Read file
    fileContent = readFile(file);

    return fileContent;
}

void outputMessage(char *outFileName)
{

    printf("\n");
    printf("-------------------------------------------------------------\n");
    printf("-------- scanned file saved in %s --------\n", outFileName);
    printf("-------------------------------------------------------------\n");
}

void flagHelp()
{
    // TODO: add help flag
}

int main(int argc, char **argv)
{
    // Variables
    char *fileName, *outFileName;
    char *flag1 = NULL, *flag2 = NULL, *flag3 = NULL;
    char *preprocesedContent;
    int fd;

    fileContent = setUpfileContent(fileName);

    // Parse

    // write prepcocesed content to file
    outFileName = writeFile(fileName, preprocesedContent);

    // Print output message
    outputMessage(outFileName);

    // Free memory and close file
    free(fileContent);

    // Close file
    fclose(file);
}