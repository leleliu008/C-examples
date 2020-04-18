//http://blog.fpliu.com/it/data/text/coding/Base16

#include <string.h>
#include "base16.h"

char* base16_encode_to_upper(unsigned char* bytes, size_t nBytes) {
    return base16_encode(bytes, nBytes, true);
}

char* base16_encode_to_lower(unsigned char* bytes, size_t nBytes) {
    return base16_encode(bytes, nBytes, false);
}

char* base16_encode(unsigned char* bytes, size_t nBytes, bool isToUpper) {
    const char *table = isToUpper ? "0123456789ABCDEF" : "0123456789abcdef";
    unsigned char highByte, lowByte;
    char *output = (char *)calloc(nBytes << 1, sizeof(char));
    for (size_t i = 0; i < nBytes; i++) {
        //向右移动4bit，获得高4bit
        highByte = bytes[i] >> 4;
        //与0x0f做位与运算，获得低4bit
        lowByte = bytes[i] & 0x0F;

        //由于高4bit和低4bit都只有4个bit，他们转换成10进制的数字，范围都在0 ～ 15闭区间内
        //大端模式
        size_t j = i << 1;
        output[j] = table[highByte];
        output[j + 1] = table[lowByte];
    }
    return output;
}

//把16进制字符转换成10进制表示的数字
//通过man ascii命令查看ASCII编码表即可得到如下转换逻辑
short hex2dec(char c) {
    if ('0' <= c && c <= '9') {
        return c - '0';
    } else if ('a' <= c && c <= 'f') {
        return c - 'a' + 10;
    } else if ('A' <= c && c <= 'F') {
        return c - 'A' + 10;
    } else {
        return 0;
    }
}

unsigned char* base16_decode(char* hex) {
    size_t inputLength = strlen(hex);
    
    //hex指向的字符串长度必须是2的整数倍，也就是必须是偶数
    if (1 == (inputLength & 1)) {
        return NULL;
    }
    
    size_t halfInputLength = inputLength >> 1;
    unsigned char *output = (unsigned char *)calloc(halfInputLength, sizeof(unsigned char));
    for (size_t i = 0; i < halfInputLength; i++) {
        //16进制数字转换为10进制数字的过程
        size_t j = i << 1;
        output[i] = (hex2dec(hex[j]) << 4) + hex2dec(hex[j + 1]);
    }
    return output;
}
