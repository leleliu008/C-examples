#ifndef BASE_16_H
#define BASE_16_H
    
    #include <stdlib.h>
    #include <stdbool.h>
     
    #ifdef __cplusplus
        extern "C" {
    #endif

            /* base16编码
             * output               base16编码后的字符串
             * input                要编码的字节的起始指针
             * inputLengthInBytes   要编码的字节的长度
             * isToUpper            是否编码为大写字母
             */
            int base16_encode(char* output, unsigned char* input, size_t inputLengthInBytes, bool isToUpper);

            /* base16解码
             * input base16编码的字符串
             */
            int base16_decode(unsigned char* output, char* input);

    #ifdef __cplusplus
        }
    #endif
#endif
