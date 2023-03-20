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
        "base64-encode --help\n"
        "base64-encode -h\n"
        COLOR_OFF
        "    show help of this command.\n\n"
        COLOR_GREEN
        "base64-encode --version\n"
        "base64-encode -V\n"
        COLOR_OFF
        "    show version of this command.\n\n"
        COLOR_GREEN
        "base64-encode <STR>\n"
        COLOR_OFF
        "    encode <STR> using base64 algorithm.\n\n"
        COLOR_GREEN
        "base64-encode < /bin/gmake\n"
        COLOR_OFF
        "    encode data using base64 algorithm.\n";

        printf("%s\n", str);
    } else {
        printf("%s\n",
            "usage:\n\n"
            "base64-encode --help\n"
            "base64-encode -h\n"
            "    show help of this command.\n\n"
            "base64-encode --version\n"
            "base64-encode -V\n"
            "    show version of this command.\n\n"
            "base64-encode <STR>\n"
            "    encode <STR> using base64 algorithm.\n\n"
            "base64-encode < /bin/gmake\n"
            "    encode data using base64 algorithm.\n"
        );
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        unsigned char inputBuff[1024];

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

            size_t outputSize = get_base64_encode_output_length_in_bytes(inputSize) + 1;
            char   outputBuff[outputSize];

            int ret = base64_encode(outputBuff, outputSize, inputBuff, inputSize);

            if (ret == 0) {
                if (write(STDOUT_FILENO, outputBuff, outputSize - 1) < 0) {
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
            fprintf(stderr, "base64-encode <STR>, <STR> should be a non-empty string.");
            return 1;
        }

        size_t outputSize = get_base64_encode_output_length_in_bytes(inputSize) + 1;
        char   outputBuff[outputSize];

        int ret = base64_encode(outputBuff, outputSize + 1, (unsigned char *)argv[1], inputSize);

        if (ret == 0) {
            if (write(STDOUT_FILENO, outputBuff, outputSize - 1) < 0) {
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
