#include <stdio.h>
#include <stdlib.h>

#include "ebfStruct.h"
#include "ebfErrorChecking.h"
#include "memoryManagement.h"


// mallocs an uninitialised struct of type ebfData to store file information to
ebfData *mallocEbf()
{
    ebfData *data = (ebfData *) malloc(sizeof(ebfData));
    return data;
}

// mallocs an uninitialised struct of type ebuData to store file information to
ebuData *mallocEbu()
{
    ebuData *data = (ebuData *) malloc(sizeof(ebuData));
    return data;
}


// frees 1 data entry from the type ebfData
void freeData(ebfData *data)
{
    // checks if imageData has been malloc'd
    if (data->imageData != NULL)
    {
        // free and dereference imageData to NULL to avoid hanging pointer
        free(data->imageData);
        data->imageData = NULL;
    }

    // checks if dataBlock has been malloc'd
    if (data->dataBlock != NULL)
    {
        // free and dereference dataBlock to NULL to avoid hanging pointer
        free(data->dataBlock);
        data->dataBlock = NULL;
    }

    // checks if data struct has been malloc'd
    if (data != NULL)
    {
        // free and dereference data struct to NULL to avoid hanging pointer
        free(data);
        data = NULL;
    }
}

// frees an array of structs (for comp files)
void freeDataArray(ebfData *dataToCompare[])
{
    // for the 2 structs in the file storing data 
    for (int fileNumber = 0; fileNumber < MAX_FILE_COMPARISON; fileNumber++)
    {
        // check if the struct at position fileNumber has some data. if so, free the struct
        if (dataToCompare[fileNumber] != NULL)
        {
            freeData(dataToCompare[fileNumber]);
        }
    }
}


// may be useful later, see ebfStruct
// void freeData(void* data)
// {
//     switch (((eDataType*)data)->type) {
//         case EBF_TYPE:
//             // cast the data pointer to an ebfData pointer and free the memory
//             free((ebfData*)data);
//             break;
//         case EBU_TYPE:
//             // cast the data pointer to an ebuData pointer and free the memory
//             free((ebuData*)data);
//             break;
//         case EBC_TYPE:
//             // cast the data pointer to an ebcData pointer and free the memory
//             free((ebcData*)data);
//             break;
//         default:
//             // error: unknown type
//             break;
//     }
// }
