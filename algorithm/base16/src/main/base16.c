#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
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
            unsigned char inputBuff[1024];
            size_t        inputSize;

            for (;;) {
                inputSize = fread(inputBuff, 1, 1024, stdin);

                if (ferror(stdin)) {
                    return 1;
                }

                size_t outputSize = inputSize << 1;
                char   outputBuff[outputSize];

                int ret = base16_encode(outputBuff, inputBuff, inputSize, true);

                if (ret == 0) {
                    if (fwrite(outputBuff, 1, outputSize, stdout) != outputSize || ferror(stdout)) {
                        return 1;
                    }
                } else {
                    return ret;
                }

                if (feof(stdin)) {
                    if (isatty(STDOUT_FILENO)) {
                        printf("\n");
                    }

                    return 0;
                }
            }
        } else {
            size_t inputSize = strlen(argv[2]);

            if (inputSize == 0) {
                fprintf(stderr, "base16 --encode <STR>, <STR> should be a non-empty string.");
                return 1;
            }

            size_t outputSize = inputSize << 1;
            char   outputBuff[outputSize];

            int ret = base16_encode(outputBuff, (unsigned char *)argv[2], inputSize, true);

            if (ret == 0) {
                if (fwrite(outputBuff, 1, outputSize, stdout) != outputSize || ferror(stdout)) {
                    return 1;
                }

                if (isatty(STDOUT_FILENO)) {
                    printf("\n");
                }
            } else {
                return ret;
            }
        }
    } else if (strcmp("--decode", argv[1]) == 0) {
        if (argv[2] == NULL) {
            char   inputBuff[1024];
            size_t inputSize;

            for (;;) {
                inputSize = fread(inputBuff, 1, 1024, stdin);

                if (ferror(stdin)) {
                    return 1;
                }

                size_t        outputSize = inputSize >> 1;
                unsigned char outputBuff[outputSize];

                int ret = base16_decode(outputBuff, inputBuff, inputSize);

                if (ret == 0) {
                    if (fwrite(outputBuff, 1, outputSize, stdout) != outputSize || ferror(stdout)) {
                        return 1;
                    }
                } else {
                    return ret;
                }

                if (feof(stdin)) {
                    if (isatty(STDOUT_FILENO)) {
                        printf("\n");
                    }

                    return 0;
                }
            }
        } else {
            size_t inputSize = strlen(argv[2]);

            size_t        outputSize = inputSize >> 1;
            unsigned char outputBuff[outputSize];

            int ret = base16_decode(outputBuff, argv[2], inputSize);

            if (ret == 0) {
                if (fwrite(outputBuff, 1, outputSize, stdout) != outputSize || ferror(stdout)) {
                    return 1;
                }

                if (isatty(STDOUT_FILENO)) {
                    printf("\n");
                }
            } else {
                return ret;
            }
        }
    } else {
        help(1);
    }

    return 0;
}
