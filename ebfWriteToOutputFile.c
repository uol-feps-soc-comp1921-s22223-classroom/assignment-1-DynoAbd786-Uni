#include <stdio.h>
#include <stdlib.h>

#include "ebfStruct.h"
#include "conversionFunctions.h"
#include "ebfErrorChecking.h"
#include "memoryManagement.h"
#include "ebfWriteToOutputFile.h"


// executes a series of functions to write to a file
// returns respective error codes if output has failed, otherwise 0 is successful
int outputFileData(ebfData *data, char *filename, FILE *outputFile)
{
    // output header to file and validate for success (0 means success)
    if (outputHeader(data->magicNumber, data->height, data->width, outputFile) != 0)
    {
        return BAD_OUTPUT;
    }
    // output image data to file and validate for success (0 means success)
    else if (outputImageData(data->imageData, data->height, data->width, outputFile) != 0)
    {
        return BAD_OUTPUT;
    }

    return 0;
}


// writes the header data and length, width parameters to the output file
// returns error code if output has failed, 0 otherwise
int outputHeader(unsigned char *magicNumber, int height, int width, FILE *outputFile)
{
    // write the header data in one block
    // and use the return from fprintf to check that we wrote.
    if (badOutput(fprintf(outputFile, "%s\n%d %d\n", (char *) magicNumber, height, width)))
    { // check write
        return BAD_OUTPUT;
    } // check write
    return 0;
}

// writes all pixel values to the output file
// returns error code if output has failed, 0 if successful
int outputImageData(unsigned int **imageData, int height, int width, FILE *outputFile)
{
    // iterate though the array and print out pixel values
    for (int currentRow = 0; currentRow < height; currentRow++)
    { // writing out row
        for (int currentColumn = 0; currentColumn < width; currentColumn++)
        { // writing out column
            // validate if output to file was sucessful
            if (badOutput(fprintf(outputFile, "%u", imageData[currentRow][currentColumn])))
            { // check write
                return BAD_OUTPUT;
            } // check write

            // if end of line has not been reached
            if ((currentColumn + 1) / width != 1)
            {
                // output whitespace to file
                // validate if output to file was sucessful
                if (badOutput(fprintf(outputFile, " ")))
                { // check write
                    return BAD_OUTPUT;
                } // check write
            }
            // else if end of line is reached, but end of row has not been reached
            else if ((currentColumn + 1) / width == 1 && currentRow != height - 1)
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


// function takes all data for ebf file and outputs it to ebu file
// returns respective error codes if failed, 0 if otherwise
int outputFileDataEbfDirectEbu(ebfData *data, char *filename, FILE *outputFile)
{
    // define the header that needs to be outputted to the file
    unsigned char *header = (unsigned char *) "eu";
    // output header to file and validate for success (0 means success)
    if (outputHeader(header, data->height, data->width, outputFile) != 0)
    {
        return BAD_OUTPUT;
    }
    // output image data to file and validate for success (0 means success)
    else if (outputImageDataEbfDirectEbu(data->imageData, data->height, data->width, outputFile) != 0)
    {
        return BAD_OUTPUT;
    }

    return 0;
}

// writes all pixel values from ebf to the ebu output file in binary format 
// returns error code if output has failed, 0 if successful
int outputImageDataEbfDirectEbu(unsigned int **imageData, int height, int width, FILE *outputFile)
{
    // iterate though the array and print out pixel values
    for (int currentRow = 0; currentRow < height; currentRow++)
    { // writing out row
        for (int currentColumn = 0; currentColumn < width; currentColumn++)
        { // writing out column
            // convert pixel value to binary format
            BYTE pixelValueByte = convertEbf2Ebu(imageData[currentRow][currentColumn]);
            // run and check if the output was successful
            // BYTE pixelValueByte = 0x00;
            if (badOutput((int) fwrite(&pixelValueByte, sizeof(BYTE), 1, outputFile)))
            { // check write
                return BAD_OUTPUT;
            } // check write
        }
    }

    return 0;
}


// writes all pixel values from ebu binary format to the ebf output file in readable format
// returns error code if output has failed, 0 if successful
int outputFileDataEbuDirectEbf(ebuData *data, char *filename, FILE *outputFile)
{
    // define the header that needs to be outputted to the file
    unsigned char *header = (unsigned char *) "eb";
    // output header to file and validate for success (0 means success)
    if (outputHeader(header, data->height, data->width, outputFile) != 0)
    {
        return BAD_OUTPUT;
    }
    // output image data to file and validate for success (0 means success)
    else if (outputImageDataEbuDirectEbf(data->imageData, data->height, data->width, outputFile) != 0)
    {
        return BAD_OUTPUT;
    }

    return 0;
}


int outputImageDataEbuDirectEbf(BYTE **imageData, int height, int width, FILE *outputFile)
{
    // iterate though the array and print out pixel values
    for (int currentRow = 0; currentRow < height; currentRow++)
    { // writing out row
        for (int currentColumn = 0; currentColumn < width; currentColumn++)
        { // writing out column
            // convert pixel value to binary format
            unsigned int pixelValue = convertEbu2Ebf(imageData[currentRow][currentColumn]);
            // run and check if the output was successful
            if (badOutput(fprintf(outputFile, "%u", pixelValue)))
            { // check write
                return BAD_OUTPUT;
            } // check write

            // if end of line has not been reached
            if ((currentColumn + 1) / width != 1)
            {
                // output whitespace to file
                // validate if output to file was sucessful
                if (badOutput(fprintf(outputFile, " ")))
                { // check write
                    return BAD_OUTPUT;
                } // check write
            }
            // else if end of line is reached, but end of row has not been reached
            else if ((currentColumn + 1) / width == 1 && currentRow != height - 1)
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



// outputs all data to a file, where the pixel values are in binary
// returns error code if output has failed, 0 if successful
int outputFileDataBinary(ebuData *data, char *filename, FILE *outputFile)
{
    // output header to file and validate for success (0 means success)
    if (outputHeader(data->magicNumber, data->height, data->width, outputFile) != 0)
    {
        return BAD_OUTPUT;
    }
    // output image data to file and validate for success (0 means success)
    else if (outputImageDataBinary(data->dataBlock, data->numBytes, outputFile) != 0)
    {
        return BAD_OUTPUT;
    }

    return 0;
}

// outputs the binary pixel data directly to a file
// returns error code if output has failed, 0 if successful
int outputImageDataBinary(BYTE *dataBlock, long numBytes, FILE *outputFile)
{
    // // iterate though the array and print out pixel values
    // for (int currentRow = 0; currentRow < height; currentRow++)
    // { // writing out row
    //     for (int currentColumn = 0; currentColumn < width; currentColumn++)
    //     { // writing out column
    //         // run and check if the output was successful
    //         if (badOutput((int) fwrite(&imageData[currentRow][currentColumn], sizeof(BYTE), 1, outputFile)))
    //         { // check write
    //             return BAD_OUTPUT;
    //         } // check write
    //     }
    // }

    fwrite(dataBlock, numBytes, 1, outputFile);

    return 0;
}