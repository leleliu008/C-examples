// http://blog.fpliu.com/it/software/mbedTLS/include/base64.h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <base64.h>

static void help(int exitCode) {
    printf("usage:\n");
    printf("    -h|--help\n");
    printf("    -V|--version\n\n");
    printf("    base64 --encode <INPUT>\n");
    printf("    base64 --decode <INPUT>\n\n");
    printf("    echo | base64 --encode\n");
    printf("    echo | base64 --decode\n");
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
            size_t  inputBufferSizeInBytes = strlen(input);
            size_t outputBufferSizeInBytes = get_base64_encode_output_length_in_bytes(inputBufferSizeInBytes) + 1;
            char outputBuffer[outputBufferSizeInBytes];
            memset(outputBuffer, 0, outputBufferSizeInBytes);
            if (0 == base64_encode(outputBuffer, outputBufferSizeInBytes, (unsigned char*)input, inputBufferSizeInBytes)) {
                printf("%s\n", outputBuffer);
                return 0;
            } else {
                perror("base64 --encode failed.");
                return 1;
            }
        } else if (strcmp("--decode", argv[1]) == 0) {
            char input[100];
            scanf("%s\n", input);
            size_t  inputBufferSizeInBytes = strlen(input);
            size_t outputBufferSizeInBytes = (inputBufferSizeInBytes >> 2) * 3 + 1;
            unsigned char output[outputBufferSizeInBytes];
            memset(output, 0, outputBufferSizeInBytes);
            size_t writtenToOutputBufferCountInBytes = 0;
            if (0 == base64_decode(output, outputBufferSizeInBytes, &writtenToOutputBufferCountInBytes, input)) {
                printf("%s\n", output);
                return 0;
            } else {
                perror("base64 --decode failed.");
                return 1;
            }

        }
    } else if (argc == 3) {
        if (strcmp("--encode", argv[1]) == 0) {
            size_t  inputBufferSizeInBytes = strlen(argv[2]);
            size_t outputBufferSizeInBytes = get_base64_encode_output_length_in_bytes(inputBufferSizeInBytes) + 1;
            char output[outputBufferSizeInBytes];
            memset(output, 0, outputBufferSizeInBytes);
            if (0 == base64_encode(output, outputBufferSizeInBytes, (unsigned char*)argv[2], inputBufferSizeInBytes)) {
                printf("%s\n", output);
                return 0;
            } else {
                perror("base64 --encode failed.");
                return 1;
            }
        } else if (strcmp("--decode", argv[1]) == 0) {
            size_t  inputBufferSizeInBytes = strlen(argv[2]);
            size_t outputBufferSizeInBytes = (inputBufferSizeInBytes >> 2) * 3 + 1;
            unsigned char output[outputBufferSizeInBytes];
            memset(output, 0, outputBufferSizeInBytes);
            size_t writtenToOutputBufferCountInBytes = 0;
            if (0 == base64_decode(output, outputBufferSizeInBytes, &writtenToOutputBufferCountInBytes, argv[2])) {
                printf("%s\n", output);
                return 0;
            } else {
                perror("base64 --decode failed.");
                return 1;
            }
        }
    } else {
        help(1);
    }
    return 0;
}
