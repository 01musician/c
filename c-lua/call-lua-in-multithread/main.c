//gcc -o main main.c -I/usr/include/luajit-2.1 -lluajit-5.1 -lpthread

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

// Thread function
void* thread_function(void* arg) {
    int thread_id = *(int*)arg;
    lua_State *L = luaL_newstate();
    if (L == NULL) {
        fprintf(stderr, "Failed to create Lua state for thread %d\n", thread_id);
        return NULL;
    }

    // Load Lua libraries
    luaL_openlibs(L);

    // Load the Lua script
    if (luaL_dofile(L, "script.lua") != LUA_OK) {
        fprintf(stderr, "Failed to load Lua script in thread %d: %s\n", thread_id, lua_tostring(L, -1));
        lua_close(L);
        return NULL;
    }

    // Get the Lua function
    lua_getglobal(L, "generate_message");
    if (!lua_isfunction(L, -1)) {
        fprintf(stderr, "Lua function not found in thread %d\n", thread_id);
        lua_close(L);
        return NULL;
    }

    // Push the argument (thread_id) to the Lua function
    lua_pushinteger(L, thread_id);

    // Call the Lua function
    if (lua_pcall(L, 1, 1, 0) != LUA_OK) {
        fprintf(stderr, "Failed to call Lua function in thread %d: %s\n", thread_id, lua_tostring(L, -1));
        lua_close(L);
        return NULL;
    }

    // Get the result (message)
    if (!lua_isstring(L, -1)) {
        fprintf(stderr, "Lua function did not return a string in thread %d\n", thread_id);
        lua_close(L);
        return NULL;
    }

    const char *message = lua_tostring(L, -1);
    printf("Thread %d: %s\n", thread_id, message);

    // Clean up
    lua_pop(L, 1);
    lua_close(L);
    return NULL;
}

int main(void) {
    const int num_threads = 4;
    pthread_t threads[num_threads];
    int thread_ids[num_threads];

    // Create threads
    for (int i = 0; i < num_threads; i++) {
        thread_ids[i] = i;
        if (pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]) != 0) {
            fprintf(stderr, "Failed to create thread %d\n", i);
            return EXIT_FAILURE;
        }
    }

    // Wait for threads to finish
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    return EXIT_SUCCESS;
}

