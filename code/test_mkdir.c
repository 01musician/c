#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>

int create_directory(const char* path) {
    struct stat st;

    if (stat(path, &st) == 0) {
        if (S_ISDIR(st.st_mode)) {
            // The directory already exists
            return 0;
        } else {
            // The path exists, but it is not a directory
            return -1;
        }
    }

    // Try creating the directory
    if (mkdir(path, 0777) == 0) {
        // Successfully created the directory
        return 0;
    } else {
        // Failed to create the directory, check if it's because of missing parent directories
        if (errno == ENOENT) {
            // The parent directory does not exist, so create it recursively
            char* parent_path = strdup(path); // Make a copy to avoid modifying the original path
            char* last_slash = strrchr(parent_path, '/');

            if (last_slash != NULL) {
                *last_slash = '\0'; // Terminate the string at the last slash
                int result = create_directory(parent_path);

                free(parent_path); // Remember to free the dynamically allocated memory
                if (result != 0) {
                    return -1; // Failed to create parent directory
                }
            } else {
                free(parent_path); // Free the memory if no more slashes are found
                return -1; // No parent directory found, cannot create the desired directory
            }

            // Retry creating the desired directory
            return mkdir(path, 0777);
        } else {
            // Failed to create the directory due to some other error
            return -1;
        }
    }
}

int main() {
    const char* directory_path = "./absent/parent/directory/new_directory";

    if (create_directory(directory_path) == 0) {
        printf("Directory created successfully.\n");
    } else {
        printf("Failed to create directory.\n");
    }

    return 0;
}

