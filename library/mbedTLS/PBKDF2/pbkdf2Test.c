//http://blog.fpliu.com/it/software/development/language/C/library/mbedTLS/include/pkcs5.h

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include"mbedtls/pkcs5.h"

#define OUTPUT_LENGTH_IN_BYTES         32
#define BASE_16_OUTPUT_LENGTH_IN_BYTES 32 * 2 + 1
#define ITERATION_COUNT 1000

void showHelp() {
    printf("usage: pbkdf2 <option> <PASSWORD> <SALT>\n");
    printf("option: -x lower case, default true\n");
    printf("        -X upper case\n");
    printf("example:pbkdf2 -X 123456 abcdefg\n");
    exit(1);
}

void base16(unsigned char input[OUTPUT_LENGTH_IN_BYTES], char* output, bool isToUpper) {
    const char* format = isToUpper ? "%02X" : "%02x";
    char tmp[3] = {0};
    for(int i = 0; i < OUTPUT_LENGTH_IN_BYTES; i++) {
        sprintf(tmp, format, input[i]);
        strcat(output, tmp);
    }
}

void performPBKDF2_HMAC_SHA256(char* password, char* salt, bool isToUpper) {
    unsigned char output[OUTPUT_LENGTH_IN_BYTES] = {0};

    mbedtls_md_context_t md_context;
    mbedtls_md_init(&md_context);
    
    extern const mbedtls_md_info_t mbedtls_sha256_info;
    int resultCode = mbedtls_md_setup(&md_context, &mbedtls_sha256_info, 1);
    if (0 == resultCode) {
        resultCode = mbedtls_pkcs5_pbkdf2_hmac(&md_context, (unsigned char*)password, strlen(password), (unsigned char*)salt, strlen(salt), ITERATION_COUNT, OUTPUT_LENGTH_IN_BYTES, output);
        if (0 == resultCode) {
            mbedtls_md_free(&md_context);
            //为了便于比较，通常会把字节数据用base16编码
            char base16Encoded[BASE_16_OUTPUT_LENGTH_IN_BYTES] = {0};
            base16(output, base16Encoded, isToUpper);
            printf("pbkdf2_hmac_sha256(password=%s,salt=%s)=%s\n", password, salt, base16Encoded);
            return;
        }
    }
    printf("occrued error, code is %d\n", resultCode);
}

int main(int argc, char* argv[]) {
    if (4 == argc) {
        if (strcmp("-x", argv[1]) == 0) {
            performPBKDF2_HMAC_SHA256(argv[2], argv[3], false);
        } else if (strcmp("-X", argv[1]) == 0) {
            performPBKDF2_HMAC_SHA256(argv[2], argv[3], true);
        } else {
            showHelp();
        }
    }

    return 0;
}
