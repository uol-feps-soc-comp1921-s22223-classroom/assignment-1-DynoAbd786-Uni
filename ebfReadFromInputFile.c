#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "ebfStruct.h"
#include "ebfErrorChecking.h"
#include "memoryManagement.h"
#include "ebfReadFromInputFile.h"

// executes a series of funcions to gather and check all data from a file
int getFileData(ebfData *inputData, char* filename, FILE *inputFile)
{   
    // set first 2 characters which should be magic number
    getMagicNumber(inputFile, inputData);

    // checking against the casted value due to endienness.
    if (checkMagicNumberValue(inputData, filename))
    { // check magic number
        return BAD_MAGIC_NUMBER;
    } // check magic number


    // scan for the dimensions
    // and capture fscanfs return to ensure we got 2 values.
    int check = getDimensions(inputData, inputFile);
    // check if dimensions satisfy requirements
    if (badDimensions(inputData, check, filename))
    { // check dimensions
        return BAD_DIM;
    } // check dimensions

    // set up data array to store pixel values later
    check = setImageDataArray(inputData, inputFile);
    if (check != 0)
    {
        return check;
    }

    check = getImageDataArray(inputData, inputFile, filename);
    if (check != 0)
    {
        return check;
    }

    // return 0 for success
    return 0;
}


// read in magic number from file 
void getMagicNumber(FILE *inputFile, ebfData *data)
{
    data->magicNumber[0] = getc(inputFile);
    data->magicNumber[1] = getc(inputFile);
}


// finds, stores and returns magic number value
int checkMagicNumberValue(ebfData *data, char *filename)
{
    unsigned short *magicNumberValue = (unsigned short *) data->magicNumber;
    if (badMagicNumber(magicNumberValue, filename))
    {
        return 1;
    }
    return 0;
}


// read in dimensions and return number of values scanned
/* NEEDS ERROR CHECKING PER LINE */
int getDimensions(ebfData *data, FILE *inputFile)
{
    int check = fscanf(inputFile, "%d %d", &data->height, &data->width);
    return check;
}


int setImageDataArray(ebfData *data, FILE *inputFile)
{
    // caclulate total size and allocate memory for array
    data->numBytes = data->height * data->width;
    data->imageData = (unsigned int **) malloc(data->numBytes * sizeof(unsigned int*));

    // if malloc is unsuccessful, it will return a BAD MALLOC error code
    if (badMalloc(data->imageData))
    { // check malloc
        return BAD_MALLOC;
    } // check malloc

    // data block malloc'd to set up 2D array for imageData
    data->dataBlock = (unsigned int*) malloc(data->numBytes * sizeof(unsigned int));

    // if malloc is unsucessful, it will return a null pointer
    if (badMalloc(data->dataBlock))
    { // check malloc
        return BAD_MALLOC;
    } // check malloc

    // pointer arithmetic to set up 2D array 
    for (int row = 0; row < data->height; row++)
    {
        data->imageData[row] = data->dataBlock + row * data->width;
    }
    return 0;
}

// gets image data pixel by pixel and checks against specified parameters
// works in line by line fashion, in case height and width of pixels doesnt match the specified parameters
int getImageDataArray(ebfData *data, FILE *inputFile, char *filename)
{
    // set up quantity for worst case scenario of integer line ups (2 digit ints plus space across the width, with newline char at the end)
    long Max_Char_Bytes = sizeof(char)*3*(data->width + 1);
    // malloc empty buffer to store 1 line of data into as type char *
    char *input = (char *) malloc(Max_Char_Bytes);

    // if malloc is unsucessful, it will return a null pointer
    if (badMalloc(input))
    { // check malloc
        return BAD_MALLOC;
    } // check malloc


    // check to see if fgets has cycled to next line (sitting on line with the magic numbers currently)
    if (noMoreLines(fgets(input, sizeof(input), inputFile), filename))
    {
        // ensure that allocated data is freed before exit.
        free(input);      
        return BAD_DATA;
    }

    // malloc an array of pointers to unsigned ints
    // used to store numbers when converted from char *input array
    unsigned int *inputIntArray = (unsigned int *) malloc(sizeof(unsigned int) * (data->width + 1));

    if (badMalloc(inputIntArray))
    { // check malloc
        free(input);    
        return BAD_MALLOC;
    } // check malloc

    // read in each grey value from the file, line by line
    for (int currentRow = 0; currentRow < data->height; currentRow++)
    { // reading in row
        // read in line on row. Error check to see if line has been sucessfully read
        if (noMoreLines(fgets(input, Max_Char_Bytes, inputFile), filename))
        {
            // ensure that allocated data is freed before exit.
            free(input);
            free(inputIntArray);
            return BAD_DATA;
        }

        // find location of \n inside input string
        int len = strcspn(input, "\n");
        // and overwrite it to a null char (helps with error checking)
        input[len] = '\0';

        // separate array of chars according to whitespace char
        char *token = strtok(input, " ");
        // and keep an account of how many times this has happened
        int sizeOfIntArray = 0;

        // separate the char *array until end of string
        while (token != NULL)
        {
            // write the number obtained from the char *array to the array of ints, according to the incrementing variable sizeOfArray
            inputIntArray[sizeOfIntArray] = (unsigned int) atoi(token);
            sizeOfIntArray++;
            token = strtok(NULL, " ");
        }        

        // BAD DATA CHECK: checks to see if the sizeOfIntArray matches the inputted width
        if (wrongArraySize(data, sizeOfIntArray, filename))
        {
            // ensure that allocated data is freed before exit.
            free(input);
            free(inputIntArray);
            return BAD_DATA;
        }
        
        // for every element inside the line
        for (int currentColumn = 0; currentColumn < data->width; currentColumn++)
        {
            // BAD DATA CHECK: check if data collected is within permitted ranges
            if (badPixelValue(inputIntArray[currentColumn], filename))
            {
                // ensure that allocated data is freed before exit.
                free(input);
                free(inputIntArray);
                return BAD_DATA;
            }

            // writes every element of the line to the respective position in the imageData array
            data->imageData[currentRow][currentColumn] = inputIntArray[currentColumn];
        }
    }

    // validate there are no more rows of data to read from
    if (tooManyLines(fgets(input, Max_Char_Bytes, inputFile), filename))
    {
        // free all necessary data before exiting
        free(input);
        free(inputIntArray);
        return BAD_DATA;
    }

    // free and dereference char *array and pointer to unsigned int array since the purpose of these has been fulfilled
    free(input);
    input = NULL;
    free(inputIntArray);
    inputIntArray = NULL;
    return 0;
}