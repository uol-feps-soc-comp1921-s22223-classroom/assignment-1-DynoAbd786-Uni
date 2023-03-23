// contains function prototypes for reading from an input file

int getFileData(ebfData *inputData, char *filename, FILE *inputFile);

void getMagicNumber(FILE *inputFile, unsigned char *data);

unsigned short *getMagicNumberValue(unsigned char *magicNumber);

int getDimensions(int *height, int *width, FILE *inputFile);

int setImageDataArray(ebfData *data);

int getImageDataArray(ebfData *data, FILE *inputFile, char *filename);

int getFileDataBinary(ebuData *inputData, char* filename, FILE *inputFile);

int setBinaryImageDataArrayEbu(ebuData *data);

int getBinaryImageDataArray(ebuData *data, FILE *inputFile, char *filename);

