#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <base16.h>

static void help(int exitCode) {
    printf("%s\n", "\
usage:\n\n\
base16 -h\n\
base16 --help\n\n\
base16 -V\n\
base16 --version\n\n\
base16 --encode <STR>\n\
base16 --decode <STR>\n\n\
head -c 4 /bin/gmake | base16 --encode\n\
printf '%s' 7F454C46 | base16 --decode\n");

    exit(exitCode);
}

static void version() {
    printf("%s\n", "1.0.0");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        help(1);
    }

    if (strcmp("-h", argv[1]) == 0) {
        help(0);
    } else if (strcmp("--help", argv[1]) == 0) {
        help(0);
    } else if (strcmp("-V", argv[1]) == 0) {
        version();
    } else if (strcmp("--version", argv[1]) == 0) {
        version();
    } else if (strcmp("--encode", argv[1]) == 0) {
        if (argv[2] == NULL) {
            unsigned char inputBuff[100];
            size_t        inputSize;

            while ((inputSize = fread(inputBuff, 1, 100, stdin)) != 0) {
                size_t outputLength = (inputSize << 1) + 1;
                char   output[outputLength];
                memset(output, 0, outputLength);

                if (base16_encode(output, inputBuff, inputSize, true) == 0) {
                    printf("%s", output);
                } else {
                    return 1;
                }
            }
            printf("\n");
        } else if (strcmp(argv[2], "") == 0) {
            fprintf(stderr, "base16 --encode <STR>, <STR> must not be empty string.");
            return 1;
        } else {
            size_t inputLength = strlen(argv[2]);
            size_t outputLength = (inputLength << 1) + 1;
            char output[outputLength];
            memset(output, 0, outputLength);

            if (base16_encode(output, (unsigned char *)argv[2], inputLength, true) == 0) {
                printf("%s\n", output);
            } else {
                return 1;
            }
        }
    } else if (strcmp("--decode", argv[1]) == 0) {
        if (argv[2] == NULL) {
            char   inputBuff[100];
            size_t inputSize;

            while ((inputSize = fread(inputBuff, 1, 100, stdin)) != 0) {
                size_t outputLength = inputSize >> 1;
                char   output[outputLength];
                memset(output, 0, outputLength);

                if (base16_decode((unsigned char*)output, inputBuff, inputSize) == 0) {
                    fwrite(output, 1, outputLength, stdout);
                    fflush(stdout);
                } else {
                    return 1;
                }
            }
        } else {
            size_t inputLength = strlen(argv[2]);
            size_t outputLength = inputLength >> 1;
            unsigned char bytes[outputLength];
            memset(bytes, 0, outputLength);

            if (base16_decode(bytes, argv[2], inputLength) == 0) {
                printf("%s\n", (char*)bytes);
                fwrite(bytes, 1, outputLength, stdout);
                fflush(stdout);
            } else {
                return 1;
            }
        }
    } else {
        help(1);
    }

    return 0;
}
