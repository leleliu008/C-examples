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
            char *output = base16_encode((unsigned char *)argv[2], strlen(argv[2]), false);
            printf("base16(%s) = %s\n", argv[2], output);
            free(output);
        } else if (strcmp("decode", argv[1]) == 0) {
            unsigned char *bytes = base16_decode(argv[2]);
            unsigned short nBytes = strlen(argv[2]) >> 1;

            char str[nBytes + 1];
            memset(str, 0, nBytes + 1);
            memcpy(str, bytes, nBytes);

            printf("base16(%s) = %s\n", argv[2], str);
            free(bytes);
        } else {
            showHelp();
        }
    } else {
        showHelp();
    }
    return 0;
}
