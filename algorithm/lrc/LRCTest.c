#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "LRC.h"
#include "../base16/base16.h"

void showHelp() {
    printf("usage: LRC hex xxxx\n");
    printf("       LRC str xxxx\n");
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc == 3) {
        if (strcmp("hex", argv[1]) == 0) {
            unsigned char* bytes = base16_decode(argv[2]);
            unsigned short nBytes = strlen(argv[2]) >> 1;
            unsigned char lrc = LRC(bytes, nBytes);
            printf("hex:%x\n", lrc);
        } else if (strcmp("str", argv[1]) == 0) {
            unsigned char lrc = LRC((unsigned char *)argv[2], strlen(argv[2]) >> 1);
            printf("hex:%x\n", lrc);
        } else {
            showHelp();
        }
    } else {
        showHelp();
    }
    return 0;
}
