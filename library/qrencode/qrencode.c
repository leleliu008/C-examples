//http://blog.fpliu.com/it/software/qrencode/include/qrencode.h/QRcode_encodeString

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <qrencode.h>

static void show_help_then_exit(int exitCode) {
    const char * helpStr = "usage:\n    -h|--help\n    -V|--version\n\n    qrencode <INPUT>\n    echo | qrencode\n";

    if (exitCode == 0) {
        fprintf(stdout, "%s", helpStr);
    } else {
        fprintf(stderr, "%s", helpStr);
    }

    exit(exitCode);
}

static void show_version_then_exit() {
    printf("%s\n", "1.0.0");
    exit(0);
}

static int qr_encode(char * input) {
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
        char input[255];
        scanf("254%s\n", input);
        return qr_encode(input);
    } else if (2 == argc) {
        if (strcmp("-h", argv[1]) == 0) {
            show_help_then_exit(0);
        } else if (strcmp("--help", argv[1]) == 0) {
            show_help_then_exit(0);
        } else if (strcmp("-V", argv[1]) == 0) {
            show_version_then_exit();
            return 0;
        } else if (strcmp("--version", argv[1]) == 0) {
            show_version_then_exit();
            return 0;
        } else {
            return qr_encode(argv[1]);
        }
    } else {
        show_help_then_exit(1);
    }
}
