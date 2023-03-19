#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "ebfStruct.h"
#include "memoryManagement.h"
#include "ebfErrorChecking.h"
#include "loadFiles.h"
#include "ebfReadFromInputFile.h"
#include "compareFiles.h"



int main(int argc, char **argv)
    { // main

    /*      CHEKCING ARGUEMENTS     */

    // Provide the user with correct usage if no arguements are provided
    if (noArguements(argc))
    {
        return SUCCESS;
    }

    // validate that user has enter 2 arguments (plus the executable name)
    if (badArguements(argc))
    { // check arg count
        return BAD_ARGS;
    } // check arg count


    /*      TAKING INPUT FROM FILES      */

    // initialise an empty array to store file data
    ebfData *dataToCompare[MAX_FILE_COMPARISON];

    for (int fileNumber = 0; fileNumber < MAX_FILE_COMPARISON; fileNumber++)
    {
        dataToCompare[fileNumber] = mallocEbf();
        // checking if struct has been malloc'd
        if (badMalloc(dataToCompare[fileNumber]))
        {
            return BAD_MALLOC;
        }

        // get and open the input file in read mode
        char *inputFilename = argv[fileNumber + 1];
        FILE *inputFile = loadInputFile(inputFilename);
        // check file opened successfully
        if (badFile(inputFile, inputFilename))
        { // check file pointer
            freeDataArray(dataToCompare);
            return BAD_FILE;
        } // check file pointer

        // checking if any error codes arise when getting data (0 means success)
        int errCode = getFileData(dataToCompare[fileNumber], inputFilename, inputFile);
        if (errCode != 0)
        {
            // exit with the error code and free any data used in the program
            freeDataArray(dataToCompare);
            fclose(inputFile);
            return errCode;
        }
        fclose(inputFile);
    }
    

    // compare the data from the two files:
    
    // start with magic number values
    if (*magicNumberValue1 != *magicNumberValue2)
        { // free and exit
        free(imageData1);
        free(imageData2);
        printf("DIFFERENT\n");
        return SUCCESS;
        } // free and exit

    // check dimensions
    if ((height1 != height2) || (width1 != width2))
        { // free and exit
        free(imageData1);
        free(imageData2);
        printf("DIFFERENT\n");
        return SUCCESS;
        } // free and exit

    // and check the pixel values
    for (int n=0; n<numBytes1; n++)
        {
        if(imageData1[n]!=imageData2[n])
            { // free and exit
            free(imageData1);
            free(imageData2);
            printf("DIFFERENT\n");
            return SUCCESS;
            } // free and exit
        }


    // free allocated memory before exit
    free(imageData1);
    free(imageData2);

    // if we have not exited on different data, must be identical
    printf("IDENTICAL\n");
    return SUCCESS;
    } // main()
