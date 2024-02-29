//gcc -o testHash testHash.c  -lssl -lcrypto

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

void calculate_hash(const unsigned char *data, size_t data_len, unsigned char *hash) {
    SHA256_CTX sha256_context;
    SHA256_Init(&sha256_context);
    SHA256_Update(&sha256_context, data, data_len);
    SHA256_Final(hash, &sha256_context);
}

int main() {
    const char *data = "Hello, world!";
    size_t data_len = strlen(data);
    unsigned char hash[SHA256_DIGEST_LENGTH];

    calculate_hash((const unsigned char *)data, data_len, hash);

    printf("Hash value of \"%s\": ", data);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    return 0;
}

