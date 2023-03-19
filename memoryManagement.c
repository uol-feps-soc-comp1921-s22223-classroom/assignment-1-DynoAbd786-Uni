#include <stdio.h>
#include <stdlib.h>

#include "ebfStruct.h"
#include "ebfErrorChecking.h"
#include "memoryManagement.h"



// frees 1 data entry from the type ebfData
void freeData(ebfData *data)
{
    if (data->imageData != NULL)
    {
        free(data->imageData);
        data->imageData = NULL;
    }

    if (data->dataBlock != NULL)
    {
        free(data->dataBlock);
        data->dataBlock = NULL;
    }

    if (data != NULL)
    {
        free(data);
        data = NULL;
    }
}

ebfData *mallocEbf()
{
    ebfData *data = (ebfData *) malloc(sizeof(ebfData));
    return data;
}

void freeDataArray(ebfData *dataToCompare[])
{
    for (int fileNumber = 0; fileNumber < MAX_FILE_COMPARISON; fileNumber++)
    {
        freeData(dataToCompare[fileNumber]);
    }
}

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
