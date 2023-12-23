#include <lua5.1/lua.h>
#include <lua5.1/lauxlib.h>
#include <lua5.1/lualib.h>

int main() {
    lua_State *L = luaL_newstate();  // Create a new Lua state
    luaL_openlibs(L);  // Open standard Lua libraries

    // Load and execute the Lua configuration file
    if (luaL_dofile(L, "config.lua") != 0) {
        fprintf(stderr, "Error loading config.lua: %s\n", lua_tostring(L, -1));
        lua_close(L);
        return 1;
    }

    // Access the values from the Lua environment
    lua_getglobal(L, "stringsArray");
    lua_getglobal(L, "integerValue");

    // Check if the variables are of the correct types
    if (!lua_istable(L, -2) || !lua_isnumber(L, -1)) {
        fprintf(stderr, "Invalid types in configuration.lua\n");
        lua_close(L);
        return 1;
    }

    // Process the array of strings
    printf("Array of Strings:\n");
    int arrayLength = lua_objlen(L, -2);
    for (int i = 1; i <= arrayLength; ++i) {
        lua_rawgeti(L, -2, i);
        const char *str = lua_tostring(L, -1);
        printf("%s\n", str);
        lua_pop(L, 1);
    }

    // Process the integer value
    int intValue = lua_tointeger(L, -1);
    printf("\nInteger Value: %d\n", intValue);

    // Close the Lua state
    lua_close(L);

    return 0;
}

