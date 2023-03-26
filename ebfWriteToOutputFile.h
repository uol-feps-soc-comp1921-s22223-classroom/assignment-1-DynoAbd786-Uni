// contains function prototypes for anything to do with writing to the output file
// output header and image data functions take in individual variables rather than the whole struct to improve modularity (intentional design choice)

// for ebf to ebf outputs
int outputFileData(ebfData *data, char *filename, FILE *outputFile);

int outputHeader(unsigned char *magicNumber, int height, int width, FILE *outputFile);

int outputImageData(unsigned int **imageData, int height, int width, FILE *outputFile);

// for ebf to ebu outputs
int outputFileDataEbfDirectEbu(ebfData *data, char *filename, FILE *outputFile);

int outputImageDataEbfDirectEbu(unsigned int **imageData, int height, int width, FILE *outputFile);

// for ebu to ebf outputs
int outputFileDataEbuDirectEbf(ebuData *data, char *filename, FILE *outputFile);

int outputImageDataEbuDirectEbf(BYTE **imageData, int height, int width, FILE *outputFile);


// for ebu to ebu outputs
int outputFileDataBinary(ebuData *data, char *filename, FILE *outputFile);

int outputImageDataBinary(BYTE *dataBlock, long numBytes, FILE *outputFile);


// for ebu to ebc outputs
int outputFileDataEbuDirectEbc(ebuData *data, char *filename, FILE *outputFile);

int outputImageDataEbuDirectEbc(ebuData *data, char *filename, FILE *outputFile);

// for ebc to ebc outputs
int outputFileDataCompressedBinary(ebcData *data, char *filename, FILE *outputFile);

// for ebc to ebu outputs


/*      NEEDS SPECIALISED FUNCTIONS TO WRITE EBC FILES      */
// may be possible to write the entire dataBlock which is of guaranteed size numBytes


