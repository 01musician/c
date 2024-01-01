#include <stdio.h>
#include <string.h>
#include <uchardet/uchardet.h>

int main() {
    const char *chineseString = "你好，世界！"; // Replace with your Chinese string

    // Create a uchardet detector
    uchardet_t ud = uchardet_new();

    // Handle errors if the detector is not created successfully
    if (!ud) {
        fprintf(stderr, "Unable to create uchardet detector\n");
        return 1;
    }

    // Feed the string to the detector
    uchardet_handle_data(ud, chineseString, strlen(chineseString));

    // Notify the detector that the data has ended
    uchardet_data_end(ud);

    // Get the detected encoding
    const char *detectedEncoding = uchardet_get_charset(ud);

    // Print the result
    printf("Detected Encoding: %s\n", detectedEncoding);

    // Clean up
    uchardet_delete(ud);

    return 0;
}

