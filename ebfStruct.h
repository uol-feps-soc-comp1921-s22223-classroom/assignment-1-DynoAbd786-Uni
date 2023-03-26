// Struct types for all files
#include <stdint.h>

// assigns type uint8_t to type BYTE for better readability
typedef uint8_t BYTE;

// gonna need this later i think
// this is me asking chatGPT the following:
// "lets say i create future structs called ebuData and ebcData. 
// how would i free each one if i dont know which one is being used in the code"
// so...

// typedef enum allows me to know what struct i am using when i need to know 
// (particularly for freeing structs within 1 contained function)
// typedef enum {
//     EBF_TYPE,
//     EBU_TYPE,
//     EBC_TYPE
// } eDataType;

// typedef struct {
//     eDataType type;
//     // other fields...
// } ebfData;

// typedef struct {
//     eDataType type;
//     // other fields...
// } ebuData;

// typedef struct {
//     eDataType type;
//     // other fields...
// } ebcData;

// ebfData* ebf = (ebfData*) malloc(sizeof(ebfData));
// ebf->type = EBF_TYPE;

// ebuData* ebu = (ebuData*) malloc(sizeof(ebuData));
// ebu->type = EBU_TYPE;

// ebcData* ebc = (ebcData*) malloc(sizeof(ebcData));
// ebc->type = EBC_TYPE;



// struct for storing data from an ebf file
typedef struct 
{
    // eDataType type;
    unsigned char magicNumber[2]; // the 2nd char can be used for free identifier (SWITCH CASE)
    int width, height;
    long numBytes;
    unsigned int **imageData;
    unsigned int *dataBlock;
} 
ebfData;

// struct for storing data from an ebu file
typedef struct
{
    unsigned char magicNumber[2]; // the 2nd char can be used for free identifier (SWITCH CASE)
    int width, height;
    long numBytes;
    BYTE **imageData;
    BYTE *dataBlock;
}
ebuData;

// struct for storing data from an ebc file
typedef struct
{
    unsigned char magicNumber[2]; // the 2nd char can be used for free identifier (SWITCH CASE)
    int width, height;
    long numBytesUncompressed;
    long numBytesCompressed;
    BYTE *dataBlockCompressed;
    BYTE *dataBlockUncompressed;
}
ebcData;



