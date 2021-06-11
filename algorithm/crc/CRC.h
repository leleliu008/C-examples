#ifndef CRC_H
#define CRC_H
    
    #include <stdlib.h>

    #ifdef __cplusplus
        extern "C" {
    #endif

    unsigned char CRC(unsigned char *bytes, size_t nBytes);
    
    #ifdef __cplusplus
        }
    #endif
#endif
