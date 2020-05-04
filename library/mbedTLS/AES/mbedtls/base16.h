#ifndef BASE_16_H
#define BASE_16_H
    
    #include <stdlib.h>
    #include <stdbool.h>
     
    #ifdef __cplusplus
        extern "C" {
    #endif

    /*base16编码
     *bytes       要编码的字节的起始指针
     *nBytes 要编码的字节的长度
     *isToUpper   是否编码为大写字母
     */
    char* base16_encode         (unsigned char *bytes, size_t nBytes, bool isToUpper);
    char* base16_encode_to_upper(unsigned char *bytes, size_t nBytes);
    char* base16_encode_to_lower(unsigned char *bytes, size_t nBytes);

    /*base16解码
     *hex base16编码的字符串
     */
    unsigned char* base16_decode(char *hex);

    #ifdef __cplusplus
        }
    #endif
#endif
