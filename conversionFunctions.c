#include "ebfStruct.h"
#include "conversionFunctions.h"

// function coverts 1 pixel value from type ebfData file to binary format.
// does a bitwise calculation to find the 8 least significant bits from the 4 byte unsigned int type
// error checking unnecessary since pixel values have already been checked to be within limits
BYTE convertEbf2Ebu(unsigned int pixelValue)
{
    BYTE byteValue = (BYTE) (pixelValue & 0xFF);        // adapted from ChatGPT. Query: "Can i cast an unsigned int ** to uint8_t **"
    return byteValue;
}

// function coverts 1 pixel value from type ebuData file to readable numeric format.
unsigned int convertEbu2Ebf(BYTE pixelValueBinary)
{
    unsigned int pixelValue = (unsigned int) pixelValueBinary;
    return pixelValue;
}

// function converts an array of compressed binary pixels to uncompressed binary format 
BYTE *convertEbc2Ebu(BYTE *compressedPixelValues);
{
    for (int byteNumber = 0; byteNumber < )
}

// function converts an array of uncompressed binary pixels to compressed binary format 
BYTE *convertEbu2Ebc(BYTE *uncompressedPixelValues);
{
    
}