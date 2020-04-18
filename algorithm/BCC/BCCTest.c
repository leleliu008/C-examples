#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "BCC.h"
#include "../base16/base16.h"

void showHelp() {
    printf("usage: BCC hex xxxx\n");
    printf("       BCC str xxxx\n");
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc == 3) {
        if (strcmp("hex", argv[1]) == 0) {
            unsigned char* bytes = base16_decode(argv[2]);
            unsigned short nBytes = strlen(argv[2]) >> 1;
            unsigned char bcc = BCC(bytes, nBytes);
            printf("hex:%x\n", bcc);
        } else if (strcmp("str", argv[1]) == 0) {
            unsigned char bcc = BCC((unsigned char *)argv[2], strlen(argv[2]) >> 1);
            printf("hex:%x\n", bcc);
        } else {
            showHelp();
        }
    } else {
        showHelp();
    }
    return 0;
}
