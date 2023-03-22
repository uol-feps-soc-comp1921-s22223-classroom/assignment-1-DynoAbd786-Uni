// contains function prototypes for reading from an input file

int getFileData(ebfData *inputData, char *filename, FILE *inputFile);

void getMagicNumber(FILE *inputFile, unsigned char *data);

int checkMagicNumberValue(unsigned char *magicNumber, char *filename);

int getDimensions(int *height, int *width, FILE *inputFile);

int setImageDataArray(ebfData *data);

int getImageDataArray(ebfData *data, FILE *inputFile, char *filename);

int setBinaryImageDataArrayEbu(ebuData *data);
