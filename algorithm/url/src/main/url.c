// http://blog.fpliu.com/it/data/text/coding/URL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <url.h>

static void help(int exitCode) {
    printf("usage:\n");
    printf("    -h|--help\n");
    printf("    -V|--version\n\n");
    printf("    url --encode <INPUT>\n");
    printf("    url --decode <INPUT>\n\n");
    printf("    echo | url --encode\n");
    printf("    echo | url --decode\n");
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
            size_t outputLength = 3 * inputLength + 1;
            char output[outputLength];
            memset(output, 0, outputLength);
            if (url_encode(output, (unsigned char *)input, inputLength, 1) == 0) {
                printf("%s\n", output);
            } else {
                perror("url --encode failed.");
                return 1;
            }
        } else if (strcmp("--decode", argv[1]) == 0) {
            char input[100];
            scanf("%s\n", input);
            size_t inputLength = strlen(input);
            unsigned char output[inputLength + 1];
            memset(output, 0, inputLength + 1);
            size_t writenBytes = 0;
            if (url_decode(output, &writenBytes, input) == 0) {
                printf("%s\n", (char*)output);
            } else {
                perror("url --decode failed.");
                return 1;
            }
        }
    } else if (argc == 3) {
        if (strcmp("--encode", argv[1]) == 0) {
            size_t inputLength = strlen(argv[2]);
            size_t outputLength = 3 * inputLength + 1;
            char output[outputLength];
            memset(output, 0, outputLength);
            if (url_encode(output, (unsigned char *)argv[2], inputLength, 1) == 0) {
                printf("%s\n", output);
            } else {
                perror("url --encode failed.");
                return 1;
            }
        } else if (strcmp("--decode", argv[1]) == 0) {
            size_t inputLength = strlen(argv[2]);
            unsigned char output[inputLength + 1];
            memset(output, 0, inputLength + 1);
            size_t writenBytes = 0;
            if (url_decode(output, &writenBytes, argv[2]) == 0) {
                printf("%s\n", (char*)output);
            } else {
                perror("url --decode failed.");
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
