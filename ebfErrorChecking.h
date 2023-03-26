// Header file for all error checking functions
// all function return 1 for any error detected, 0 otherwise

// macors to define different return values, pixel value and dimension range, and magic number for the program
#define SUCCESS 0
#define BAD_ARGS 1
#define BAD_FILE 2
#define BAD_MAGIC_NUMBER 3
#define BAD_DIM 4
#define BAD_MALLOC 5
#define BAD_DATA 6
#define BAD_OUTPUT 7
#define MAGIC_NUMBER_EBF 0x6265
#define MAGIC_NUMBER_EBU 0x7565
#define MAGIC_NUMBER_EBC 0x6365
#define MAX_DIMENSION 262144
#define MIN_DIMENSION 1
#define MIN_PIXEL_VALUE 0
#define MAX_PIXEL_VALUE 31


int noArguements(int argc, char **argv);

int badArguements(int argc);

int badFile(FILE *file, char *filename);

int badMagicNumberEbf(unsigned short *magicNumberValue, char *filename);

int badMagicNumberEbu(unsigned short *magicNumberValue, char *filename);

int badMagicNumberEbc(unsigned short *magicNumberValue, char *filename);

int badDimensions(int height, int width, int checkValue, char *filename);

int badMalloc(void *mallocData);

int endOfFile(FILE *file, char *filename);

int notEndOfFile(FILE *file, char *filename);

int badPixelValue(int pixel, char *filename);

int wrongArraySize(int width, int arraySize, char *filename);

int noMoreLines(void *array, char *filename);

int tooManyLines(void *array, char *filename);

int badByteRead(int count, char *filename);

int badNumBytes(long count, long numBytesUncompressed, char *filename);

int badOutput(int check);