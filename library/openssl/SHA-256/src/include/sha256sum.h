#ifndef SHA256SUM_H
#define SHA256SUM_H
    
    #include <stdio.h>
    #include <stdlib.h>
     
    #ifdef __cplusplus
        extern "C" {
    #endif
        int sha256sum_of_bytes (char outputBuffer[65], unsigned char * inputBuffer, size_t inputBufferSizeInBytes);
        int sha256sum_of_string(char outputBuffer[65], const char * str);
        int sha256sum_of_file  (char outputBuffer[65], const char * filepath);
        int sha256sum_of_stream(char outputBuffer[65], FILE * file);
    #ifdef __cplusplus
        }
    #endif
#endif
