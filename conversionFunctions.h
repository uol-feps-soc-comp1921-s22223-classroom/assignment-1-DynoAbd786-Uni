// contains all header files for converting data between data types ebf, ebu, and ebc

BYTE convertEbf2Ebu(unsigned int pixelValue);

unsigned int convertEbu2Ebf(BYTE pixelValueBinary);

BYTE convertEbc2Ebu(BYTE *compressedPixelValues);

BYTE *convertEbu2Ebc(BYTE *uncompressedPixelValues);
