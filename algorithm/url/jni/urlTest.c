//参考：http://blog.fpliu.com/it/data/text/coding/URL

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"url.h"

void showHelp() {
    printf("usage: url encode xxxx\n");
    printf("       url decode yyyy\n");
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc == 3) {
        if (strcmp("encode", argv[1]) == 0) {
            char *output = url_encode((unsigned char *)argv[2], strlen(argv[2]), 1);
            printf("url_encode(%s) = %s\n", argv[2], output);
            free(output);
        } else if (strcmp("decode", argv[1]) == 0) {
            unsigned short writenBytes = 0;
            unsigned char *output = url_decode(argv[2], &writenBytes);
            char outputStr[writenBytes + 1];
            memset(outputStr, 0, writenBytes + 1);
            memcpy(outputStr, output, writenBytes);
            printf("url_decode(%s) = %s\n", argv[2], output);
            free(output);
        } else {
            showHelp();
        }
    } else {
        showHelp();
    }
    return 0;
}
