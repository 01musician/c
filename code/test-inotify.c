#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/inotify.h>

#define EVENT_SIZE (sizeof(struct inotify_event))
#define EVENT_BUF_LEN (1024 * (EVENT_SIZE + 16))
#define PATH_MAX 256

void monitor_directory(const char *path, int inotifyFd);
void monitor_subdirectory(const char *path, int inotifyFd);
void unmonitor_directory(int inotifyFd, int watchDescriptor);
int g_wd;

int main() {
    int inotifyFd = inotify_init();
    if (inotifyFd < 0) {
        perror("inotify_init");
        exit(EXIT_FAILURE);
    }

    // Specify the directory to monitor
    const char *parentDirectory = "../../c";

    // Monitor the parent directory
    monitor_directory(parentDirectory, inotifyFd);

    while (1) {
        char buffer[EVENT_BUF_LEN];
        int length = read(inotifyFd, buffer, EVENT_BUF_LEN);
        if (length < 0) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        int i = 0;
        while (i < length) {
            struct inotify_event *event = (struct inotify_event *)&buffer[i];

            // Check for the creation of a new directory
            if (event->mask & IN_CREATE && event->mask & IN_ISDIR) {
                printf("New directory created: %s/%s\n", parentDirectory, event->name);

                // Add the new directory to be monitored
                char newPath[PATH_MAX];
                snprintf(newPath, PATH_MAX, "%s/%s", parentDirectory, event->name);
                monitor_subdirectory(newPath, inotifyFd);
            }

            // Check for the deletion of a directory
            if (event->mask & IN_DELETE && event->mask & IN_ISDIR) {
                printf("Subdirectory deleted: %s/%s\n", parentDirectory, event->name);

                // Remove the deleted subdirectory from monitoring
                unmonitor_directory(inotifyFd, event->wd);
            }

            i += EVENT_SIZE + event->len;
        }
    }

    close(inotifyFd);
    return 0;
}

void monitor_directory(const char *path, int inotifyFd) {
    int wd = inotify_add_watch(inotifyFd, path, IN_CREATE | IN_MOVED_TO | IN_DELETE);
    if (wd < 0) {
        perror("inotify_add_watch");
        exit(EXIT_FAILURE);
    }
    printf("Now monitoring directory: %s\n", path);
}

void monitor_subdirectory(const char *path, int inotifyFd) {
    g_wd = inotify_add_watch(inotifyFd, path, IN_CREATE | IN_MOVED_TO);
    if (g_wd < 0) {
        perror("inotify_add_watch");
        exit(EXIT_FAILURE);
    }
    printf("Now monitoring directory: %s\n", path);
}



void unmonitor_directory(int inotifyFd, int watchDescriptor) {
    // Remove the watch for the deleted subdirectory
    int result = inotify_rm_watch(inotifyFd, g_wd);
    if (result < 0) {
        perror("inotify_rm_watch");
        exit(EXIT_FAILURE);
    }
    printf("No longer monitoring directory (wd=%d)\n", watchDescriptor);
}

