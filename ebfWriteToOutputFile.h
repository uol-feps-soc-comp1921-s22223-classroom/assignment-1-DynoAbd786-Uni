// contains function prototypes for anything to do with writing to the output file

int outputFileData(ebfData *inputData, char *filename, FILE *file);

int outputHeader(ebfData *data, FILE *outputFile);

int outputImageData(ebfData *data, FILE *outputFile);

