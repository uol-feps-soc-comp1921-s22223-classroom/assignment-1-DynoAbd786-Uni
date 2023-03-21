#include <stdio.h>

#include "loadFiles.h"

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

// loads input file in read binary mode
FILE *loadInputFileBinary(char *filename)
{
    // open the input file in read mode
    FILE *outputFile = fopen(filename, "rb");
    return outputFile;
}

// loads output file in write binary mode
FILE *loadOutputFileBinary(char *filename)
{
    // open the input file in read mode
    FILE *outputFile = fopen(filename, "wb");
    return outputFile;
}