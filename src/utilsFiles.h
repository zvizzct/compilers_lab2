
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
FILE *openFile(char *fileName)
{
    // Check if fileName is NULL, if it is, print an error message and return NULL
    if (fileName == NULL)
    {
        return NULL;
    }
    // Try to open the file with the given fileName in read mode
    FILE *fptr = fopen(fileName, "r");

    // If the file doesn't exist, print an error message and return NULL
    if (fptr == NULL)
    {
        printf("File does not exist %s\n", fileName);
        return NULL;
    }
    // If file exists, return the file pointer
    return fptr;
}

/**
 * @brief Read the content of a file and return it as a string
 *
 * @param file The file to read
 * @return char* The content of the file as a string, or NULL if no file was provided
 */
char *readFile(FILE *file)
{
    // Check if file is NULL, if it is, print an error message and return NULL
    if (file == NULL)
    {
        printf("No file provided, usage: ./preprocesor filename.c");
        return NULL;
    }
    // Get the file size
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);
    // Allocate memory for file content
    char *fileContent = (char *)malloc((fileSize + 1) * sizeof(char));
    // Read the file
    fread(fileContent, sizeof(char), fileSize, file);
    fileContent[fileSize] = '\0';
    return fileContent;
}

/**
 * @brief  Extract the base name of a file from a provided file name
 *
 * @param fileName The name of the file
 * @return char* The base name of the file, or the original file name if no '/' or '' is present
 */
char *baseName(const char *fileName)
{
    // Initialize base to NULL
    char *base = NULL;

    // If fileName is not NULL
    if (fileName != NULL)
    {
        // Find the last '/' in fileName
        base = strrchr(fileName, '/');
        // If '/' is not found
        if (base == NULL)
        {
            // Find the last '\' in fileName
            base = strrchr(fileName, '\\');
        }
    }
    // If base is still NULL
    if (base == NULL)
    {
        // Return fileName
        return (char *)fileName;
    }
    else
    {
        // Return the filename after the last '/' or '\'
        return base + 1;
    }
}

/**
 * @brief Generate a new file name by appending "-pre" to the original file name before its extension
 *
 * @param fileName  fileName The original file name
 * @return char*  The new file name
 */
char *getNewFileName(const char *fileName)
{
    // Allocate memory for newFileName
    char *newFileName = malloc(sizeof(char) * 256);
    // Find the last occurrence of '.' in fileName
    char *dot = strrchr(fileName, '.');
    // If '.' is found and the extension is .c
    if (dot && (!strcmp(dot, ".c")))
    {
        // Copy the substring of fileName before '.' to newFileName
        strncpy(newFileName, fileName, dot - fileName);
        // Add null character at the end of the substring
        newFileName[dot - fileName] = 0;
        // Append "-pre" to newFileName
        strcat(newFileName, "_pp");
        // Append the extension to newFileName
        strcat(newFileName, dot);
    }
    else
    {
        // If '.' is not found or the extension is not .c, just copy the fileName to newFileName
        strcpy(newFileName, fileName);
    }
    // return the newFileName
    return newFileName;
}

/**
 * @brief Write a string to a file with a provided name
 *
 * @param fileName The name of the file to create/write to
 * @param fileContent The content to write to the file
 * @return  char * The new file name
 */
char *writeFile(char *fileName, char *fileContent)
{
    // check if fileName or fileContent is NULL
    if (fileName == NULL || fileContent == NULL)
    {
        // if so, print an error message and return
        printf("No file name or content provided, usage: ./preprocesor filename.c");
        return NULL;
    }
    // get the base name of the file
    char *base = baseName(fileName);
    // get the new file name
    char *newFileName = getNewFileName(base);

    // create a string for the output folder
    char *outputFolder = "output/";
    // allocate memory for the new file name with folder
    char *newFileNameWithFolder = malloc(sizeof(char) * (strlen(outputFolder) + strlen(newFileName) + 1));

    // copy the output folder to newFileNameWithFolder
    strcpy(newFileNameWithFolder, outputFolder);
    // concatenate the new file name to newFileNameWithFolder
    strcat(newFileNameWithFolder, newFileName);

    // open the new file for writing
    FILE *fptr = fopen(newFileNameWithFolder, "w");
    // check if there was an error writing to the file
    if (fwrite(fileContent, sizeof(char), strlen(fileContent), fptr) < 0)
    {
        printf("Error writing to file %s", newFileNameWithFolder);
    }
    // close the file
    fclose(fptr);
    // return the new file name with folder
    return newFileNameWithFolder;
}