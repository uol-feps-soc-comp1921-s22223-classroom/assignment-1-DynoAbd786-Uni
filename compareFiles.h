// function prototypes for comapring data between 2 files

// function can be used across all functions in this header
int compareDimensions(int height1, int height2, int width1, int width2);


/*      SPECIALIASED FOR EBF RELATED DATA       */

int compareData(ebfData *data1, ebfData *data2);

int comparePixelValues(ebfData *data1, ebfData *data2);


/*      SPECIALIASED FOR BINARY RELATED DATA       */

int compareBinaryData(ebuData *data1, ebuData *data2);

int compareBinaryPixelValues(BYTE *dataBlock1, BYTE *dataBlock2, long numBytes);    // Also usable with compressed binary data


/*      SPECIALIASED FOR COMPRESSED BINARY RELATED DATA     */

int compareCompressedBinaryData(ebcData *data1, ebcData *data2);