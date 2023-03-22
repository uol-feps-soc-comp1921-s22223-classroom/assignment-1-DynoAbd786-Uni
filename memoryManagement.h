// Header file for all global memory related variables

// defines the maximum amount of files that can be compared by any Comp file
#define MAX_FILE_COMPARISON 2

ebfData *mallocEbf();

ebuData *mallocEbu();

void freeData(ebfData *data);

void freeDataArray(ebfData *dataToCompare[]);

void freeEbfReadDataArrays(char *input, unsigned int *inputIntArray);