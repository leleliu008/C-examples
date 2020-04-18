#ifndef LRC_H
#define LRC_H
    
    #include <stdlib.h>
    
    #ifdef __cplusplus
        extern "C" {
    #endif

    unsigned char LRC(unsigned char *bytes, size_t nBytes);
    
    #ifdef __cplusplus
        }
    #endif
#endif
