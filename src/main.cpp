#include <pch.h>
#include <lua_util.h>

int main(int argc, char* argv[])
{
	struct Player
	{
		std::string title;
		std::string name;
		std::string family;
		int level;
	} player;

	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	lua_register(L, "HostFunction", mylua::HostFunction);
	if(mylua::CheckLua(L, luaL_dofile(L, "src/script-Main.lua")))
	{
		lua_getglobal(L, "DoAThing");
		if (lua_isfunction(L, -1))
		{
			lua_pushnumber(L, 5);
			lua_pushnumber(L, 6);

			if (mylua::CheckLua(L, lua_pcall(L, 2, 1, 0)))
			{
				std::cout << "Did a thing" << std::endl;

				/*if (lua_istable(L, -1))
				{
					lua_pushstring(L, "Name");
					lua_gettable(L, -2);
					player.name = lua_tostring(L, -1);
					lua_pop(L, 1);

					lua_pushstring(L, "Family");
					lua_gettable(L, -2);
					player.family = lua_tostring(L, -1);
					lua_pop(L, 1);

					lua_pushstring(L, "Title");
					lua_gettable(L, -2);
					player.title = lua_tostring(L, -1);
					lua_pop(L, 1);

					lua_pushstring(L, "Level");
					lua_gettable(L, -2);
					player.level = (int)lua_tonumber(L, -1);
					lua_pop(L, 1);

					std::cout << player.name << player.title << player.family << player.level << std::endl;
				}*/
			}

		}

	}
	

	sf::ContextSettings settings{};
	settings.antialiasingLevel = 8;
	sf::RenderWindow wnd{ { 1600U , 900U , 32U}, "LuaGame", sf::Style::Close, settings };

	while (wnd.isOpen())
	{
		sf::Event e;
		while (wnd.pollEvent(e))
		{
			if (e.type == sf::Event::Closed || (e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::Escape))
				wnd.close();
		}
		wnd.clear(sf::Color::Blue);

		wnd.display();
	}


	lua_close(L);
	return 0;
}