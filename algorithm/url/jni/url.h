#ifndef URL_H
#define URL_H
    
    #include <stdlib.h>
    #include <stdbool.h>
     
    #ifdef __cplusplus
        extern "C" {
    #endif

    char* url_encode         (unsigned char *bytes, size_t nBytes, bool isToUpper);
    char* url_encode_to_upper(unsigned char *bytes, size_t nBytes);
    char* url_encode_to_lower(unsigned char *bytes, size_t nBytes);
    
    unsigned char* url_decode(char *input, size_t *outputLength);

    #ifdef __cplusplus
        }
    #endif
#endif
