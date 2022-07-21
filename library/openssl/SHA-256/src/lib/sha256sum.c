#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <sha256sum.h>

char* sha256sum_of_bytes(unsigned char * inputBuffer, size_t inputBufferSizeInBytes) {
    unsigned char sha256Bytes[SHA256_DIGEST_LENGTH] = {0};
 
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, inputBuffer, inputBufferSizeInBytes);
    SHA256_Final(sha256Bytes, &ctx);
 
    char * sha256sum = (char*)calloc(SHA256_DIGEST_LENGTH * 2 + 1, sizeof(char));
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&sha256sum[i * 2], "%02x", (unsigned char)sha256Bytes[i]);
    }

    return sha256sum;
}

char* sha256sum_of_string(const char * str) {
    unsigned char sha256Bytes[SHA256_DIGEST_LENGTH] = {0};
 
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, str, strlen(str));
    SHA256_Final(sha256Bytes, &ctx);
 
    char * sha256sum = (char*)calloc(SHA256_DIGEST_LENGTH * 2 + 1, sizeof(char));
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&sha256sum[i * 2], "%02x", (unsigned char)sha256Bytes[i]);
    }

    return sha256sum;
}

char* sha256sum_of_file(FILE * file) {
    unsigned char sha256Bytes[SHA256_DIGEST_LENGTH] = {0};
 
    SHA256_CTX ctx;
    SHA256_Init(&ctx);

    unsigned char buffer[1024] = {0};
    size_t size = 0;

    while ((size = fread(buffer, 1, 1024, file)) != 0) {
        SHA256_Update(&ctx, buffer, size);
    }

    SHA256_Final(sha256Bytes, &ctx);
 
    char * sha256sum = (char*)calloc(SHA256_DIGEST_LENGTH * 2 + 1, sizeof(char));
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&sha256sum[i * 2], "%02x", (unsigned char)sha256Bytes[i]);
    }

    return sha256sum;
}
