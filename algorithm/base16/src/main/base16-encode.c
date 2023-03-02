#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <base16.h>

#define COLOR_GREEN  "\033[0;32m"
#define COLOR_OFF    "\033[0m"

static void showHelp() {
    if (isatty(STDOUT_FILENO)) {
        const char * str = "usage:\n\n"
        COLOR_GREEN
        "base16-encode --help\n"
        "base16-encode -h\n"
        COLOR_OFF
        "    show help of this command.\n\n"
        COLOR_GREEN
        "base16-encode --version\n"
        "base16-encode -V\n"
        COLOR_OFF
        "    show version of this command.\n\n"
        COLOR_GREEN
        "base16-encode <STR>\n"
        COLOR_OFF
        "    encode <STR> using base16 algorithm.\n\n"
        COLOR_GREEN
        "head -c 4 /bin/gmake | base16-encode\n"
        COLOR_OFF
        "    encode data using base16 algorithm.\n";

        printf("%s\n", str);
    } else {
        printf("%s\n",
            "usage:\n\n"
            "base16-encode --help\n"
            "base16-encode -h\n"
            "    show help of this command.\n\n"
            "base16-encode --version\n"
            "base16-encode -V\n"
            "    show version of this command.\n\n"
            "base16-encode <STR>\n"
            "    encode <STR> using base16 algorithm.\n\n"
            "head -c 4 /bin/gmake | base16-encode\n"
            "    encode data using base16 algorithm.\n"
        );
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
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
    }

           if (strcmp(argv[1], "-h") == 0) {
        showHelp();
    } else if (strcmp(argv[1], "--help") == 0) {
        showHelp();
    } else if (strcmp(argv[1], "-V") == 0) {
        printf("%s\n", "1.0.0");
    } else if (strcmp(argv[1], "--version") == 0) {
        printf("%s\n", "1.0.0");
    } else {
        size_t inputSize = strlen(argv[1]);

        if (inputSize == 0) {
            fprintf(stderr, "base16-encode <STR>, <STR> should be a non-empty string.");
            return 1;
        }

        size_t outputSize = inputSize << 1;
        char   outputBuff[outputSize];

        int ret = base16_encode(outputBuff, (unsigned char *)argv[1], inputSize, true);

        if (ret == 0) {
            if (fwrite(outputBuff, 1, outputSize, stdout) != outputSize || ferror(stdout)) {
                return 1;
            }

            if (isatty(STDOUT_FILENO)) {
                printf("\n");
            }

            return 0;
        } else {
            return ret;
        }
    }
}
