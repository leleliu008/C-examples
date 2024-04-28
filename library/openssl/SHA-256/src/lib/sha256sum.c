#include <errno.h>
#include <stdio.h>
#include <string.h>

#include <openssl/sha.h>

#include "sha256sum.h"

static inline void tohex(char buf[65], const unsigned char * sha256Bytes) {
    const char * const table = "0123456789abcdef";

    for (size_t i = 0U; i < SHA256_DIGEST_LENGTH; i++) {
        size_t j = i << 1;
        buf[j]      = table[sha256Bytes[i] >> 4];
        buf[j + 1U] = table[sha256Bytes[i] & 0x0F];
    }
}

int sha256sum_of_bytes(char outputBuffer[65], unsigned char * inputBuffer, size_t inputBufferSizeInBytes) {
    if (outputBuffer == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (inputBuffer == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (inputBufferSizeInBytes == 0U) {
        errno = EINVAL;
        return -1;
    }

    unsigned char sha256Bytes[SHA256_DIGEST_LENGTH] = {0};
 
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, inputBuffer, inputBufferSizeInBytes);
    SHA256_Final(sha256Bytes, &ctx);

    tohex(outputBuffer, sha256Bytes);

    return 0;
}

int sha256sum_of_string(char outputBuffer[65], const char * str) {
    if (str == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (str[0] == '\0') {
        errno = EINVAL;
        return -1;
    }

    unsigned char sha256Bytes[SHA256_DIGEST_LENGTH] = {0};
 
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, str, strlen(str));
    SHA256_Final(sha256Bytes, &ctx);

    tohex(outputBuffer, sha256Bytes);

    return 0;
}

int sha256sum_of_stream(char outputBuffer[65], FILE * file) {
    if (outputBuffer == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (file == NULL) {
        errno = EINVAL;
        return -1;
    }

    unsigned char sha256Bytes[SHA256_DIGEST_LENGTH] = {0};
 
    SHA256_CTX ctx;
    SHA256_Init(&ctx);

    unsigned char buffer[1024];

    for (;;) {
        size_t size = fread(buffer, 1, 1024, file);

        if (ferror(file)) {
            errno = EIO;
            return -1;
        }

        if (size > 0U) {
            SHA256_Update(&ctx, buffer, size);
        }

        if (feof(file)) {
            break;
        }
    }

    SHA256_Final(sha256Bytes, &ctx);

    tohex(outputBuffer, sha256Bytes);

    return 0;
}

int sha256sum_of_file(char outputBuffer[65], const char * filepath) {
    if (outputBuffer == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (filepath == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (filepath[0] == '\0') {
        errno = EINVAL;
        return -1;
    }

    FILE * file = fopen(filepath, "rb");

    if (file == NULL) {
        errno = EINVAL;
        return -1;
    }

    int ret = sha256sum_of_stream(outputBuffer, file);

    fclose(file);

    return ret;
}
