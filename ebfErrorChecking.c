#include <stdio.h>

#include "ebfStruct.h"

#define SUCCESS 0
#define BAD_ARGS 1
#define BAD_INPUT_FILE 2
#define BAD_MAGIC_NUMBER 3
#define BAD_DIM 4
#define BAD_MALLOC 5
#define BAD_DATA 6
#define BAD_OUTPUT 7
#define MAGIC_NUMBER 0x6265
#define MAX_DIMENSION 262144
#define MIN_DIMENSION 1
#define MIN_PIXEL_VALUE 0
#define MAX_PIXEL_VALUE 31

/*      NO ARGUEMENTS       */
// Provide the user with correct usage if no arguements are provided
// Returns 1 if no arguements are provided
int NO_ARGUEMENTS(int argc)
{
    if (argc == 1)
    {
        printf("Usage: ebfEcho file1 file2"); // need to change this to become more universal. use argv[0]
        return 1;
    }

    return 0;
}

/*      BAD ARGUEMENTS      */
// validate that user has enter 2 arguments (plus the executable name)
// Returns 1 if the wrong amount of arguements are provided
int BAD_ARGUEMENTS(int argc)
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
int BAD_FILE(FILE *file, char *filename)
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
int BAD_MAGIC_NUMBER(unsigned short *magicNumberValue, filename)
{
    if (*magicNumberValue != MAGIC_NUMBER)
    { // check magic number
        printf("ERROR: Bad Magic Number (%s)\n", filename);
        return 1;
    } //check magic number

    return 0;
}

/*      BAD DIMENSIONS      */
// check dimensions to see if 2 values have been captured, and if dimensions are within acceptable range
// returns 1 if requirements arent met
int BAD_DIMENSIONS(ebfData data, int checkValue, char *filename)
{
    if (checkValue != 2 || data.height < MIN_DIMENSION || data.width < MIN_DIMENSION || data.height > MAX_DIMENSION || data.width > MAX_DIMENSION)
    { // check dimensions
        // close the file as soon as an error is found
        // print appropriate error message and return
        printf("ERROR: Bad Dimensions (%s)\n", argv[1]);
        return 1;
    } // check dimensions

    return 0;
}

/*      BAD MALLOC      */
// checks if malloc has sucessfully allocated memory
// returns 1 if failed
int BAD_MALLOC(void *mallocData)
{
    if (mallocData == NULL)
    { // check malloc
        printf("ERROR: Image Malloc Failed\n");
        return 1;
    } // check malloc

    return 0;
}

/*      BAD DATA        */
// check if pixel value is not out of bounds
int BAD_PIXEL_VALUE(int pixel, char *filename)
{
    if (inputIntArray[currentColumn] < MIN_PIXEL_VALUE || inputIntArray[currentColumn] > MAX_PIXEL_VALUE)
    {
        printf("ERROR: Bad Data (%s)\n", filename);
        return 1;
    }

    return 0;
}

// checks if length of array is the same as the width given in file
int WRONG_ARRAY_SIZE(ebfData data, int arraySize, char *filename)
{
    if (arraySize != data.width)
    {
        printf("ERROR: Bad Data (%s)\n", filename);
        return 1;
    }

    return 0;
}

int NO_MORE_LINES(void *array, char *filename)
{
    if (array == NULL)
    {
        printf("ERROR: Bad Data (%s)\n", filename);
        return 1;
    }

    return 0;
}

int TOO_MANY_LINES(void *array, char *filename)
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
int BAD_OUTPUT(int check)
{
    if (check == 0 || check == -1)
    {
        printf("ERROR: Bad Output\n");
        return 1;
    }

    return 0;
}




