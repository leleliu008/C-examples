//参考：http://blog.fpliu.com/it/data/text/encoding/URL

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

short hex2dec(char c) {
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

static char dic[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

char* url_encode(unsigned char *input, unsigned short inputLength) {
    int outputLength = 0;
    //以最坏的情况分配内存
    char *output = (char *)calloc(3 * inputLength + 1, sizeof(char));
    int i = 0;
    for (i = 0; i < inputLength; i++) {
        unsigned char c = input[i];
        //这些字符保持原样
        if (('0' <= c && c <= '9') ||
            ('a' <= c && c <= 'z') ||
            ('A' <= c && c <= 'Z') || 
            c == '.' || c == '_' || c == '-' || c == '*') {
            output[outputLength++] = c;
        } else if (' ' == c) { //把空格编码成+
            output[outputLength++] = '+';
        } else { //其他字符都转换成%XY，XY是Base16编码
            //向右移动4bit，获得高4bit
            unsigned char highByte = c >> 4;
            //与0x0f做位与运算，获得低4bit
            unsigned char lowByte = c & 0x0f;
            //由于高4bit和低4bit都只有4个bit，他们转换成10进制的数字，范围都在0 ～ 15闭区间内
            //大端模式
            output[outputLength++] = '%';
            output[outputLength++] = dic[highByte];
            output[outputLength++] = dic[lowByte];
        }
    }
    return output;
}

unsigned char* url_decode(char *input, unsigned short *outputLength) {
    int inputLength = strlen(input);
    int outputLength_ = 0;
    //以最坏的情况分配内存
    unsigned char *output = (unsigned char *)calloc(inputLength + 1, sizeof(unsigned char));
    int i = 0;
    for (i = 0; i < inputLength; i++) {
        char c = input[i];
        if (c == '%') {
            char c1 = input[++i];
            char c0 = input[++i];
            //16进制转10进制
            int num = hex2dec(c1) * 16 + hex2dec(c0);
            output[outputLength_++] = num;
        } else if (c == '+') {
            output[outputLength_++] = ' ';
        } else {
            output[outputLength_++] = c;
        }
    }
    *outputLength = outputLength_;
    return output;
}
