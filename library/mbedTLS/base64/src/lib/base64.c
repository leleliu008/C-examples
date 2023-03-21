// http://blog.fpliu.com/it/software/mbedTLS/include/base64.h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <base64.h>
#include "base64_mbedtls.h"

size_t get_base64_encode_output_length_in_bytes(size_t inputBufferSizeInBytes) {
    //看看需要分配多少个字节
    size_t n = inputBufferSizeInBytes / 3U + (((inputBufferSizeInBytes % 3U) == 0) ? 0U : 1U);
    return (n << 2);
}

int base64_encode(char* outputBuffer, size_t outputBufferSizeInBytes, unsigned char* inputBuffer, size_t inputBufferSizeInBytes) {
    size_t writtenToOutputBufferCountInBytes = 0U;
    if (0 == mbedtls_base64_encode((unsigned char*)outputBuffer, outputBufferSizeInBytes, &writtenToOutputBufferCountInBytes, inputBuffer, inputBufferSizeInBytes)) {
        return 0;
    } else {
        return MBEDTLS_ERR_BASE64_BUFFER_TOO_SMALL;
    }
}

int base64_decode(unsigned char* outputBuffer, size_t outputBufferSizeInBytes, size_t* writtenToOutputBufferCountInBytes, char* input) {
    size_t inputBufferSizeInBytes = strlen(input);

    //base64编码的字符串的长度必须是4的整数倍
    if ((inputBufferSizeInBytes & 3U) != 0U) {
        return MBEDTLS_ERR_BASE64_INVALID_CHARACTER; 
    }

    if (0 == mbedtls_base64_decode(outputBuffer, outputBufferSizeInBytes, writtenToOutputBufferCountInBytes, (unsigned char *)input, inputBufferSizeInBytes)) {
        return 0;
    } else {
        return MBEDTLS_ERR_BASE64_INVALID_CHARACTER;
    }
}
