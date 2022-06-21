#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <base16.h>
#include <bcc.h>

static void help(int exitCode) {
    printf("usage:\n");
    printf("    -h|--help\n");
    printf("    -V|--version\n\n");
    printf("    bccsum hex <INPUT>\n");
    printf("    bccsum str <INPUT>\n\n");
    printf("    echo | bccsum hex\n");
    printf("    echo | bccsum str\n");
    exit(exitCode);
}

static void version() {
    printf("%s\n", "1.0.0");
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        if (strcmp("-h", argv[1]) == 0) {
            help(0);
        } else if (strcmp("--help", argv[1]) == 0) {
            help(0);
        } else if (strcmp("-V", argv[1]) == 0) {
            version();
        } else if (strcmp("--version", argv[1]) == 0) {
            version();
        } else if (strcmp("hex", argv[1]) == 0) {
            char input[100];
            scanf("%s", input);
            unsigned short nBytes = strlen(input) >> 1;
            unsigned char bytes[nBytes];
            if (base16_decode(bytes, input) == 0) {
                unsigned char bccsum  = bcc(bytes, nBytes);
                printf("%x\n", bccsum);
            } else {
                perror("invalid base16 encode str.");
                return 1;
            }
        } else if (strcmp("hex", argv[1]) == 0) {
            char input[100];
            scanf("%s", input);
            unsigned char bccsum  = bcc((unsigned char*)input, strlen(input));
            printf("%x\n", bccsum);
        } else {
            help(1);
        }
    } else if (argc == 3) {
        if (strcmp("hex", argv[1]) == 0) {
            unsigned short nBytes = strlen(argv[2]) >> 1;
            unsigned char bytes[nBytes];
            if (base16_decode(bytes, argv[2]) == 0) {
                unsigned char bccsum  = bcc(bytes, nBytes);
                printf("%x\n", bccsum);
            } else {
                perror("invalid base16 encode str.");
                return 1;
            }
        } else if (strcmp("str", argv[1]) == 0) {
            unsigned char bccsum = bcc((unsigned char *)argv[2], strlen(argv[2]) >> 1);
            printf("%x\n", bccsum);
        } else {
            help(1);
        }
    } else {
        help(1);
    }
    return 0;
}
