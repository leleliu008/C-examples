#include<string.h>

//从一个字符串中删除一个特定字符
//注意：是直接修改原来的字符串
void delChar(char *str, char c) {
    if(NULL == str) {
        return;
    }
    int length = strlen(str);
    for(int i = 0; i < length; i++) {
        if(str[i] == c) {
            //从后往前移动
            for(int j = i + 1; j < length; j++) {
                str[j - 1] = str[j];
            }
            str[length - 1] = '\0';
            break;
        }
    }
}

//字节流转换为十六进制字符串
void bytes2HexStr(char *dest, const unsigned char* source, unsigned short sourceLen) {
    unsigned short i;
    unsigned char highByte, lowByte;

    for (i = 0; i < sourceLen; i++) {
        highByte = source[i] >> 4;
        lowByte = source[i] & 0x0f;

        highByte += 0x30;

        if (highByte > 0x39) {
            dest[i * 2] = highByte + 0x07;
        } else {
            dest[i * 2] = highByte;
        }

        lowByte += 0x30;
        if (lowByte > 0x39) {
            dest[i * 2 + 1] = lowByte + 0x07;
        } else {
            dest[i * 2 + 1] = lowByte;
        }
    }
    return;
}

void bytes2hexStr(char *dest, const unsigned char* source, unsigned short sourceLen) {
    bytes2HexStr(dest, source, sourceLen);
    
    #ifdef DEBUG
        LOGI("bytes2HexStr = %s", dest);
    #endif

    size_t length = strlen(dest);
    for (int i = 0; i < length; i++) {
        if (dest[i] >= 'A' && dest[i] <= 'Z') {
            dest[i] += 32;
        }
    }
}
