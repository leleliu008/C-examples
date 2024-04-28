#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
        "base64-encode [--no-wrap] <STR>\n"
        COLOR_OFF
        "    encode <STR> using base64 algorithm.\n\n"
        COLOR_GREEN
        "base64-encode [--no-wrap] < /bin/gmake\n"
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
            "base64-encode [--no-wrap] <STR>\n"
            "    encode <STR> using base64 algorithm.\n\n"
            "base64-encode [--no-wrap] < /bin/gmake\n"
            "    encode data using base64 algorithm.\n"
        );
    }
}

static int base64_encode_stream(bool wrap) {
    unsigned char readBuf[1023];

    for (;;) {
        ssize_t readSize = read(STDIN_FILENO, readBuf, 1023);

        if (readSize < 0) {
            perror(NULL);
            return 1;
        }

        if (readSize == 0) {
            if (wrap) {
                printf("\n");
            }

            return 0;
        }

        size_t outputSize = get_base64_encode_output_length_in_bytes(readSize);
        char   outputBuff[outputSize + 1U];

        int ret = base64_encode(outputBuff, outputSize + 1U, readBuf, readSize);

        if (ret != 0) {
            return ret;
        }

        ssize_t writtenSize = write(STDOUT_FILENO, outputBuff, outputSize);

        if (writtenSize == -1) {
            perror(NULL);
            return 1;
        }

        if ((size_t)writtenSize != outputSize) {
            fprintf(stderr, "not fully written to stdout.\n");
            return 1;
        }
    }
}

static int base64_encode_string(bool wrap, const char * inputString) {
    if (inputString[0] == '\0') {
        fprintf(stderr, "base64-encode <STR>, <STR> should be a non-empty string.");
        return 1;
    }

    size_t inputSize = strlen(inputString);

    size_t outputSize = get_base64_encode_output_length_in_bytes(inputSize);
    char   outputBuff[outputSize + 1U];

    int ret = base64_encode(outputBuff, outputSize + 1U, (unsigned char *)inputString, inputSize);

    if (ret != 0) {
        return ret;
    }

    ssize_t writtenSize = write(STDOUT_FILENO, outputBuff, outputSize);

    if (writtenSize == -1) {
        perror(NULL);
        return 1;
    }

    if ((size_t)writtenSize != outputSize) {
        fprintf(stderr, "not fully written to stdout.\n");
        return 1;
    }

    if (wrap) {
        printf("\n");
    }

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        return base64_encode_stream(true);
    }

    if (argc == 2) {
               if (strcmp(argv[1], "-h") == 0) {
            showHelp();
            return 0;
        } else if (strcmp(argv[1], "--help") == 0) {
            showHelp();
            return 0;
        } else if (strcmp(argv[1], "-V") == 0) {
            printf("%s\n", "1.0.0");
            return 0;
        } else if (strcmp(argv[1], "--version") == 0) {
            printf("%s\n", "1.0.0");
            return 0;
        } else if (strcmp(argv[1], "--no-wrap") == 0) {
            return base64_encode_stream(false);
        } else {
            return base64_encode_string(true, argv[1]);
        }
    }

    if (argc == 3) {
        if (strcmp(argv[1], "--no-wrap") == 0) {
            return base64_encode_string(false, argv[2]);
        } else if (strcmp(argv[1], "--") == 0) {
            return base64_encode_string(true, argv[2]);
        } else {
            fprintf(stderr, "unrecognized option: %s\n", argv[1]);
            return 1;
        }
    }

    fprintf(stderr, "too many arguments.\n");
    return 2;
}
