#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sha256sum.h>

static void show_help(const char * programName) {
    printf("USAGE: %s [--string STR] [--file FILE]\n", programName);
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
        char * sha256sum = sha256sum_of_string(argv[2]);
        if (sha256sum == NULL) {
            perror("sha256sum_of_string");
            return 1;
        } else {
            printf("%s\n", sha256sum);
            return 0;
        }
    } else if (strcmp(argv[1], "--file") == 0) {
        if (argv[2] == NULL) {
            printf("filepath argument is not given.\n");
            return 1;
        }

        FILE * file = fopen(argv[2], "rb");

        if (file == NULL) {
            perror(argv[2]);
            return 1;
        }

        char * sha256sum = sha256sum_of_file(file);

        fclose(file);

        if (sha256sum == NULL) {
            perror("sha256sum_of_file");
            return 1;
        } else {
            printf("%s  %s\n", sha256sum, argv[2]);
            return 0;
        }
    } else {
        printf("unrecognized argument: %s\n", argv[1]);
        return 1;
    }

    return 0;
}
