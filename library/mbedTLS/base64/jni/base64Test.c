#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"base64.h"

void showHelp() {
    printf("usage: base64 encode xxxx\n");
    printf("       base64 decode yyyy\n");
    exit(1);
}

char* base64Encode(unsigned char *input, size_t inputLength, size_t *writenBytes, int *errorCode) {
    //看看需要分配多少个字节
    size_t n = inputLength / 3 + (inputLength % 3);
    size_t outputLength = 4 * n + 1;

    //加密后的数据，这里定义为char*更明确，因为编码后的内容就是ASCII字符集中的字符组成的字符串
    char *output = (char *)calloc(outputLength, sizeof(char));
    
    //编码数据
    int base64EncodeIsOK = mbedtls_base64_encode((unsigned char *)output, outputLength, writenBytes, input, inputLength);
    if (0 == base64EncodeIsOK) {
        (*errorCode) = 0;
        return output;
    }
    (*errorCode) = MBEDTLS_ERR_BASE64_BUFFER_TOO_SMALL;
    return NULL;
}

unsigned char* base64Decode(char *input, size_t *writenBytes, int *errorCode) {
    size_t inputLength = strlen(input);

    //base64编码的字符串的长度必须是4的整数倍
    if ( inputLength % 4 != 0) {
        (*errorCode) = MBEDTLS_ERR_BASE64_INVALID_CHARACTER; 
        return NULL;
    }
    
    size_t outputLength = inputLength;
    //解码后的数据
    unsigned char *output = (unsigned char *)calloc(outputLength, sizeof(char));
    
    //解码数据
    int base64DecodeIsOK = mbedtls_base64_decode(output, outputLength, writenBytes, (unsigned char *)input, inputLength);
    if (0 == base64DecodeIsOK) {
        (*errorCode) = 0;
        return output;
    }
    (*errorCode) = MBEDTLS_ERR_BASE64_INVALID_CHARACTER;
    return NULL;
}


int main(int argc, char *argv[]) {
    if (argc == 3) {
        if (strcmp("encode", argv[1]) == 0) {
            size_t writenBytes = 0;
            int errorCode = -1;
            char * output = base64Encode((unsigned char *)argv[2], strlen(argv[2]), &writenBytes, &errorCode);
            printf("errorCode = %d\n", errorCode);
            if (NULL == output) {
                perror("error");
            } else {
                printf("base64(%s) = %s\n", argv[2], output);
            }
        } else if (strcmp("decode", argv[1]) == 0) {
            size_t writenBytes = 0;
            int errorCode = -1;
            unsigned char * output = base64Decode(argv[2], &writenBytes, &errorCode);
            printf("errorCode = %d\n", errorCode);
            if (NULL == output) {
                perror("error");
            } else {
                printf("base64(%s) = %s\n", argv[2], output);
            }
            
        } else {
            showHelp();
        }
    } else {
        showHelp();
    }
    return 0;
}
