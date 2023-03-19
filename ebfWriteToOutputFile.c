#include <stdio.h>
#include <stdlib.h>

#include "ebfStruct.h"
#include "ebfErrorChecking.h"
#include "memoryManagement.h"
#include "ebfWriteToOutputFile.h"

// executes a series of functions to write to a file
// returns respective error codes if output has failed, otherwise 0 is successful
int outputFileData(ebfData *inputData, char *filename, FILE *outputFile)
{
    // output header to file and validate for success (0 means success)
    if (outputHeader(inputData, outputFile) != 0)
    {
        return BAD_OUTPUT;
    }

    // output image data to file and validate for success (0 means success)
    if (outputImageData(inputData, outputFile) != 0)
    {
        return BAD_OUTPUT;
    }

    return 0;
}


// writes the header data and length, width parameters to the output file
// returns error code if output has failed, 0 otherwise
int outputHeader(ebfData *data, FILE *outputFile)
{
    // write the header data in one block
    // and use the return from fprintf to check that we wrote.
    if (badOutput(fprintf(outputFile, "eb\n%d %d\n", data->height, data->width))) 
    { // check write
        return BAD_OUTPUT;
    } // check write
    return 0;
}

// writes all pixel values to the output file
// returns error code if output has failed, 0 if successful
int outputImageData(ebfData *data, FILE *outputFile)
{
    // iterate though the array and print out pixel values
    for (int currentRow = 0; currentRow < data->height; currentRow++)
    { // writing out row
        for (int currentColumn = 0; currentColumn < data->width; currentColumn++)
        { // writing out column
            // validate if output to file was sucessful
            if (badOutput(fprintf(outputFile, "%u", data->imageData[currentRow][currentColumn])))
            { // check write
                return BAD_OUTPUT;
            } // check write

            // if end of line has not been reached
            if ((currentColumn + 1) / data->width != 1)
            {
                // output whitespace to file
                // validate if output to file was sucessful
                if (badOutput(fprintf(outputFile, " ")))
                { // check write
                    return BAD_OUTPUT;
                } // check write
            }
            // else if end of line is reached, but end of row has not been reached
            else if ((currentColumn + 1) / data->width == 1 && currentRow != data->height - 1)
            {
                // output newline to file               
                // validate if output to file was sucessful
                if (badOutput(fprintf(outputFile, "\n")))
                { // check write
                    return BAD_OUTPUT;
                } // check write
            }
        }       
    }

    return 0;
}