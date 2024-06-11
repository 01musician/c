#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generate_suffix(char *suffix, int index, int suffix_len) {
    for (int i = suffix_len - 1; i >= 0; i--) {
        suffix[i] = 'a' + (index % 26);
        index /= 26;
    }
    suffix[suffix_len] = '\0';
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <input file> <chunk size> <prefix> <suffix length>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input_file = argv[1];
    long chunk_size = atol(argv[2]);
    const char *prefix = argv[3];
    int suffix_len = atoi(argv[4]);

    if (chunk_size <= 0 || suffix_len <= 0) {
        fprintf(stderr, "Chunk size and suffix length must be positive numbers.\n");
        return EXIT_FAILURE;
    }

    FILE *input = fopen(input_file, "rb");
    if (!input) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    char *buffer = (char *)malloc(chunk_size);
    if (!buffer) {
        perror("Memory allocation error");
        fclose(input);
        return EXIT_FAILURE;
    }

    char suffix[suffix_len + 1];
    int part_number = 0;
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, chunk_size, input)) > 0) {
        generate_suffix(suffix, part_number++, suffix_len);

        char output_filename[strlen(prefix) + suffix_len + 1];
        sprintf(output_filename, "%s%s", prefix, suffix);

        FILE *output = fopen(output_filename, "wb");
        if (!output) {
            perror("Error opening output file");
            free(buffer);
            fclose(input);
            return EXIT_FAILURE;
        }

        fwrite(buffer, 1, bytes_read, output);
        fclose(output);
    }

    free(buffer);
    fclose(input);

    if (ferror(input)) {
        perror("Error reading input file");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

