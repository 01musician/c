#include <lua5.1/lua.h>
#include <lua5.1/lauxlib.h>
#include <lua5.1/lualib.h>

int main() {
    // Create a Lua state
    lua_State *L = luaL_newstate();

    // Load Lua standard libraries
    luaL_openlibs(L);

    // Load the Lua script containing the isFileValid function
    luaL_dofile(L, "checkFileValid.lua");

    // Get the function isFileValid from the Lua global environment
    lua_getglobal(L, "isFileValid");

    // Push the argument (file path) onto the Lua stack
    const char *filePath = "./checkFileValid.lua";
    lua_pushstring(L, filePath);

    // Call the function with 1 argument and expect 1 result
    if (lua_pcall(L, 1, 1, 0) != 0) {
        // Handle the error, if any
        const char *errorMsg = lua_tostring(L, -1);
        fprintf(stderr, "Error calling isFileValid: %s\n", errorMsg);
    } else {
        // Retrieve the result from the Lua stack
        int result = lua_toboolean(L, -1);

        // Use the result in your C code
        if (result) {
            printf("File is valid: matches the pattern and has a size greater than 1kB. judged from c.\n");
        } else {
            printf("File is not valid: does not match the pattern or its size is not greater than 1kB. judged from c\n");
        }
    }

    // Close the Lua state
    lua_close(L);

    return 0;
}

