#include "ebfStruct.h"
#include "compareFiles.h"


// compares the data to each other to check for differences
// returns 1 if data is different, 0 if same
// does not need to compare magic number value (MNV) since if a = MNV, b = MNV, then a = b (checking this means redundancy)
int compareData(ebfData *data1, ebfData *data2)
{
    // checking if dimensions are the same
    if (comapareDimensions(data1, data2))
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
int comapareDimensions(ebfData *data1, ebfData *data2)
{
    // checking if dimensions are different
    if (data1->height != data2->height || data1->width != data2->width)
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