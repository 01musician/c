#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <zookeeper/zookeeper.h>

void watcher(zhandle_t *zzh, int type, int state, const char *path, void *watcherCtx) {
    printf("Watcher triggered for znode: %s\n", path);
}

int main(int argc, char *argv[]) {
    char host[] = "localhost:2181";  // ZooKeeper server host and port
    int timeout = 30000;  // Connection timeout in milliseconds
    char path[] = "/example_node";  // Path of the node to create

    zhandle_t *zh = zookeeper_init(host, NULL, timeout, 0, NULL, 0);
    if (zh == NULL) {
        fprintf(stderr, "Error connecting to ZooKeeper server!\n");
        return EXIT_FAILURE;
    }

    // Create a znode
    char data[] = "Hello, ZooKeeper!";
    int datalen = strlen(data);
    int flags = 0;
    char *created_path = zoo_create(zh, path, data, datalen, &ZOO_OPEN_ACL_UNSAFE, flags, NULL, 0);
    if (created_path == NULL) {
        fprintf(stderr, "Error creating znode!\n");
        zookeeper_close(zh);
        return EXIT_FAILURE;
    }
    printf("Created znode: %s\n", created_path);

    // Set a watcher on the znode
    zoo_exists(zh, path, 1, NULL);

    // Sleep for a while to allow watching events to be triggered
    sleep(10);

    // Retrieve data from the znode
    char buffer[256];
    int buffer_len = sizeof(buffer) - 1;
    struct Stat stat;
    int ret = zoo_get(zh, path, 1, buffer, &buffer_len, &stat);
    if (ret != ZOK) {
        fprintf(stderr, "Error retrieving data from znode!\n");
    } else {
        buffer[buffer_len] = '\0';
        printf("Retrieved data: %s\n", buffer);
        printf("Data version: %d\n", stat.version);
    }

    // Cleanup and close the connection
    zookeeper_close(zh);

    return EXIT_SUCCESS;
}

