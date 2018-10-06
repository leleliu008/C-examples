//http://blog.fpliu.com/it/data/text/encoding/Base16

#include<stdlib.h>
#include<string.h>
#include"base16.h"

static char base16EncodeTable[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

char* base16_encode(unsigned char* input, unsigned short inputLength) {
    unsigned short i;
    unsigned char highByte, lowByte;
    char *output = (char *)calloc(2 * inputLength, sizeof(char));
    for (i = 0; i < inputLength; i++) {
        //向右移动4bit，获得高4bit
        highByte = input[i] >> 4;
        //与0x0f做位与运算，获得低4bit
        lowByte = input[i] & 0x0f;

        //由于高4bit和低4bit都只有4个bit，他们转换成10进制的数字，范围都在0 ～ 15闭区间内
        //大端模式
        output[i * 2] = base16EncodeTable[highByte];
        output[i * 2 + 1] = base16EncodeTable[lowByte];
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

//input指向的字符串长度必须是2的整数倍
//outputLength是解码后的字节数组长度
unsigned char* base16_decode(char* input, unsigned short *outputLength) {
    unsigned int inputLength = strlen(input);
    unsigned int halfInputLength = inputLength / 2;
    unsigned char *output = (unsigned char *)calloc(halfInputLength, sizeof(unsigned char));
    int i;
    for(i = 0; i < halfInputLength; i++) {
        //16进制数字转换为10进制数字的过程
        output[i] = hex2dec(input[2 * i]) * 16 + hex2dec(input[2 * i + 1]);
    }
    *outputLength = halfInputLength;
    return output;
}
