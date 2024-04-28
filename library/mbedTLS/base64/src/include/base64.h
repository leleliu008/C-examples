#ifndef BASE64_H
#define BASE64_H
    
    #include <stdlib.h>
     
    #ifdef __cplusplus
        extern "C" {
    #endif
            /* 获取base64编码成功后的字节数 */
            size_t get_base64_encode_output_length_in_bytes(size_t inputBufferSizeInBytes);

            /* base64编码
             * outputBuffer             base64编码后的字符串存放缓存区
             * outputBufferSizeInBytes  base64编码后的字符串存放缓存区的大小
             * inputBuffer              要编码的字节的起始指针
             * inputBufferSizeInBytes   要编码的字节的长度
             */
            int base64_encode(char * outputBuffer, size_t outputBufferSizeInBytes, unsigned char * inputBuffer, size_t inputBufferSizeInBytes);

            /* base64解码
             * outputBuffer                     base64解码后的字符串存放缓存区
             * outputBufferSizeInBytes          base64解码后的字符串存放缓存区的大小
             * writenToOutputBufferSizeInBytes  真实的向缓存区写入了多少字节
             * input                            base64编码的字符串
             */
            int base64_decode(unsigned char * outputBuffer, size_t outputBufferSizeInBytes, size_t * writenToOutputBufferSizeInBytes, char * inputBuffer, size_t inputBufferSizeInBytes);

    #ifdef __cplusplus
        }
    #endif
#endif
