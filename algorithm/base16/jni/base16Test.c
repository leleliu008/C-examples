#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"base16.h"

void showHelp() {
    printf("usage: base16 encode xxxx\n");
    printf("       base16 decode yyyy\n");
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc == 3) {
        if (strcmp("encode", argv[1]) == 0) {
            char *output = base16_encode((unsigned char *)argv[2], strlen(argv[2]), 0);
            printf("base16(%s) = %s\n", argv[2], output);
            free(output);
        } else if (strcmp("decode", argv[1]) == 0) {
            unsigned short writenBytes = 0;
            unsigned char *output = base16_decode(argv[2], &writenBytes);
            char outputStr[writenBytes + 1];
            memset(outputStr, 0, writenBytes + 1);
            memcpy(outputStr, output, writenBytes);
            printf("base16(%s) = %s\n", argv[2], output);
            free(output);
        } else {
            showHelp();
        }
    } else {
        showHelp();
    }
    return 0;
}
