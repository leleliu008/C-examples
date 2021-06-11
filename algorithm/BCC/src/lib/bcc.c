//http://blog.fpliu.com/it/algorithm/check/BCC

#include <bcc.h>

unsigned char bcc(unsigned char *bytes, size_t nBytes) {
    unsigned char byte = 0;
    for (size_t i = 0; i < nBytes; i++) {
        byte ^= bytes[i];
    }
    return byte;
}
