// http://blog.fpliu.com/it/software/mbedTLS/include/base64.h

#include <base64.h>

#include "base64_mbedtls.h"

size_t get_base64_encode_output_length_in_bytes(size_t inputBufferSizeInBytes) {
    //看看需要分配多少个字节
    //编码后，长度变为原来的4/3倍
    size_t n = inputBufferSizeInBytes / 3U + (((inputBufferSizeInBytes % 3U) == 0) ? 0U : 1U);
    return (n << 2);
}

int base64_encode(char * outputBuffer, size_t outputBufferSizeInBytes, unsigned char * inputBuffer, size_t inputBufferSizeInBytes) {
    size_t writtenSizeInBytes;
    return mbedtls_base64_encode((unsigned char*)outputBuffer, outputBufferSizeInBytes, &writtenSizeInBytes, inputBuffer, inputBufferSizeInBytes);
}

int base64_decode(unsigned char * outputBuffer, size_t outputBufferSizeInBytes, size_t * writtenSizeInBytes, char * inputBuffer, size_t inputBufferSizeInBytes) {
    return mbedtls_base64_decode(outputBuffer, outputBufferSizeInBytes, writtenSizeInBytes, (unsigned char *)inputBuffer, inputBufferSizeInBytes);
}
