#ifndef URL_H
#define URL_H
    
    #include <stdlib.h>
    #include <stdbool.h>
     
    #ifdef __cplusplus
        extern "C" {
    #endif

            int url_encode(char* output, unsigned char* input, size_t inputLengthInBytes, bool isToUpper);

            int url_decode(unsigned char* output, size_t* outputLength, char* input);

    #ifdef __cplusplus
        }
    #endif
#endif
