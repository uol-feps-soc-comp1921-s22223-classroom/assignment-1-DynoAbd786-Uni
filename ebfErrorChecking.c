#include <stdio.h>
#include <string.h>

#include "ebfStruct.h"
#include "ebfErrorChecking.h"

// all functions within this file return 1 for any error detected, 0 otherwise

/*      NO ARGUEMENTS       */
// Provide the user with correct usage if no arguements are provided
// Returns 1 if no arguements are provided
int noArguements(int argc, char **argv)
{
    if (argc == 1)
    {
        // obtaining the executable name without the ./ at the beginning. 
        // this was adapted from a query asked to ChatGPT, asking "how to i take out the ./ from ./ebfComp"
        char *executableName = argv[0];
        int length = strlen(executableName);
        memmove(executableName, executableName + 2, length - 1);

        // output error message with respected executable name
        printf("Usage: %s file1 file2\n", executableName);
        return 1;
    }

    return 0;
}

/*      BAD ARGUEMENTS      */
// validate that user has enter 2 arguments (plus the executable name)
// Returns 1 if the wrong amount of arguements are provided
int badArguements(int argc)
{
    if (argc != 3)
    { // check arg count
        printf("ERROR: Bad Arguments\n");
        return 1;
    } // check arg count

    return 0;
}

/*      BAD FILE      */
// check file opened successfully
// returns 1 if bad file is given
int badFile(FILE *file, char *filename)
{
    if (!file)
    { // check file pointer
        printf("ERROR: Bad File Name (%s)\n", filename);
        return 1;
    } // check file pointer

    return 0;
}

/*      BAD MAGIC NUMBER        */
// checking against the casted value due to endienness
// returns 1 if magic number doesnt match known value
int badMagicNumber(unsigned short *magicNumberValue, char *filename)
{
    if (*magicNumberValue != MAGIC_NUMBER)
    { // check magic number
        printf("ERROR: Bad Magic Number (%s)\n", filename);
        return 1;
    } // check magic number

    return 0;
}

/*      BAD DIMENSIONS      */
// check dimensions to see if 2 values have been captured, and if dimensions are within acceptable range
// returns 1 if requirements arent met
int badDimensions(ebfData *data, int checkValue, char *filename)
{
    if (checkValue != 2 || data->height < MIN_DIMENSION || data->width < MIN_DIMENSION || data->height > MAX_DIMENSION || data->width > MAX_DIMENSION)
    { // check dimensions
        // close the file as soon as an error is found
        // print appropriate error message and return
        printf("ERROR: Bad Dimensions (%s)\n", filename);
        return 1;
    } // check dimensions

    return 0;
}

/*      BAD MALLOC      */
// checks if malloc has sucessfully allocated memory
// returns 1 if failed
int badMalloc(void *mallocData)
{
    if (mallocData == NULL)
    { // check malloc
        printf("ERROR: Image Malloc Failed\n");
        return 1;
    } // check malloc

    return 0;
}

/*      BAD DATA        */
// check if pixel value is out of bounds
// returns 1 if pixel value is out of bounds
int badPixelValue(int pixel, char *filename)
{
    if (pixel < MIN_PIXEL_VALUE || pixel > MAX_PIXEL_VALUE)
    {
        printf("ERROR: Bad Data (%s)\n", filename);
        return 1;
    }

    return 0;
}

// checks if length of array is the same as the width given in file
// returns 1 if array size does not match the stated width from the file
int wrongArraySize(ebfData *data, int arraySize, char *filename)
{
    if (arraySize != data->width)
    {
        printf("ERROR: Bad Data (%s)\n", filename);
        return 1;
    }

    return 0;
}

// checks if there are no more lines to read from the file (height given is lower than actual height of file)
// returns 1 if there are not enough lines in the file
int noMoreLines(void *array, char *filename)
{
    if (array == NULL)
    {
        printf("ERROR: Bad Data (%s)\n", filename);
        return 1;
    }

    return 0;
}

// checks if there are too many lines inside the file (height given is greater than actual height of file)
// returns 1 if there are too many lines in the file
int tooManyLines(void *array, char *filename)
{
    if (array != NULL)
    {
        printf("ERROR: Bad Data (%s)\n", filename);
        return 1;
    }

    return 0;
}

/*      BAD OUTPUT     */
// checks to see if the data is being outputted correctly
// returns 1 if the fprintf statement has had an error occur, or if nothing has been printed to the file
int badOutput(int check)
{
    if (check == 0 || check == -1)
    {
        printf("ERROR: Bad Output\n");
        return 1;
    }

    return 0;
}




