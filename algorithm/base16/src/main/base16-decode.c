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
        "base16-decode --help\n"
        "base16-decode -h\n"
        COLOR_OFF
        "    show help of this command.\n\n"
        COLOR_GREEN
        "base16-decode --version\n"
        "base16-decode -V\n"
        COLOR_OFF
        "    show version of this command.\n\n"
        COLOR_GREEN
        "base16-decode <BASE16-ENCODED-STR>\n"
        COLOR_OFF
        "    decode <BASE16-ENCODED-STR> using base16 algorithm.\n\n"
        COLOR_GREEN
        "printf '%s' 7F454C46 | base16-decode\n"
        COLOR_OFF
        "    decode data using base16 algorithm.\n";

        printf("%s\n", str);
    } else {
        printf("%s\n",
            "usage:\n\n"
            "base16-decode --help\n"
            "base16-decode -h\n"
            "    show help of this command.\n\n"
            "base16-decode --version\n"
            "base16-decode -V\n"
            "    show version of this command.\n\n"
            "base16-decode <BASE16-ENCODED-STR>\n"
            "    decode <BASE16-ENCODED-STR> using base16 algorithm.\n\n"
            "printf '%s' 7F454C46 | base16-decode\n"
            "    decode data using base16 algorithm.\n"
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

            size_t        outputSize = inputSize >> 1;
            unsigned char outputBuff[outputSize];

            int ret = base16_decode(outputBuff, inputBuff, inputSize);

            if (ret != 0) {
                return ret;
            }

            if (write(STDOUT_FILENO, outputBuff, outputSize) < 0) {
                perror(NULL);
                return 1;
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
            fprintf(stderr, "base16-decode <BASE16-ENCODED-STR>, <BASE16-ENCODED-STR> should be a non-empty string.");
            return 1;
        }

        size_t        outputSize = inputSize >> 1;
        unsigned char outputBuff[outputSize];

        int ret = base16_decode(outputBuff, argv[1], inputSize);

        if (ret != 0) {
            return ret;
        }

        if (write(STDOUT_FILENO, outputBuff, outputSize) < 0) {
            perror(NULL);
            return 1;
        }

        if (isatty(STDOUT_FILENO)) {
            printf("\n");
        }

        return 0;
    }
}
