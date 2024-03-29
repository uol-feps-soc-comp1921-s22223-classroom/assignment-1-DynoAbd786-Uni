#include <stdio.h>

#include "fileStructs.h"
#include "memoryManagement.h"
#include "errorChecking.h"
#include "loadFiles.h"
#include "readFromInputFile.h"
#include "compareFiles.h"



int main(int argc, char **argv)
{
    /*      CHEKCING ARGUEMENTS     */

    // Provide the user with correct usage if no arguements are provided
    if (noArguements(argc, argv))
    {
        return SUCCESS;
    }

    // validate that user has enter 2 arguments (plus the executable name)
    if (badArguements(argc))
    { // check arg count
        return BAD_ARGS;
    } // check arg count


    /*      TAKING INPUT FROM FILES      */

    // initialise an empty array to store file data (max files to compare is 2)
    ebuData *dataToCompare[MAX_FILE_COMPARISON];

    // looping through the number of files to compare
    for (int fileNumber = 0; fileNumber < MAX_FILE_COMPARISON; fileNumber++)
    {
        // allocate data for array of type ebu
        dataToCompare[fileNumber] = mallocEbu();
        // checking if struct has been malloc'd
        if (badMalloc(dataToCompare[fileNumber]))
        {
            // free data and exit
            freeEbuDataArray(dataToCompare);
            return BAD_MALLOC;
        }

        // get and open the input file in read mode
        char *inputFilename = argv[fileNumber + 1];
        FILE *inputFile = loadInputFileBinary(inputFilename);
        // check file opened successfully
        if (badFile(inputFile, inputFilename))
        { // check file pointer
            // free data and exit
            freeEbuDataArray(dataToCompare);
            return BAD_FILE;
        } // check file pointer

        // checking if any error codes arise when getting data (0 means success)
        int errCode = getFileDataBinary(dataToCompare[fileNumber], inputFilename, inputFile);
        if (errCode != 0)
        {
            // exit with the error code and free any data used in the program
            freeEbuDataArray(dataToCompare);
            fclose(inputFile);
            return errCode;
        }
        fclose(inputFile);
    }
    

    /*      COMPARING DATA BETWEEN FILES      */

    // running function to check if file data is the same
    // prints different if return value is 1, identical if return value is 0
    if (compareBinaryData(dataToCompare[0], dataToCompare[1]))
    {
        printf("DIFFERENT\n");
    }
    else
    {
        printf("IDENTICAL\n");
    }

    // free the data array and close the progran with return value SUCCESS.
    freeEbuDataArray(dataToCompare);
    return SUCCESS;
}