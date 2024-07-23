#ifndef LUA_UTIL_H__
#define LUA_UTIL_H__
#include <iostream>

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <string>

}



#ifdef _WIN32
#pragma comment(lib, "lua53.lib")
#endif

namespace mylua
{
	static bool CheckLua(lua_State* L, int r)
	{
		if (r != LUA_OK)
		{
			std::string errormsg = lua_tostring(L, -1);
			std::cout << errormsg << std::endl;
			return false;
		}
		return true;
	};
	static int lua_HostFunction(lua_State* L)
	{
		float a = (float)lua_tonumber(L, 1);
		float b = (float)lua_tonumber(L, 2);
		std::cout << "HostFunction called" << std::endl;
		float  c = a * b;
		lua_pushnumber(L, c);
		return 1;
	};
	
}
#endif