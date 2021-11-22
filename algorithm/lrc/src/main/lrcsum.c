#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <base16.h>
#include "lrc.h"

void showHelp() {
    printf("usage: lrc hex xxxx\n");
    printf("       lrc str xxxx\n");
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc == 3) {
        if (strcmp("hex", argv[1]) == 0) {
            unsigned short nBytes = strlen(argv[2]) >> 1;
            unsigned char bytes[nBytes + 1];
            memset(bytes, 0, nBytes + 1);
            base16_decode(bytes, argv[2]);
            unsigned char lrcsum = lrc(bytes, nBytes);
            printf("%x\n", lrcsum);
        } else if (strcmp("str", argv[1]) == 0) {
            unsigned char lrcsum = lrc((unsigned char *)argv[2], strlen(argv[2]) >> 1);
            printf("%x\n", lrcsum);
        } else {
            showHelp();
        }
    } else {
        showHelp();
    }
    return 0;
}
