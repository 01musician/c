//gcc -Wall genDirHashFilterByLua.c -o genDirHashFilterByLua -I/usr/include/lua5.4 -lcrypto -llua5.4
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#define HASH_SIZE SHA256_DIGEST_LENGTH

// Global Lua state
lua_State *L = NULL;
int lua_loaded = 0;

// Print hash as hex
void print_hash_hex(const unsigned char *hash) {
    for (int i = 0; i < HASH_SIZE; i++)
        printf("%02x", hash[i]);
}

// Compute SHA256 of given buffer
void sha256_buffer(const unsigned char *buf, size_t len, unsigned char *out_hash) {
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, buf, len);
    SHA256_Final(out_hash, &ctx);
}

// Compute hash of file content + relative path
int hash_file(const char *filepath, const char *relpath, unsigned char *out_hash) {
    FILE *fp = fopen(filepath, "rb");
    if (!fp) {
        perror(filepath);
        return -1;
    }

    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, relpath, strlen(relpath));

    unsigned char buf[4096];
    size_t n;
    while ((n = fread(buf, 1, sizeof(buf), fp)) > 0) {
        SHA256_Update(&ctx, buf, n);
    }

    SHA256_Final(out_hash, &ctx);
    fclose(fp);

    printf("[FILE] ");
    print_hash_hex(out_hash);
    printf("  %s\n", relpath);

    return 0;
}

// Forward declaration
int hash_directory(const char *root, const char *dirpath, unsigned char *out_hash);

// Compute hash for file or directory, optionally using Lua validation
int compute_path_hash(const char *root, const char *path, const char *relpath, unsigned char *out_hash) {
    struct stat st;
    if (lstat(path, &st) < 0) {
        perror(path);
        return -1;
    }

    int validate = 1;  // default: hash everything

    // Call Lua isValidate(relpath) if Lua is loaded
    if (lua_loaded) {
        lua_getglobal(L, "isValidate");   // push isValidate function
        if (lua_isfunction(L, -1)) {
            lua_pushstring(L, relpath);   // push argument
            if (lua_pcall(L, 1, 1, 0) != LUA_OK) {
                fprintf(stderr, "Lua error: %s\n", lua_tostring(L, -1));
                lua_pop(L, 1);
            } else {
                if (lua_isinteger(L, -1)) {
                    validate = (int)lua_tointeger(L, -1);
                } else if (lua_isboolean(L, -1)) {
                    validate = lua_toboolean(L, -1);
                }
                lua_pop(L, 1); // pop return value
            }
        } else {
            lua_pop(L, 1); // pop nil
        }
    }

    if (!validate) {
        // Skip hashing
        unsigned char empty[HASH_SIZE] = {0};
        memcpy(out_hash, empty, HASH_SIZE);
        printf("[SKIP] %s (Lua skipped)\n", relpath);
        return 0;
    }

    if (S_ISREG(st.st_mode)) {
        return hash_file(path, relpath, out_hash);
    } else if (S_ISDIR(st.st_mode)) {
        return hash_directory(root, path, out_hash);
    } else {
        // Special files: hash relpath + type
        SHA256_CTX ctx;
        SHA256_Init(&ctx);
        SHA256_Update(&ctx, relpath, strlen(relpath));
        SHA256_Update(&ctx, "SPECIAL", 7);
        SHA256_Final(out_hash, &ctx);
        printf("[SKIP] ");
        print_hash_hex(out_hash);
        printf("  %s (special)\n", relpath);
        return 0;
    }
}

// Hash directory contents (recursively, sorted)
int hash_directory(const char *root, const char *dirpath, unsigned char *out_hash) {
    DIR *dir = opendir(dirpath);
    if (!dir) {
        perror(dirpath);
        return -1;
    }

    struct dirent **namelist = NULL;
    int n = scandir(dirpath, &namelist, NULL, alphasort);
    if (n < 0) {
        perror("scandir");
        closedir(dir);
        return -1;
    }

    SHA256_CTX ctx;
    SHA256_Init(&ctx);

    for (int i = 0; i < n; i++) {
        struct dirent *entry = namelist[i];
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            free(entry);
            continue;
        }

        char fullpath[4096];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", dirpath, entry->d_name);

        char relpath[4096];
        snprintf(relpath, sizeof(relpath), "%s", fullpath + strlen(root) + 1);

        unsigned char child_hash[HASH_SIZE];
        if (compute_path_hash(root, fullpath, relpath, child_hash) == 0) {
            SHA256_Update(&ctx, child_hash, HASH_SIZE);
        }

        free(entry);
    }

    free(namelist);
    closedir(dir);

    SHA256_Final(out_hash, &ctx);

    printf("[DIR ] ");
    print_hash_hex(out_hash);
    printf("  %s/\n", (strcmp(root, dirpath) == 0) ? "." : dirpath + strlen(root) + 1);

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <root_directory> [filter.lua]\n", argv[0]);
        return 1;
    }

    // Initialize Lua
    L = luaL_newstate();
    luaL_openlibs(L);

    if (argc > 2)
    if (access(argv[2], F_OK) == 0) {
        if (luaL_dofile(L, argv[2]) != LUA_OK) {
            fprintf(stderr, "Failed to load %s: %s\n", argv[2], lua_tostring(L, -1));
            lua_pop(L, 1);
        } else {
            lua_loaded = 1;
            printf("Lua %s loaded.\n", argv[2]);
        }
    }

    char root[4096];
    if (!realpath(argv[1], root)) {
        perror("realpath");
        if (L) lua_close(L);
        return 1;
    }

    unsigned char root_hash[HASH_SIZE];
    if (hash_directory(root, root, root_hash) == 0) {
        printf("\nFinal Root Directory Hash: ");
        print_hash_hex(root_hash);
        printf("\n");
    } else {
        fprintf(stderr, "Failed to compute directory hash\n");
        if (L) lua_close(L);
        return 1;
    }

    if (L) lua_close(L);
    return 0;
}

