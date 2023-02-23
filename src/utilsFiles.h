
/*
 * @file utilsFiles.h
 * @brief File containing the function declarations for file handling
 */

#include <stdio.h>
#include <stdlib.h> //

/**
 * @brief Open a file with a provided name
 *
 * @param fileName The name of the file to open
 * @return FILE* Pointer to the opened file, or NULL if the file does not exist or no file name was provided
 */
FILE *openFile(char *fileName, char* openMode)
{
    // Check if fileName is NULL, if it is, print an error message and return NULL
    if (fileName == NULL)
    {
        return NULL;
    }
    // Try to open the file with the given fileName in read mode
    FILE *fptr = fopen(fileName, openMode);

    // If the file doesn't exist, print an error message and return NULL
    if (fptr == NULL)
    {
        printf("File does not exist %s\n", fileName);
        return NULL;
    }
    // If file exists, return the file pointer
    return fptr;
}

void getOutputFileName(char input_file_name[], char* output_file_name) {
    int i;
    for (i = 0; input_file_name[i] != '\0'; i++)
    {
        output_file_name[i] = input_file_name[i];
    }
    output_file_name[i] = 's';
    output_file_name[i+1] = 'c';
    output_file_name[i+2] = 'n';
    output_file_name[i+3] = '\0';
}
