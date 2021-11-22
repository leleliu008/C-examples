//http://blog.fpliu.com/it/algorithm/check/LRC

#include "lrc.h"

unsigned char lrc(unsigned char* bytes, size_t nBytes) {
    unsigned char byte = 0;
    for (size_t i = 0; i < nBytes; i++) {
        byte += bytes[i];
        byte &= 0xFF;
    }
    return 256 - byte;
}
