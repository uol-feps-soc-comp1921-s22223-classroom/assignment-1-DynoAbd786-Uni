// Header file for all global memory related variables

// defines the maximum amount of files that can be compared by any Comp file
#define MAX_FILE_COMPARISON 2

void freeData(ebfData *data);

ebfData *mallocEbf();

void freeDataArray(ebfData *dataToCompare[]);