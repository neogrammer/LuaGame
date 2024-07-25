#include <pch.hpp>
#include "util/lua_util.hpp"
bool mylua::CheckLua(lua_State* L, int r)
{
	if (r != LUA_OK)
	{
		std::string errormsg = lua_tostring(L, -1);
		std::cout << errormsg << std::endl;
		return false;
	}
	return true;
}

int mylua::lua_HostFunction(lua_State* L)
{
	float a = (float)lua_tonumber(L, 1);
	float b = (float)lua_tonumber(L, 2);
	std::cout << "HostFunction called" << std::endl;
	float  c = a * b;
	lua_pushnumber(L, c);
	return 1;
}
