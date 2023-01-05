//http://blog.fpliu.com/it/data/text/coding/Base16

#include <string.h>
#include "base16.h"

int base16_encode(char * output, const unsigned char * input, size_t inputSizeInBytes, bool isToUpper) {
    const char * table = isToUpper ? "0123456789ABCDEF" : "0123456789abcdef";

    unsigned char highByte, lowByte;
    size_t i, j;

    for (i = 0; i < inputSizeInBytes; i++) {
        //向右移动4bit，获得高4bit
        highByte = input[i] >> 4;
        //与0x0f做位与运算，获得低4bit
        lowByte = input[i] & 0x0F;

        //由于高4bit和低4bit都只有4个bit，他们转换成10进制的数字，范围都在0 ～ 15闭区间内
        //大端模式
        j = i << 1;
        output[j] = table[highByte];
        output[j + 1] = table[lowByte];
    }

    return 0;
}

//把16进制字符转换成10进制表示的数字
//通过man ascii命令查看ASCII编码表即可得到如下转换逻辑
static short hex2dec(char c) {
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

int base16_decode(unsigned char* output, const char* input, size_t inputSizeInBytes) {
    if (inputSizeInBytes == 0) {
        inputSizeInBytes = strlen(input);
    }

    //input指向的字符串长度必须是2的整数倍，也就是必须是偶数
    if (1 == (inputSizeInBytes & 1)) {
        return 1;
    }

    size_t halfInputSize = inputSizeInBytes >> 1;
    size_t i, j;

    for (i = 0; i < halfInputSize; i++) {
        //16进制数字转换为10进制数字的过程
        j = i << 1;
        output[i] = (hex2dec(input[j]) << 4) + hex2dec(input[j + 1]);
    }

    return 0;
}
