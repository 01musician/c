//gcc -o printCLuaStack printCLuaStack.c -I /usr/include/lua5.4 -llua5.4
#include<stdio.h>
#include "lua.h"
#include "lauxlib.h"

static void stackDump(lua_State *L)
{
	int i;
	int top = lua_gettop(L);

	for(i=1; i<=top; i++) {
		int t = lua_type(L, i);
		switch (t) {
			case LUA_TSTRING: {
						 printf("'%s'", lua_tostring(L, i));
						 break;
					 }
					 
			case LUA_TBOOLEAN: {
						   printf(lua_toboolean(L, i) ? "ture" : "false");
						   break;
					   }

			case LUA_TNUMBER: {
						   printf("%g", lua_tonumber(L, i));
						   break;
					   }

			default : 	   {
						   printf("%s", lua_typename(L, t));
						   break;
					   }

		}
		printf(" ");
	}
	printf("\n");
}

int main(void) {
	lua_State *L = luaL_newstate();
	lua_pushboolean(L, 1);
	lua_pushnumber(L, 10);
	lua_pushnil(L);
	lua_pushstring(L, "hello");

	stackDump(L);
	lua_pushvalue(L, -4);
	stackDump(L);
	lua_close(L);
	return 0;
}
