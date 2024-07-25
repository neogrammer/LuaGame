#ifndef LUA_UTIL_H__
#define LUA_UTIL_H__
#include <iostream>
struct lua_State;
namespace mylua
{
	bool CheckLua(lua_State* L, int r);

	int lua_HostFunction(lua_State* L);
}
#endif