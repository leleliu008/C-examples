#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <base64.h>

#define COLOR_GREEN  "\033[0;32m"
#define COLOR_OFF    "\033[0m"

static void showHelp() {
    if (isatty(STDOUT_FILENO)) {
        const char * str = "usage:\n\n"
        COLOR_GREEN
        "base64-decode --help\n"
        "base64-decode -h\n"
        COLOR_OFF
        "    show help of this command.\n\n"
        COLOR_GREEN
        "base64-decode --version\n"
        "base64-decode -V\n"
        COLOR_OFF
        "    show version of this command.\n\n"
        COLOR_GREEN
        "base64-decode <BASE64-ENCODED-STR>\n"
        COLOR_OFF
        "    decode <BASE64-ENCODED-STR> using base64 algorithm.\n\n"
        COLOR_GREEN
        "printf '%s' YWJjZA== | base64-decode\n"
        COLOR_OFF
        "    decode data using base64 algorithm.\n";

        printf("%s\n", str);
    } else {
        printf("%s\n",
            "usage:\n\n"
            "base64-decode --help\n"
            "base64-decode -h\n"
            "    show help of this command.\n\n"
            "base64-decode --version\n"
            "base64-decode -V\n"
            "    show version of this command.\n\n"
            "base64-decode <BASE64-ENCODED-STR>\n"
            "    decode <BASE64-ENCODED-STR> using base64 algorithm.\n\n"
            "printf '%s' 7F454C46 | base64-decode\n"
            "    decode data using base64 algorithm.\n"
        );
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        char inputBuff[1024];

        for (;;) {
            ssize_t inputSize = read(STDIN_FILENO, inputBuff, 1024);

            if (inputSize < 0) {
                perror(NULL);
                return 1;
            }

            if (inputSize == 0) {
                if (isatty(STDOUT_FILENO)) {
                    printf("\n");
                }

                return 0;
            }

            size_t        outputBuffSize = (inputSize * 3U) >> 2;
            unsigned char outputBuff[outputBuffSize];
            size_t        outputSize;

            int ret = base64_decode(outputBuff, outputBuffSize, &outputSize, inputBuff);

            if (ret == 0) {
                if (write(STDOUT_FILENO, outputBuff, outputSize) < 0) {
                    perror(NULL);
                    return 1;
                }
            } else {
                return ret;
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

        if (inputSize == 0U) {
            fprintf(stderr, "base64-encode <BASE64-ENCODED-STR>, <BASE64-ENCODED-STR> should be a non-empty string.");
            return 1;
        }

        size_t        outputBuffSize = (inputSize * 3U) >> 2;
        unsigned char outputBuff[outputBuffSize];
        size_t        outputSize;

        int ret = base64_decode(outputBuff, outputBuffSize, &outputSize, argv[1]);

        if (ret == 0) {
            if (write(STDOUT_FILENO, outputBuff, outputSize) < 0) {
                perror(NULL);
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
