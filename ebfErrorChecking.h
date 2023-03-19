// Header file for all error checking functions

#define SUCCESS 0
#define BAD_ARGS 1
#define BAD_FILE 2
#define BAD_MAGIC_NUMBER 3
#define BAD_DIM 4
#define BAD_MALLOC 5
#define BAD_DATA 6
#define BAD_OUTPUT 7
#define MAGIC_NUMBER 0x6265
#define MAX_DIMENSION 262144
#define MIN_DIMENSION 1
#define MIN_PIXEL_VALUE 0
#define MAX_PIXEL_VALUE 31


int noArguements(int argc);

int badArguements(int argc);

int badFile(FILE *file, char *filename);

int badMagicNumber(unsigned short *magicNumberValue, char *filename);

int badDimensions(ebfData *data, int checkValue, char *filename);

int badMalloc(void *mallocData);

int badPixelValue(int pixel, char *filename);

int wrongArraySize(ebfData *data, int arraySize, char *filename);

int noMoreLines(void *array, char *filename);

int tooManyLines(void *array, char *filename);

int badOutput(int check);