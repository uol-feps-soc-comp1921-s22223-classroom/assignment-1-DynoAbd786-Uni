#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "ebfStruct.h"
#include "memoryManagement.h"
#include "ebfErrorChecking.h"
#include "loadFiles.h"
#include "ebfReadFromInputFile.h"
#include "ebfWriteToOutputFile.h"


int main(int argc, char **argv)
{ // main
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


    /*      TAKING INPUT FROM FILE      */

    // malloc a struct of type ebfData to store data to
    ebcData *inputData = mallocEbc();
    // checking if struct has been malloc'd
    if (badMalloc(inputData))
    {
        return BAD_MALLOC;
    }

    // get and open the input file in read mode
    char *inputFilename = argv[1];
    FILE *inputFile = loadInputFileBinary(inputFilename);
    // check file opened successfully
    if (badFile(inputFile, inputFilename))
    { // check file pointer
        freeEbcData(inputData);
        return BAD_FILE;
    } // check file pointer

    // checking if any error codes arise when getting data (0 means success)
    int errCode = getFileDataCompressedBinary(inputData, inputFilename, inputFile);
    if (errCode != 0)
    {
        // exit with the error code and free any data used in the program
        freeEbcuData(inputData);
        fclose(inputFile);
        return errCode;
    }

    fclose(inputFile);