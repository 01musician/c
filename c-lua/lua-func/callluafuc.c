// main.c
#include <lua5.1/lua.h>
#include <lua5.1/lualib.h>
#include <lua5.1/lauxlib.h>
#include <stdio.h>

int main() {
    // Create a Lua state
    lua_State *L = luaL_newstate();

    // Load Lua libraries
    luaL_openlibs(L);

    // Load the Lua script
    if (luaL_dofile(L, "add.lua") == 0) {
        // Call the Lua function
        lua_getglobal(L, "add_numbers");
        lua_pushnumber(L, 10);
        lua_pushnumber(L, 20);

        // Call the Lua function with 2 arguments and 1 result
        if (lua_pcall(L, 2, 1, 0) == 0) {
            // Retrieve the result from the Lua stack
            double result = lua_tonumber(L, -1);

            // Print the result
            printf("Result of add_numbers(10, 20): %.2f\n", result);
        } else {
            fprintf(stderr, "Error calling Lua function: %s\n", lua_tostring(L, -1));
        }

        lua_getglobal(L, "divide_numbers");
        lua_pushnumber(L, 10);
        lua_pushnumber(L, 20);

        // Call the Lua function with 2 arguments and 1 result
        if (lua_pcall(L, 2, 1, 0) == 0) {
            // Retrieve the result from the Lua stack
            double result = lua_tonumber(L, -1);

            // Print the result
            printf("Result of divide_numbers(10, 20): %.2f\n", result);
        } else {
            fprintf(stderr, "Error calling Lua function: %s\n", lua_tostring(L, -1));
        }
 
    } else {
        fprintf(stderr, "Error loading Lua script: %s\n", lua_tostring(L, -1));
    }

    // Close the Lua state
    lua_close(L);

    return 0;
}

