//参考：http://blog.fpliu.com/it/data/text/coding/URL

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"URL.h"

void showHelp() {
    printf("usage: URL encode xxxx\n");
    printf("       URL decode yyyy\n");
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc == 3) {
        if (strcmp("encode", argv[1]) == 0) {
            char *output = url_encode((unsigned char *)argv[2], strlen(argv[2]), 1);
            printf("url_encode(%s) = %s\n", argv[2], output);
            free(output);
        } else if (strcmp("decode", argv[1]) == 0) {
            size_t writenBytes = 0;
            unsigned char *bytes = url_decode(argv[2], &writenBytes);
            
            char str[writenBytes + 1];
            memset(str, 0, writenBytes + 1);
            memcpy(str, bytes, writenBytes);
            
            printf("url_decode(%s) = %s\n", argv[2], str);
            
            free(bytes);
        } else {
            showHelp();
        }
    } else {
        showHelp();
    }
    return 0;
}
