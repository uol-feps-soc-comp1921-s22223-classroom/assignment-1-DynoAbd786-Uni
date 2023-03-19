#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "ebfStruct.h"
#include "ebfErrorChecking.h"

// read in magic number from file 
void getMagicNumber(FILE inputFile, ebfData data)
{
    data.magicNumber[0] = getc(inputFile);
    data.magicNumber[1] = getc(inputFile);    
}

// finds and returns magic number value
unsigned short *getMagicNumberValue(ebfData data)
{
    unsigned short *magicNumberValue = (unsigned short *) data.magicNumber;
    return *magicNumberValue;
}

// read in dimensions and return number of values scanned
/* NEEDS ERROR CHECKING PER LINE */
int getDimensions(ebfData data, FILE *inputFile);
{
    int check = fscanf(inputFile, "%d %d", &data.height, &data.width);
    return check;
}

int setImageDataArray(ebfData data, FILE *inputFile)
{
    // caclulate total size and allocate memory for array
    data.numBytes = data.height * data.width
    data.imageData = (unsigned int **)malloc(numBytes * sizeof(unsigned int*));

    // if malloc is unsuccessful, it will return a BAD MALLOC error code
    if (BAD_MALLOC(data.imageData))
    { // check malloc
        fclose(inputFile);
        return BAD_MALLOC;
    } // check malloc

    // data block malloc'd to set up 2D array for imageData
    unsigned int* dataBlock = (unsigned int*) malloc(numBytes * sizeof(unsigned int));

    // if malloc is unsucessful, it will return a null pointer
    if (BAD_MALLOC(dataBlock))
    { // check malloc
        free(imageData);
        fclose(inputFile);
        return BAD_MALLOC;
    } // check malloc

    // pointer arithmetic to set up 2D array 
    for (int row = 0; row < height; row++)
    {
        imageData[row] = dataBlock + row * width;
    }
}

// gets image data pixel by pixel and checks against specified parameters
// works in line by line fashion, in case height and width of pixels doesnt match the specified parameters
int getImageDataArray (ebfData data, FILE *inputFile, char *filename)
{
    // set up quantity for worst case scenario of integer line ups (2 digit ints plus space across the width, with newline char at the end)
    long Max_Char_Bytes = sizeof(char)*3*(width + 1);
    // malloc empty buffer to store 1 line of data into as type char *
    char *input = (char *) malloc(Max_Char_Bytes);

    // if malloc is unsucessful, it will return a null pointer
    if (BAD_MALLOC(input))
    { // check malloc
        free(data.imageData);
        free(data.dataBlock);
        fclose(inputFile);
        return BAD_MALLOC;
    } // check malloc


    // check to see if fgets has cycled to next line (sitting on line with the magic numbers currently)
    if (NO_MORE_LINES(fgets(input, sizeof(input), inputFile)))
    {
        // ensure that allocated data is freed before exit.
        free(data.imageData);
        free(data.dataBlock);
        free(input);
        fclose(inputFile);        
        printf("ERROR: Bad Data (%s)\n", argv[1]);
        return BAD_DATA;
    }

    // malloc an array of pointers to unsigned ints
    // used to store numbers when converted from char *input array
    unsigned int *inputIntArray = (unsigned int *) malloc(sizeof(unsigned int) * (width + 1));

    if (BAD_MALLOC(inputIntArray))
    { // check malloc
        free(data.imageData);
        free(data.dataBlock);
        free(input);
        fclose(inputFile);
        return BAD_MALLOC;
    } // check malloc

    // read in each grey value from the file, line by line
    for (int currentRow = 0; currentRow < height; currentRow++)
    { // reading in row
        // read in line on row. Error check to see if line has been sucessfully read
        if (NO_MORE_LINES(fgets(input, Max_Char_Bytes, inputFile), filename))
        {
            // ensure that allocated data is freed before exit.
            free(data.imageData);
            free(data.dataBlock);
            free(input);
            free(inputIntArray);
            fclose(inputFile);
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
        if (sizeOfIntArray != width)
        {
            // ensure that allocated data is freed before exit.
            free(data.imageData);
            free(data.dataBlock);
            free(input);
            free(inputIntArray);
            fclose(inputFile);
            return BAD_DATA;
        }
        
        // for every element inside the line
        for (int currentColumn = 0; currentColumn < width; currentColumn++)
        {
            // BAD DATA CHECK: check if data collected is within permitted ranges
            if (BAD_PIXEL_VALUE(inputIntArray[currentColumn], filename))
            {
                // ensure that allocated data is freed before exit.
                free(data.imageData);
                free(data.dataBlock);
                free(input);
                free(inputIntArray);
                fclose(inputFile);
                printf("ERROR: Bad Data (%s)\n", argv[1]);
                return BAD_DATA;
            }

            // writes every element of the line to the respective position in the imageData array
            data.imageData[currentRow][currentColumn] = inputIntArray[currentColumn];
        }
    }

    // validate there are no more rows of data to read from
    if (TOO_MANY_LINES(fgets(input, Max_Char_Bytes, inputFile)))
    {
        // free all necessary data before exiting
        free(imageData);
        free(dataBlock);
        free(input);
        free(inputIntArray);
        fclose(inputFile);
        printf("ERROR: Bad Data (%s)\n", argv[1]);
        return BAD_DATA;
    }

    // free and dereference char *array and pointer to unsigned int array since the purpose of these has been fulfilled
    free(input);
    input = NULL;
    free(inputIntArray);
    inputIntArray = NULL;
}