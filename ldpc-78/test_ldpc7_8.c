#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DATA_BLOCK 7
#define CODE_BLOCK 8
#define INPUT_SIZE 1024
#define BLOCKS (INPUT_SIZE / DATA_BLOCK)
#define CODE_SIZE (BLOCKS * CODE_BLOCK)

#define BILLION 1000000000L

// Toy H matrix from previous example
const int H[8][10] = {
    {0, 5,13,22,29,36,42,51,57,63},
    {1, 6,14,23,30,37,43,52,58,-1},
    {2, 7,15,24,31,38,44,53,-1,-1},
    {3, 8,16,25,32,39,45,54,-1,-1},
    {4, 9,17,26,33,40,46,55,-1,-1},
    {10,18,27,34,41,47,56,59,-1,-1},
    {11,19,28,35,48,49,60,-1,-1,-1},
    {12,20,21,50,61,62,-1,-1,-1,-1}
};

void ldpc78_encode(const unsigned char* data, unsigned char* codeword) {
    memcpy(codeword, data, DATA_BLOCK);
    memset(codeword + DATA_BLOCK, 0, 1);  // dummy parity

    for (int i = 56; i < 64; i++) {
        int parity = 0;
        for (int j = 0; j < 8; j++) {
            for (int k = 0; k < 10 && H[j][k] != -1; k++) {
                int bit = H[j][k];
                if (bit == i) continue;
                int val = (codeword[bit / 8] >> (bit % 8)) & 1;
                parity ^= val;
            }
            codeword[i / 8] |= (parity & 1) << (i % 8);
        }
    }
}

void ldpc78_decode(unsigned char* block) {
    for (int iter = 0; iter < 10; iter++) {
        int errors = 0;
        for (int i = 0; i < 8; i++) {
            int sum = 0;
            int last = -1;
            for (int j = 0; j < 10 && H[i][j] != -1; j++) {
                int bit = H[i][j];
                int val = (block[bit / 8] >> (bit % 8)) & 1;
                sum ^= val;
                last = bit;
            }
            if (sum != 0 && last != -1) {
                block[last / 8] ^= (1 << (last % 8));
                errors++;
            }
        }
        if (errors == 0) break;
    }
}

void encode_array(const unsigned char* input, unsigned char* encoded) {
    for (int i = 0; i < BLOCKS; i++) {
        ldpc78_encode(input + i * DATA_BLOCK, encoded + i * CODE_BLOCK);
    }
}

void decode_array(unsigned char* encoded) {
    for (int i = 0; i < BLOCKS; i++) {
        ldpc78_decode(encoded + i * CODE_BLOCK);
    }
}

int main() {
    srand(time(NULL));
    unsigned char input[INPUT_SIZE] = {0};
    unsigned char encoded[CODE_SIZE] = {0};

    for (int i = 0; i < INPUT_SIZE; i++) {
        input[i] = rand() % 256;
    }

    encode_array(input, encoded);

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    decode_array(encoded);  // time this

    clock_gettime(CLOCK_MONOTONIC, &end);
    long diff = BILLION * (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec);

    printf("Decode time for %d bytes (LDPC 7/8): %ld ns = %.2f us\n",
           INPUT_SIZE, diff, diff / 1000.0);
    printf("Time per byte: %.2f ns\n", (double)diff / INPUT_SIZE);

    return 0;
}
