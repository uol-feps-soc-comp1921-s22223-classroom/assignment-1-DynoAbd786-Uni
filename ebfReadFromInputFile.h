// contains function prototypes for reading from an input file

int getFileData(ebfData *inputData, char *filename, FILE *inputFile);

void getMagicNumber(FILE *inputFile, ebfData *data);

int checkMagicNumberValue(ebfData *data, char *filename);

int getDimensions(ebfData *data, FILE *inputFile);

int setImageDataArray(ebfData *data, FILE *inputFile);

int getImageDataArray(ebfData *data, FILE *inputFile, char *filename);
