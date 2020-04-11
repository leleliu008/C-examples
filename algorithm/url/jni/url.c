//参考：http://blog.fpliu.com/it/data/text/coding/URL

#include <string.h>
#include "URL.h"

char* url_encode(unsigned char *bytes, size_t nBytes, bool isToUpper) {
    const char *table = isToUpper ? "0123456789ABCDEF" : "0123456789abcdef";

    size_t outputLength = 0;
    //以最坏的情况分配内存
    char *output = (char *)calloc(3 * nBytes + 1, sizeof(char));
    for (size_t i = 0; i < nBytes; i++) {
        unsigned char byte = bytes[i];
        //这些字符保持原样
        if (('0' <= byte && byte <= '9') ||
            ('a' <= byte && byte <= 'z') ||
            ('A' <= byte && byte <= 'Z') || 
            byte == '.' || byte == '_' || byte == '-' || byte == '*') {
            output[outputLength++] = byte;
        } else if (' ' == byte) { //把空格编码成+
            output[outputLength++] = '+';
        } else { //其他字符都转换成%XY，XY是Base16编码
            //向右移动4bit，获得高4bit
            unsigned char highByte = byte >> 4;
            //与0x0f做位与运算，获得低4bit
            unsigned char lowByte = byte & 0x0F;
            //由于高4bit和低4bit都只有4个bit，他们转换成10进制的数字，范围都在0 ～ 15闭区间内
            //大端模式
            output[outputLength++] = '%';
            output[outputLength++] = table[highByte];
            output[outputLength++] = table[lowByte];
        }
    }
    return output;
}

char* url_encode_to_upper(unsigned char *bytes, size_t nBytes) {
    return url_encode(bytes, nBytes, true);
}

char* url_encode_to_lower(unsigned char *bytes, size_t nBytes) {
    return url_encode(bytes, nBytes, false);
}

char hex2dec(char c) {
    if ('0' <= c && c <= '9') {
        return c - '0';
    } else if ('a' <= c && c <= 'f') {
        return c - 'a' + 10;
    } else if ('A' <= c && c <= 'F') {
        return c - 'A' + 10;
    } else {
        return -1;
    }
}

unsigned char* url_decode(char *input, size_t *outputLength) {
    size_t inputLength = strlen(input);
    size_t outputLength_ = 0;
    //以最坏的情况分配内存
    unsigned char *output = (unsigned char *)calloc(inputLength + 1, sizeof(unsigned char));
    for (size_t i = 0; i < inputLength; i++) {
        char c = input[i];
        if (c == '%') {
            char c1 = input[++i];
            char c0 = input[++i];
            //16进制转10进制
            output[outputLength_++] = (hex2dec(c1) << 4) + hex2dec(c0);
        } else if (c == '+') {
            output[outputLength_++] = ' ';
        } else {
            output[outputLength_++] = c;
        }
    }
    *outputLength = outputLength_;
    return output;
}
