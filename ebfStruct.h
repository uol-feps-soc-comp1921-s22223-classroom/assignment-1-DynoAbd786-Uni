typedef struct ebfFile 
{
    unsigned char magicNumber[2];
    unsigned short *magicNumberValue = (unsigned short *)magicNumber;
    int width = 0, height = 0;
    unsigned int *imageData;
    long numBytes;
    
}