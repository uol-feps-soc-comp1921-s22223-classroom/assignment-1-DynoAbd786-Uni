#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "ebfErrorChecking.h"
#include "ebfReadFromInputFile.h"
#include "ebfWriteToOutputFile.h"
#include "ebfStruct.h"


int main(int argc, char **argv)
    { // main

    // Provide the user with correct usage if no arguements are provided
    if (NO_ARGUEMENTS(argc))
    {
        return SUCCESS;
    }

    // validate that user has enter 2 arguments (plus the executable name)
    if (BAD_ARGUEMENTS(argc))
    { // check arg count
        return BAD_ARGS;
    } // check arg count




    // // create a char array to hold magic number
    // // and cast to short
    // unsigned char magicNumber[2];
    // unsigned short *magicNumberValue = (unsigned short *)magicNumber;

    // // create and initialise variables used within code
    // int width = 0, height = 0;
    // unsigned int **imageData;
    // long numBytes;

    ebfData inputData;
    // inputFile.magicNumberValue = funct()




    // open the input file in read mode
    char *filename = argv[1];
    FILE *inputFile = loadInputFile(filename);
    // check file opened successfully
    if (BAD_FILE(&inputFile, filename))
    { // check file pointer
        return BAD_INPUT_FILE;
    } // check file pointer


    
    // set first 2 characters which should be magic number
    getMagicNumber(inputData);

    // checking against the casted value due to endienness.
    if (BAD_MAGIC_NUMBER(getMagicNumberValue(inputData), filename))
    { // check magic number
        fclose(inputFile);
        return BAD_MAGIC_NUMBER;
    } // check magic number


    // scan for the dimensions
    // and capture fscanfs return to ensure we got 2 values.
    int check = fscanf(inputFile, "%d %d", &height, &width);
    // check if dimensions satisfy requirements
    if (BAD_DIMENSIONS(inputData, check, filename))
    { // check dimensions
        fclose(inputFile);
        return BAD_DIM;
    } // check dimensions




    // // caclulate total size and allocate memory for array
    // numBytes = height * width;
    // imageData = (unsigned int **)malloc(numBytes * sizeof(unsigned int*));

    // // if malloc is unsuccessful, it will return a null pointer
    // if (BAD_MALLOC(imageData))
    // { // check malloc
    //     fclose(inputFile);
    //     return BAD_MALLOC;
    // } // check malloc

    // unsigned int* dataBlock = (unsigned int*) malloc(numBytes * sizeof(unsigned int));

    // // if malloc is unsucessful, it will return a null pointer
    // if (BAD_MALLOC(dataBlock))
    // { // check malloc
    //     free(imageData);
    //     fclose(inputFile);
    //     return BAD_MALLOC;
    // } // check malloc

    // // pointer arithmetic to set up 2D array 
    // for (int row = 0; row < height; row++)
    // {
    //     imageData[row] = dataBlock + row * width;
    // }

    // set up data array to store pixel values later
    check = setImageDataArray(inputData, inputFile);
    if (check = BAD_MALLOC)
    {
        return BAD_MALLOC;
    }

    check = getImageDataArray(inputData, inputFile, filename);
    switch (check)
    {
        case BAD_MALLOC:
            return check;
        case BAD_DATA:
            return check;
    }



    // // set up quantity for worst case scenario of integer line ups (2 digit ints plus space across the width, with newline char at the end)
    // long Max_Char_Bytes = sizeof(char)*3*(width + 1);
    // // malloc empty buffer to store 1 line of data into as type char *
    // char *input = (char *) malloc(Max_Char_Bytes);

    // // if malloc is unsucessful, it will return a null pointer
    // if (input == NULL)
    // { // check malloc
    //     free(imageData);
    //     free(dataBlock);
    //     fclose(inputFile);
    //     return BAD_MALLOC;
    // } // check malloc


    // // check to see if fgets has cycled to next line (sitting on line with the magic numbers currently)
    // if (fgets(input, sizeof(input), inputFile) == NULL)
    // {
    //     // ensure that allocated data is freed before exit.
    //     free(imageData);
    //     free(dataBlock);
    //     free(input);
    //     fclose(inputFile);        
    //     printf("ERROR: Bad Data (%s)\n", argv[1]);
    //     return BAD_DATA;
    // }

    // // malloc an array of pointers to unsigned ints
    // // used to store numbers when converted from char *input array
    // unsigned int *inputIntArray = (unsigned int *) malloc(sizeof(unsigned int) * (width + 1));

    // if (inputIntArray == NULL)
    // { // check malloc
    //     free(imageData);
    //     free(dataBlock);
    //     free(input);
    //     fclose(inputFile);
    //     printf("ERROR: Image Malloc Failed\n");
    //     return BAD_MALLOC;
    // } // check malloc

    // // read in each grey value from the file, line by line
    // for (int currentRow = 0; currentRow < height; currentRow++)
    // { // reading in row
    //     // read in line on row. Error check to see if line has been sucessfully read
    //     if (fgets(input, Max_Char_Bytes, inputFile) == NULL)
    //     {
    //         // ensure that allocated data is freed before exit.
    //         free(imageData);
    //         free(dataBlock);
    //         free(input);
    //         free(inputIntArray);
    //         fclose(inputFile);
    //         printf("ERROR: Bad Data (%s)\n", argv[1]);
    //         return BAD_DATA;
    //     }

    //     // find location of \n inside input string
    //     int len = strcspn(input, "\n");
    //     // and overwrite it to a null char (helps with error checking)
    //     input[len] = '\0';

    //     // separate array of chars according to whitespace char
    //     char *token = strtok(input, " ");
    //     // and keep an account of how many times this has happened
    //     int sizeOfIntArray = 0;

    //     // separate the char *array until end of string
    //     while (token != NULL)
    //     {
    //         // write the number obtained from the char *array to the array of ints, according to the incrementing variable sizeOfArray
    //         inputIntArray[sizeOfIntArray] = (unsigned int) atoi(token); //can be negative numbers
    //         sizeOfIntArray++;
    //         token = strtok(NULL, " ");
    //     }        

    //     // BAD DATA CHECK: checks to see if the sizeOfIntArray matches the inputted width
    //     if (sizeOfIntArray != width)
    //     {
    //         // ensure that allocated data is freed before exit.
    //         free(imageData);
    //         free(dataBlock);
    //         free(input);
    //         free(inputIntArray);
    //         fclose(inputFile);
    //         printf("ERROR: Bad Data (%s)\n", argv[1]);
    //         return BAD_DATA;
    //     }
        
    //     // for every element inside the line
    //     for (int currentColumn = 0; currentColumn < width; currentColumn++)
    //     {
    //         // BAD DATA CHECK: check if data collected is within permitted ranges
    //         if (inputIntArray[currentColumn] < 0 || inputIntArray[currentColumn] > 31)
    //         {
    //             // ensure that allocated data is freed before exit.
    //             free(imageData);
    //             free(dataBlock);
    //             free(input);
    //             free(inputIntArray);
    //             fclose(inputFile);
    //             printf("ERROR: Bad Data (%s)\n", argv[1]);
    //             return BAD_DATA;
    //         }

    //         // writes every element of the line to the respective position in the imageData array
    //         imageData[currentRow][currentColumn] = inputIntArray[currentColumn];
    //     }
    // }

    // // validate there are no more rows of data to read from
    // if (fgets(input, Max_Char_Bytes, inputFile) != NULL)
    // {
    //     // free all necessary data before exiting
    //     free(imageData);
    //     free(dataBlock);
    //     free(input);
    //     free(inputIntArray);
    //     fclose(inputFile);
    //     printf("ERROR: Bad Data (%s)\n", argv[1]);
    //     return BAD_DATA;
    // }

    // free char *array and pointer to unsigned int array since the purpose of these has been fulfilled
    // free(input);
    // // input = NULL;
    // free(inputIntArray);
    // // input = 

    // now we have finished using the inputFile we should close it
    fclose(inputFile);

    // open the output file in write mode
    // overwrite new filename
    filename = argv[2];
    FILE *outputFile = loadOutputFile(filename);
    // validate that the file has been opened correctly
    if (BAD_FILE(outputFile, filename))
        { // validate output file
            // free malloc'd data before exiting
            free(inputData.imageData);
            free(inputData.dataBlock);
            return BAD_FILE;
        } // validate output file

    

    // // write the header data in one block
    // check = fprintf(outputFile, "eb\n%d %d\n", height, width);
    // // and use the return from fprintf to check that we wrote.
    // if (check == 0) 
    //     { // check write
    //         free(imageData);
    //         free(dataBlock);
    //         fclose(outputFile);
    //         printf("ERROR: Bad Output\n");
    //         return BAD_OUTPUT;
    //     } // check write


    // // iterate though the array and print out pixel values
    // for (int currentRow = 0; currentRow < height; currentRow++)
    // { // writing out row
    //     for (int currentColumn = 0; currentColumn < width; currentColumn++)
    //     { // writing out column
    //         check = fprintf(outputFile, "%u", imageData[currentRow][currentColumn]);
    //         // validate if output to file was sucessful
    //         if (check == 0)
    //         { // check write
    //             fclose(outputFile);
    //             free(imageData);
    //             printf("ERROR: Bad Output\n");
    //             return BAD_OUTPUT;
    //         } // check write

    //         // if end of line has not been reached
    //         if ((currentColumn + 1) / width != 1)
    //         {
    //             // output whitespace to file
    //             check = fprintf(outputFile, " ");
                
    //             // validate if output to file was sucessful
    //             if (check == 0)
    //             { // check write
    //                 fclose(outputFile);
    //                 free(imageData);
    //                 printf("ERROR: Bad Output\n");
    //                 return BAD_OUTPUT;
    //             } // check write
    //         }
    //         // else if end of line is reached, but end of row has not been reached
    //         else if ((currentColumn + 1) / width == 1 && currentRow != height - 1)
    //         {
    //             // output newline to file
    //             check = fprintf(outputFile, "\n");
                
    //             // validate if output to file was sucessful
    //             if (check == 0)
    //             { // check write
    //                 fclose(outputFile);
    //                 free(imageData);
    //                 printf("ERROR: Bad Output\n");
    //                 return BAD_OUTPUT;
    //             } // check write
    //         }
    //     }       
    // } // writing out

    if (outputImageData(inputData, outputFile))
    {
        return BAD_OUTPUT;
    }

    // free allocated memory before exit
    free(imageData);
    free(dataBlock);
    // close the output file before exit
    fclose(outputFile);

    // print final success message and return
    printf("ECHOED\n");
    return SUCCESS;
    } // main()