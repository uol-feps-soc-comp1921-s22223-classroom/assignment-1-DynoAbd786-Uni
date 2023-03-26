// function prototypes for comapring data between 2 files

// function can be used across all functions in this header
int compareDimensions(int height1, int height2, int width1, int width2);

int compareBinaryPixelValues(BYTE *dataBlock1, BYTE *dataBlock2, long numBytes);


/*      SPECIALIASED FOR EBF RELATED DATA       */

int compareData(ebfData *data1, ebfData *data2);

int comparePixelValues(ebfData *data1, ebfData *data2);        // could be redundant


/*      SPECIALIASED FOR BINARY RELATED DATA       */

int compareBinaryData(ebuData *data1, ebuData *data2);


/*      SPECIALIASED FOR COMPRESSED BINARY RELATED DATA     */

int compareCompressedBinaryData(ebcData *data1, ebcData *data2);