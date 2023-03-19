#include <stdio.h>

// loads input file in read mode
FILE *loadInputFile(char *filename)
{
    // open the input file in read mode
    FILE *inputFile = fopen(filename, "r");
    return inputFile;
}

// loads output file in write mode
FILE *loadOutputFile(char *filename)
{
    // open the input file in read mode
    FILE *outputFile = fopen(filename, "w");
    return outputFile;
}