#include <stdio.h>
#include <stdlib.h>
#include <openssl/sha.h>

void calculate_sha256(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Cannot open file");
        return;
    }

    SHA256_CTX sha256;
    SHA256_Init(&sha256);

    const size_t bufSize = 32768;
    unsigned char *buffer = malloc(bufSize);
    if (!buffer) {
        perror("Cannot allocate buffer");
        fclose(file);
        return;
    }

    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, bufSize, file)) > 0) {
        SHA256_Update(&sha256, buffer, bytesRead);
    }
    if (ferror(file)) {
        perror("Error reading file");
    }

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_Final(hash, &sha256);

    printf("SHA-256 of %s: ", filename);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        printf("%02x", hash[i]);
    printf("\n");

    fclose(file);
    free(buffer);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <pdf1> [pdf2 ...]\n", argv[0]);
        return 1;
    }


    for (int i = 1; i < argc; i++) {
        calculate_sha256(argv[i]);
    }

    return 0;
}