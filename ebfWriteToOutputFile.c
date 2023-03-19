#include <stdio.h>

#include "ebfStruct.h"
#include "ebfErrorChecking.h"

// writes the header data and length, width parameters to the output file
int outputHeader(ebfData data, FILE *outputFile)
{
    // write the header data in one block
    // and use the return from fprintf to check that we wrote.
    if (BAD_OUTPUT(fprintf(outputFile, "eb\n%d %d\n", height, width))) 
        { // check write
            free(imageData);
            free(dataBlock);
            fclose(outputFile);
            printf("ERROR: Bad Output\n");
            return BAD_OUTPUT;
        } // check write
}

// writes all pixel values to the output file
int outputImageData(ebfData data, FILE *outputFile)
{
    // iterate though the array and print out pixel values
    for (int currentRow = 0; currentRow < data.height; currentRow++)
    { // writing out row
        for (int currentColumn = 0; currentColumn < data.width; currentColumn++)
        { // writing out column
            // validate if output to file was sucessful
            if (BAD_OUTPUT(fprintf(outputFile, "%u", data.imageData[currentRow][currentColumn])))
            { // check write
                fclose(outputFile);
                free(data.imageData);
                free(data.dataBlock);
                printf("ERROR: Bad Output\n");
                return BAD_OUTPUT;
            } // check write

            // if end of line has not been reached
            if ((currentColumn + 1) / width != 1)
            {
                // output whitespace to file
                // validate if output to file was sucessful
                if (BAD_OUTPUT(fprintf(outputFile, " ")))
                { // check write
                    fclose(outputFile);
                    free(data.imageData);
                    free(data.dataBlock);
                    return BAD_OUTPUT;
                } // check write
            }
            // else if end of line is reached, but end of row has not been reached
            else if ((currentColumn + 1) / width == 1 && currentRow != height - 1)
            {
                // output newline to file               
                // validate if output to file was sucessful
                if (BAD_OUTPUT(fprintf(outputFile, "\N")))
                { // check write
                    fclose(outputFile);
                    free(data.imageData);
                    free(data.dataBlock);
                    return BAD_OUTPUT;
                } // check write
            }
        }       
    } // writing out
}