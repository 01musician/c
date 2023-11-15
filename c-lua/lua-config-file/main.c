#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <stdio.h>

// Function to read graphics configuration
void readGraphicsConfig(lua_State *L) {
    lua_getfield(L, -1, "graphics");

    // Read resolution
    lua_getfield(L, -1, "resolution");
    int width = luaL_checkinteger(L, -1);
    int height = luaL_checkinteger(L, -2);
    lua_pop(L, 1); // Pop resolution table

    // Read fullscreen
    lua_getfield(L, -1, "fullscreen");
    int fullscreen = lua_toboolean(L, -1);
    lua_pop(L, 1); // Pop fullscreen

    // Read vsync
    lua_getfield(L, -1, "vsync");
    int vsync = lua_toboolean(L, -1);
    lua_pop(L, 1); // Pop vsync

    // Pop graphics table
    lua_pop(L, 1);

    // Print graphics configuration
    printf("Graphics Configuration:\n");
    printf("Resolution: %dx%d\n", width, height);
    printf("Fullscreen: %s\n", fullscreen ? "true" : "false");
    printf("Vsync: %s\n", vsync ? "true" : "false");
}

// Function to read input configuration
void readInputConfig(lua_State *L) {
    lua_getfield(L, -1, "input");

    // Read key bindings
    lua_getfield(L, -1, "key_bindings");
    lua_getfield(L, -1, "move_forward");
    const char *moveForwardKey = luaL_checkstring(L, -1);
    lua_pop(L, 1); // Pop move_forward key

    // Repeat for other key bindings...

    // Pop key_bindings table
    lua_pop(L, 1);

    // Pop input table
    lua_pop(L, 1);

    // Print input configuration
    printf("\nInput Configuration:\n");
    printf("Move Forward Key: %s\n", moveForwardKey);
    // Print other key bindings...
}

// Function to read game configuration
void readGameConfig(lua_State *L) {
    lua_getfield(L, -1, "game");

    // Read difficulty
    lua_getfield(L, -1, "difficulty");
    const char *difficulty = luaL_checkstring(L, -1);
    lua_pop(L, 1); // Pop difficulty

    // Read max players
    lua_getfield(L, -1, "max_players");
    int maxPlayers = luaL_checkinteger(L, -1);
    lua_pop(L, 1); // Pop max_players

    // Pop game table
    lua_pop(L, 1);

    // Print game configuration
    printf("\nGame Configuration:\n");
    printf("Difficulty: %s\n", difficulty);
    printf("Max Players: %d\n", maxPlayers);
}

int main() {
    // Create a Lua state
    lua_State *L = luaL_newstate();
    
    // Load Lua libraries
    luaL_openlibs(L);

    // Load the Lua configuration script
    if (luaL_dofile(L, "game_config.lua") == 0) {
        // Retrieve the config table from the Lua global environment
        lua_getglobal(L, "config");

        // Read and use different sections of the configuration
        readGraphicsConfig(L);
        readInputConfig(L);
        readGameConfig(L);
    } else {
        fprintf(stderr, "Error loading Lua script: %s\n", lua_tostring(L, -1));
    }

    // Close the Lua state
    lua_close(L);

    return 0;
}

