// Struct type for ebf file

typedef struct ebfData 
{
    unsigned char magicNumber[2];
    int width, height;
    long numBytes;
    unsigned int **imageData;
    unsigned int *dataBlock;
}
ebfData;