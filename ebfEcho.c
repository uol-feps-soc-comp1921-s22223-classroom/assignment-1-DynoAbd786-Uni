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
    if (noArguements(argc))
    {
        return SUCCESS;
    }

    // validate that user has enter 2 arguments (plus the executable name)
    if (badArguements(argc))
    { // check arg count
        return BAD_ARGS;
    } // check arg count


    /*      TAKING INPUT FROM FILE      */

    // set up and store data from the ebf file
    ebfData *inputData = mallocEbf();
    // checking if struct has been malloc'd
    if (badMalloc(inputData))
    {
        return BAD_MALLOC;
    }

    // get and open the input file in read mode
    char *inputFilename = argv[1];
    FILE *inputFile = loadInputFile(inputFilename);
    // check file opened successfully
    if (badFile(inputFile, inputFilename))
    { // check file pointer
        freeData(inputData);
        return BAD_FILE;
    } // check file pointer

    // checking if any error codes arise when getting data (0 means success)
    int errCode = getFileData(inputData, inputFilename, inputFile);
    if (errCode != 0)
    {
        // exit with the error code and free any data used in the program
        freeData(inputData);
        fclose(inputFile);
        return errCode;
    }

    fclose(inputFile);


    /*      WRITING TO FILE     */

    // get and open the input file in read mode
    char *outputFilename = argv[2];
    FILE *outputFile = loadOutputFile(outputFilename);
    // validate that the file has been opened correctly
    if (badFile(outputFile, outputFilename))
    { // validate output file
        return BAD_FILE;
    } // validate output file

    // output to file
    errCode = outputFileData(inputData, outputFilename, outputFile);
    // checking for no rteturn errors
    if (errCode != 0)
    {
        // exit with the error code and free any data used in the program
        freeData(inputData);
        fclose(inputFile);
        return errCode;
    }

    // print final success message and return
    printf("ECHOED\n");
    return SUCCESS;
} // main()