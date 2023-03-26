#include <stdio.h>

#include "ebfStruct.h"
#include "compareFiles.h"


// compares the data to each other to check for differences
// returns 1 if data is different, 0 if same
// does not need to compare magic number value (MNV) since if a = MNV, b = MNV, then a = b (checking this means redundancy)
int compareData(ebfData *data1, ebfData *data2)
{
    // checking if dimensions are the same
    if (compareDimensions(data1->height, data2->height, data1->width, data2->width))
    {
        return 1;
    }
    
    // checking if pixel values are the same
    if (comparePixelValues(data1, data2))
    {
        return 1;
    }

    // return 0 for files are the same
    return 0;   
}

// compares the dimensions agaisnt each other
// return 1 if dimensions are different, 0 if same
int compareDimensions(int height1, int height2, int width1, int width2)
{
    // checking if dimensions are different
    if (height1 != height2 || width1 != width2)
    {
        // return 1 if different
        return 1; 
    }

    return 0;
}

// compares the pixel values agaisnt each other
// returns 1 if the data is different, 0 if same
int comparePixelValues(ebfData *data1, ebfData *data2)
{
    // looping through the respective arrays
    for (int row = 0; row < data1->height; row++)
    {
        for (int column = 0; column < data1->width; column++)
        {
            // checking if the pixel values match
            if (data1->imageData[row][column] != data2->imageData[row][column])
            {
                // return 1 if different
                return 1;
            }
        }
    }

    return 0;
}


// compares binary data agaisnt each other to check for differences
// returns 1 if data is different, 0 if same
// function also does not need to compare magic number
int compareBinaryData(ebuData *data1, ebuData *data2)
{
    // checking if dimensions are the same
    if (compareDimensions(data1->height, data2->height, data1->width, data2->width))
    {
        return 1;
    }
    
    // checking if pixel values are the same
    if (compareBinaryPixelValues(data1->dataBlock, data2->dataBlock, data1->numBytes))
    {
        return 1;
    }

    // return 0 for files are the same
    return 0;   
}


// TEST IF INT CAST IS REQUIRED
// compares binary pixel values agaisnt each other
// returns 1 if the data is different, 0 if same
int compareBinaryPixelValues(BYTE *dataBlock1, BYTE *dataBlock2, long numBytes)
{
    // looping through both 1D arrays
    for (int byteNumber = 0; byteNumber < numBytes; byteNumber++)
    {
        // checking if the pixel values match
        if ((int) dataBlock1[byteNumber] != (int) dataBlock2[byteNumber])
        {
            // return 1 if different
            return 1;
        }
    }

    // return 0 for files are the same
    return 0;   
}

// compares compressed binary data agaisnt each other to check for differences
// returns 1 if data is different, 0 if same
// function also does not need to compare magic number
int compareCompressedBinaryData(ebcData *data1, ebcData *data2)
{
    // checking if dimensions are the same
    if (compareDimensions(data1->height, data2->height, data1->width, data2->width))
    {
        return 1;
    }
    
    // checking if pixel values in compressed form are the same
    if (compareBinaryPixelValues(data1->dataBlockCompressed, data2->dataBlockCompressed, data1->numBytesCompressed))
    {
        return 1;
    }

    // return 0 for files are the same
    return 0;   
}


