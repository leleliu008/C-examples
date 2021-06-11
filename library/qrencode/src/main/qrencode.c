//http://blog.fpliu.com/it/software/qrencode/include/qrencode.h/QRcode_encodeString

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <qrencode.h>

static void help(int exitCode) {
    printf("usage:\n");
    printf("    -h|--help\n");
    printf("    -V|--version\n\n");
    printf("    qrencode <INPUT>\n");
    printf("    echo | qrencode\n");
    exit(exitCode);
}

static void version() {
    printf("%s\n", "1.0.0");
}

static int qrencode(char* input) {
    QRcode* qrcode = QRcode_encodeString(input, 1, QR_ECLEVEL_H, QR_MODE_8, 1);

    if (NULL == qrcode) {
        extern int errno;
        printf("error occurred. code is %d\n", errno);
        return errno;
    }

    int i, j, width = qrcode->width;
    for (i = 0; i < width; i++) {
        for (j = 0; j < width; j++) { 
            if (qrcode->data[(i * width) + j] & 0x1) {
                printf("\033[40m  \033[0m");
            } else {
                printf("\033[47m  \033[0m");
            }
        }
        printf("\n");
    }

    QRcode_free(qrcode);

    return 0;
}

int main(int argc, char* argv[]) {
    if (1 == argc) {
        char input[100];
        scanf("%s\n", input);
        return qrencode(input);
    } else if (2 == argc) {
        if (strcmp("-h", argv[1]) == 0) {
            help(0);
        } else if (strcmp("--help", argv[1]) == 0) {
            help(0);
        } else if (strcmp("-V", argv[1]) == 0) {
            version();
            return 0;
        } else if (strcmp("--version", argv[1]) == 0) {
            version();
            return 0;
        } else {
            return qrencode(argv[1]);
        }
    } else {
        help(1);
    }
}
