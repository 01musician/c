//gcc -o genPubPriKey genPubPriKey.c -lssl -lcrypto

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <stdio.h>

int main() {
    int bits = 2048;  // Key size
    unsigned long e = RSA_F4; // Public exponent

    // Generate RSA key pair
    RSA *rsa = RSA_generate_key(bits, e, NULL, NULL);
    if (rsa == NULL) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    // Save private key
    FILE *private_file = fopen("private_key.pem", "wb");
    if (!private_file) {
        perror("Unable to open file for private key");
        exit(EXIT_FAILURE);
    }
    PEM_write_RSAPrivateKey(private_file, rsa, NULL, NULL, 0, NULL, NULL);
    fclose(private_file);

    // Save public key
    FILE *public_file = fopen("public_key.pem", "wb");
    if (!public_file) {
        perror("Unable to open file for public key");
        exit(EXIT_FAILURE);
    }
    PEM_write_RSAPublicKey(public_file, rsa);
    fclose(public_file);

    // Free the RSA structure
    RSA_free(rsa);

    printf("RSA Key pair generated and saved to private_key.pem and public_key.pem\n");

    return 0;
}

