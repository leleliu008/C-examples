#include <stdio.h>
#include <string.h>

#include <sha256sum.h>

static void show_help(const char * programName) {
    printf("USAGE: %s [--string <STR>] [--file <FILE>]\n", programName);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        show_help(argv[0]);
        return 0;
    }

    if (strcmp(argv[1], "") == 0) {
        show_help(argv[0]);
    } else if (strcmp(argv[1], "--help") == 0) {
        show_help(argv[0]);
    } else if (strcmp(argv[1], "--string") == 0) {
        if (argv[2] == NULL) {
            fprintf(stderr, "USAGE: %s --string <STR> , <STR> is unspecifed.\n", argv[0]);
            return 0;
        }

        if (argv[2][0] == '\0') {
            fprintf(stderr, "USAGE: %s --string <STR> , <STR> should be a non-empty string.\n", argv[0]);
            return 0;
        }

        char sha256sum[65] = {0};

        int ret = sha256sum_of_string(sha256sum, argv[2]);

        if (ret == 0) {
            printf("%s\n", sha256sum);
            return 0;
        } else {
            perror(NULL);
            return 1;
        }
    } else if (strcmp(argv[1], "--file") == 0) {
        if (argv[2] == NULL) {
            fprintf(stderr, "USAGE: %s --file <FILE> , <FILE> is unspecifed.\n", argv[0]);
            return 0;
        }

        if (argv[2][0] == '\0') {
            fprintf(stderr, "USAGE: %s --file <FILE> , <FILE> should be a non-empty string.\n", argv[0]);
            return 0;
        }

        char sha256sum[65] = {0};

        int ret = sha256sum_of_file(sha256sum, argv[2]);

        if (ret == 0) {
            printf("%s  %s\n", sha256sum, argv[2]);
            return 0;
        } else {
            perror(argv[2]);
            return 1;
        }
    } else {
        printf("unrecognized argument: %s\n", argv[1]);
        return 1;
    }

    return 0;
}
