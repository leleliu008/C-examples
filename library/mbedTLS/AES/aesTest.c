//http://blog.fpliu.com/it/software/development/language/C/library/mbedTLS/include/aes.h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mbedtls/aes.h"
#include "mbedtls/base16.h"

void showHelp() {
    printf("usage:   aes encode STRING\n");
    printf("usage:   aes decode HEX\n");
    exit(1);
}

//AES/CBC/PKCS5Padding
//input可以是任意长度
//key只能是16、24、32个ASSCII字符组成的串儿
unsigned char* aes_cbc_pkcs5padding_encode(const char* key, unsigned char iv[16], const char* input, size_t* outputLength) {
    size_t keyLength = strlen(key);
    
    if (keyLength != 32 && keyLength != 24 && keyLength != 16) {
        perror("key必须是16、24、32个ASSCII字符组成的串\n");
        return NULL;
    }
        
    //获取到输入的要加密的内容的长度
    size_t inputLength = strlen(input);
    printf("input = %s, inputLength = %zu\n", input, inputLength);

    //看看需要分成多少个块，即使输入的数据是16的整数倍，也要补充16个字节的整数16
    size_t n = (inputLength >> 4) + 1;
    printf("n = %zu\n", n);

    //https://tools.ietf.org/html/rfc8018#appendix-B.2.5
    unsigned int padding = 16 - (inputLength & 15);
    printf("padding = %d\n", padding);

    //用于加密的的数据长度：字节数，此字节数正好等于输出的字节数
    size_t needInputLength = n << 4;
    printf("needInputLength = %zu\n", needInputLength);

    *outputLength = needInputLength;

    unsigned char* toBeEncryptBytes = (unsigned char*) calloc(needInputLength, sizeof(unsigned char));
    memcpy(toBeEncryptBytes, (unsigned char*)input, inputLength);
    
    //填充数据
    for (unsigned int i = 0; i < padding; i++) {
        toBeEncryptBytes[inputLength + i] = padding;
    }
     
    //加密后的数据
    unsigned char* output = (unsigned char*) calloc(needInputLength, sizeof(unsigned char));

    mbedtls_aes_context aes;
    mbedtls_aes_init(&aes);
    //设置加密的key
    mbedtls_aes_setkey_enc(&aes, (unsigned char*)key, keyLength << 3);
    //加密
    int resultCode = mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_ENCRYPT, needInputLength, iv, toBeEncryptBytes, output);
    
    if (NULL != toBeEncryptBytes) {
        free(toBeEncryptBytes);
        toBeEncryptBytes = NULL;
    }
    
    if (0 == resultCode) {
        return output;
    } else {
        free(output);
        return NULL;
    }
}

//AES/CBC/PKCS5Padding
//key只能是16、24、32个ASSCII字符组成的串儿
int aes_cbc_pkcs5padding_decode(const char*key, unsigned char iv[16], unsigned char* input, size_t inputLength, unsigned char* output, size_t* outputLength) {
    size_t keyLength = strlen(key);
     
    if (keyLength != 32 && keyLength != 24 && keyLength != 16) {
        perror("key必须是16、24、32个ASSCII字符组成的串\n");
        return MBEDTLS_ERR_AES_INVALID_INPUT_LENGTH;
    }
    
    if ((inputLength & 15) != 0) {
        perror("inputLength必须是16大的整数倍");
        return MBEDTLS_ERR_AES_INVALID_INPUT_LENGTH;
    }

    //设置解密的key
    mbedtls_aes_context aes;
    mbedtls_aes_init(&aes);
    mbedtls_aes_setkey_dec(&aes, (unsigned char*)key, keyLength << 3);
    
    //解密数据
    int resultCode = mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_DECRYPT, inputLength, iv, input, output);
    if (0 == resultCode) {
        int padding = output[inputLength - 1];
        (*outputLength) = inputLength - padding;
    }

    return resultCode;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        showHelp();
    }
    if (strcmp("encode", argv[1]) == 0 || strcmp("decode", argv[1]) == 0) {
        //初始向量，一般是一个随机数组成的，长度必须是块大小，一个块是16字节
        unsigned char iv[16] = {0};
        const char* key = "abcdefghjklqwert";
        size_t written = 0;
        if (strcmp("encode", argv[1]) == 0) {
            unsigned char* aesEncodedBytes = aes_cbc_pkcs5padding_encode(key, iv, argv[2], &written);
            char* hex = base16_encode(aesEncodedBytes, written, true);
            printf("aes_cbc_pkcs5padding(content=%s,key=%s)=%s\n", argv[2], key, hex);
            return 0;
        } else {
            unsigned char* input = base16_decode(argv[2]);
            size_t inputLength = strlen(argv[2]) >> 1;
            unsigned char output[inputLength];
            int resultCode = aes_cbc_pkcs5padding_decode(key, iv, input, inputLength, output, &written);
            if (0 == resultCode) {
                output[written] = '\0';
                printf("aes_cbc_pkcs5padding(content=%s,key=%s)=%s\n", output, key, argv[2]);
            } else {
                printf("error occurred. code is %d\n", resultCode);
            }
            return resultCode;
        }
    } else {
        showHelp();
    }
}
