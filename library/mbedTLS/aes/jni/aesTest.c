#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>
#include<string.h>
#include"aes.h"
#include"util.h"

void showHelp() {
    printf("usage:   aes <content> <key>\n");
    printf("summary: key可以分别是16、24、32个ASCII字符组成的字符串\n");
    printf("example: aes sssssss 01234567890123456789012345678901\n");
    exit(1);
}

//AES/CBC/PKCS5Padding
//input可以是任意长度
//key只能是16、24、32个ASSCII字符组成的串儿
unsigned char* aes_cbc_pkcs5padding_encode(const char *input, const char *key, size_t *outputLength) {
    size_t keyLength = strlen(key);
    printf("keyLength = %zu\n", keyLength);

    if (keyLength != 32 && keyLength != 24 && keyLength != 16) {
        perror("key必须是16、24、32个ASSCII字符组成的串\n");
        return NULL;
    }
        
    mbedtls_aes_context aes;

    //获取到输入的要加密的内容的长度
    size_t inputLength = strlen(input);
    printf("input = %s, inputLength = %zu\n", input, inputLength);

    //看看需要分成多少个块，即使输入的数据是16的整数倍，也要补充16个字节的整数16
    size_t n = inputLength / 16 + 1;

    //https://tools.ietf.org/html/rfc8018#appendix-B.2.5
    int padding = 16 - inputLength % 8;

    //用于加密的的数据长度：字节数，此字节数正好等于输出的字节数
    int needInputLength = 16 * n;
    *outputLength = needInputLength;

    //初始向量，一般是一个随机数组成的，长度必须是块大小，一个块是16字节，也就是16个ASCII字符
    unsigned char iv[16];
    memcpy(iv, key, keyLength);

    unsigned char *toBeEncryptBytes = (unsigned char *)calloc(needInputLength + 1, sizeof(unsigned char));
    memcpy(toBeEncryptBytes, (unsigned char *)input, inputLength);
    
    //填充数据
    for (int i = 0; i < padding; i++) {
        toBeEncryptBytes[inputLength + i] = padding;
    }
    toBeEncryptBytes[needInputLength] = '\0';

    //加密后的数据长度
    unsigned char *output = (unsigned char *)calloc(needInputLength, sizeof(unsigned char));

    //设置加密的key，并初始化
    mbedtls_aes_setkey_enc(&aes, (unsigned char*)key, keyLength * 8);

    //加密数据
    mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_ENCRYPT, needInputLength, iv, toBeEncryptBytes, output);
    
    char outputHex[ 2 * needInputLength + 1];
    memset(outputHex, 0, 2 * needInputLength + 1);

    bytes2HexStr(outputHex, output, needInputLength);

    printf("aesEncode(%s, %s)=%s\n", toBeEncryptBytes, key, outputHex);

    if (NULL != toBeEncryptBytes) {
        free(toBeEncryptBytes);
        toBeEncryptBytes = NULL;
    }

    return output;
}

//AES/CBC/PKCS5Padding
//key只能是16、24、32个ASSCII字符组成的串儿
unsigned char* aes_cbc_pkcs5padding_decode(unsigned char *input, size_t inputLength, size_t *outputLength, const char *key) {
    size_t keyLength = strlen(key);
    printf("keyLength = %zu\n", keyLength);
    
    if (keyLength != 32 && keyLength != 24 && keyLength != 16) {
        perror("key必须是16、24、32个ASSCII字符组成的串\n");
        return NULL;
    }
    
    mbedtls_aes_context aes;
    
    //初始向量，一般是一个随机数组成的，长度必须是块大小，一个块是16字节，也就是16个ASCII字符
    unsigned char iv[16];
    memcpy(iv, key, keyLength);
    
    //解密后的数据长度
    unsigned char *output = (unsigned char *)calloc(inputLength, sizeof(unsigned char));
    
    //设置加密的key，并初始化
    mbedtls_aes_setkey_dec(&aes, (unsigned char*)key, keyLength * 8);
    
    //加密数据
    mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_DECRYPT, inputLength, iv, input, output);
    
    int outputLastIndex = inputLength - 1;

    //取出output最后一个字节，转成数字
    unsigned int lastValue = output[outputLastIndex];
    printf("lastValue = %d\n", lastValue);
    if (lastValue > 0 && lastValue <= 16) {
        int j = outputLastIndex;
        while(output[j] == lastValue) {
            j--;
        }
        printf("j = %d\n", j);
        *outputLength = j + 1;
        outputLastIndex = j;
    }

    size_t inputHexLength = 2 * inputLength + 1;
    char inputHex[inputHexLength];
    memset(inputHex, 0, inputHexLength);
    bytes2HexStr(inputHex, input, inputLength);
    
    size_t outputHexLength = 2 * inputLength + 1;
    char outputHex[outputHexLength];
    memset(outputHex, 0, outputHexLength);
    bytes2HexStr(outputHex, output, inputLength);

    printf("aesDecode(%s, %s)=%s\n", inputHex, key, outputHex);
    
    return output;
}

int main(int argc, char *argv[]) {
    if (argc == 3) {
        //加密后的数据长度
        size_t encodedDataLength = 0;
        //加密
        unsigned char *encodedData = aes_cbc_pkcs5padding_encode(argv[1], argv[2], &encodedDataLength);
        //解密后的数据长度
        size_t decodedDataLength = 0;
        //解密
        unsigned char *decodedData = aes_cbc_pkcs5padding_decode(encodedData, encodedDataLength, &decodedDataLength, argv[2]);
        //因为我们自己知道，解密后的数据就是ASCII字符组成的字符串，所以，我们可以直接以字符串输出
        char ch[decodedDataLength + 1];
        memset(ch, 0, decodedDataLength + 1);
        memcpy(ch, decodedData, decodedDataLength);

        int length = strlen(ch);
        printf("ch = %s, length = %d\n", ch, length);
        printf("encodedDataLength = %lu, decodedDataLength = %lu\n", encodedDataLength, decodedDataLength);
    } else {
        showHelp();
    }
    return 0;
}
