#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <base16.h>

static void help(int exitCode) {
    printf("%s\n", "\
usage:\n\
-h|--help\n\
-V|--version\n\n\
base16 --encode <INPUT>\n\
base16 --decode <INPUT>\n\n\
echo | base16 --encode\n\
echo | base16 --decode\n");

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
        } else if (strcmp("--encode", argv[1]) == 0) {
            char input[100];
            scanf("%s\n", input);
            size_t inputLength = strlen(input);
            size_t outputLength = inputLength << 1;
            char output[outputLength + 1];
            memset(output, 0, outputLength + 1);
            if (base16_encode(output, (unsigned char *)argv[2], strlen(argv[2]), false) == 0) {
                printf("%s\n", output);
            } else {
                perror("base16 --encode failed.");
                return 1;
            }
        } else if (strcmp("--decode", argv[1]) == 0) {
            char input[100];
            scanf("%s\n", input);
            size_t inputLength = strlen(input);
            size_t outputLength = inputLength >> 1;
            unsigned char bytes[outputLength + 1];
            memset(bytes, 0, outputLength + 1);
            if (base16_decode(bytes, argv[2]) == 0) {
                printf("%s\n", (char*)bytes);
            } else {
                perror("base16 --decode failed.");
                return 1;
            }
        } else {
            help(1);
        }
    } else if (argc == 3) {
        if (strcmp("--encode", argv[1]) == 0) {
            size_t inputLength = strlen(argv[2]);
            size_t outputLength = inputLength << 1;
            char output[outputLength + 1];
            memset(output, 0, outputLength + 1);
            if (base16_encode(output, (unsigned char *)argv[2], strlen(argv[2]), false) == 0) {
                printf("%s\n", output);
            } else {
                perror("base16 --encode failed.");
                return 1;
            }
        } else if (strcmp("--decode", argv[1]) == 0) {
            size_t inputLength = strlen(argv[2]);
            size_t outputLength = inputLength >> 1;
            unsigned char bytes[outputLength + 1];
            memset(bytes, 0, outputLength + 1);
            if (base16_decode(bytes, argv[2]) == 0) {
                printf("%s\n", (char*)bytes);
            } else {
                perror("base16 --decode failed.");
                return 1;
            }
        } else {
            help(1);
        }
    } else {
        help(1);
    }
    return 0;
}
