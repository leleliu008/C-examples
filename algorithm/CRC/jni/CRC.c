//http://blog.fpliu.com/it/algorithm/check/CRC

#include"CRC.h"

static unsigned char CRC7_POLY = 0x09;

unsigned char CRC(unsigned char* bytes, size_t nBytes) {
    unsigned char crc = 0;
    for (size_t i = 0; i < nBytes; i++) {
        crc ^= bytes[i];
        for (size_t j = 0; j < 8; j++) {
            if (crc & 1) {
                crc ^= CRC7_POLY;
            }
            crc >>= 1;
        }
    }
    return crc;
}
