//http://blog.fpliu.com/it/software/qrencode/include/qrencode.h/QRcode_encodeString

#include <qrencode.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    if (1 == argc) {
        printf("please provide a string to encode.\n");
        return 1;
    }

    QRcode* qrcode = QRcode_encodeString(argv[1], 1, QR_ECLEVEL_H, QR_MODE_8, 1);
    
    if (!qrcode) {
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
