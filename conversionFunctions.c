#include <stdio.h>

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
// BYTE *convertEbc2Ebu(BYTE *compressedPixelValues);
// {
//     for (int byteNumber = 0; byteNumber < )
// }

// function converts an array of uncompressed binary pixels to compressed binary format 
BYTE *convertEbu2Ebc(BYTE *uncompressedPixelValues, BYTE *compressedBinaryArray, int numBytes)
{    
    // variables for storing and tracking compressed binary information
    BYTE storageByte = 0;
    int compressedBitPostitionTracker = 0;
    int compressedBinaryArrayPostitionTracker = 0;

    // for every byte stored inside the uncompressed byte array
    for (int byteNumber = 0; byteNumber < numBytes; byteNumber++)
    {
        // for the first 5 bits inside the selected byte, starting at byte 5
        for (int bitNumber = MAX_BIT; bitNumber > 0; bitNumber--)
        {
            // grab the least significant bit at the position bitNumber
            int LSB = (uncompressedPixelValues[byteNumber] >> (bitNumber - 1)) & 0x01;

            // overwrite the storageByte to contain the LSB and the information of the storageByte at correct positions
            storageByte = (storageByte << 1) | LSB;
            compressedBitPostitionTracker++;
            
            // checking if the byte is full of information
            if (compressedBitPostitionTracker == 8)
            {
                // write the storageByte to the compressed array and increment the array to the next position
                compressedBinaryArray[compressedBinaryArrayPostitionTracker] = storageByte;
                compressedBinaryArrayPostitionTracker++;
                // reset all variables for the next byte
                storageByte = 0;
                compressedBitPostitionTracker = 0;
                
            }
        }
    }

    // output final byte to the compressed array
    compressedBinaryArray[compressedBinaryArrayPostitionTracker] = storageByte;

    return compressedBinaryArray;
}