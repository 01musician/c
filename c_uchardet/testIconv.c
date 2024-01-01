#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iconv.h>

// Convert a string from one encoding to another
char *convertEncoding(const char *input, const char *from_encoding, const char *to_encoding) {
    iconv_t cd = iconv_open(to_encoding, from_encoding);
    if (cd == (iconv_t)-1) {
        perror("iconv_open");
        exit(EXIT_FAILURE);
    }

    size_t in_len = strlen(input);
    size_t out_len = in_len; // It's generally safe to assume the output length won't exceed 4 times the input length

    char *output = (char *)malloc(out_len);
    if (output == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    char *in = (char *)input;
    char *out = output;

    if (iconv(cd, &in, &in_len, &out, &out_len) == (size_t)-1) {
        perror("iconv");
        exit(EXIT_FAILURE);
    }

    iconv_close(cd);

    return output;
}

int main() {
    // Replace these values with your actual file name and encodings
    const char *filename_utf8= "你好，世界";
    const char *from_encoding = "UTF-8";
    const char *to_encoding = "GB2312";

    // Convert the filename from GB2312 to UTF-8
    char *filename_gb2312 = convertEncoding(filename_utf8, from_encoding, to_encoding);

    // Print the result
    printf("Original Filename (UTF-8): %s\n", filename_utf8);
    printf("Converted Filename (GB2312): %s\n", filename_gb2312);

    // Don't forget to free the memory allocated by convertEncoding
    free(filename_gb2312);

    return 0;
}

