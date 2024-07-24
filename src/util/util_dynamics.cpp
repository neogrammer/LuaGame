#include <pch.hpp>

int Game::lua_createDynamicObject(lua_State* L)
{
	if (lua_gettop(L) != 7) return -1;
	Game* object = static_cast<Game*>(lua_touserdata(L, 1));
	int type = (int)lua_tointeger(L, 2);
	float x = (float)lua_tonumber(L, 3);
	float y = (float)lua_tonumber(L, 4);
	float w = (float)lua_tonumber(L, 5);
	float h = (float)lua_tonumber(L, 6);
	int dir = (int)lua_tointeger(L, 7);
	lua_pushlightuserdata(L, std::move(object->createDynamicObject(type, x, y, w, h, dir)));
	return 1;
};

int Game::lua_moveObject(lua_State* L)
{
	if (lua_gettop(L) != 5) return -1;

	Game* object = static_cast<Game*>(lua_touserdata(L, 1));
	Dynamic* dyno = static_cast<Dynamic*>(lua_touserdata(L, 2));
	float x = (float)lua_tonumber(L, 3);
	float y = (float)lua_tonumber(L, 4);
	float t = (float)lua_tonumber(L, 5);
	object->moveObject(*dyno, x, y, t);
	return 0;
};

int Game::lua_moveBullet(lua_State* L)
{
	if (lua_gettop(L) != 6) return -1;

	Game* object = static_cast<Game*>(lua_touserdata(L, 1));
	Dynamic* dyno = static_cast<Dynamic*>(lua_touserdata(L, 2));
	float x = (float)lua_tonumber(L, 3);
	float y = (float)lua_tonumber(L, 4);
	float t = (float)lua_tonumber(L, 5);
	int d = (int)lua_tointeger(L, 6);

	object->moveObject(*dyno, x*d, y, t);
	return 0;
}