#include <pch.hpp>


void Game::run()
{
	lua_State* Lvl = luaL_newstate();
	luaL_openlibs(Lvl);
	lua_register(Lvl, "cpp_loadLevel", lua_loadLevel);
	lua_register(Lvl, "cpp_setTile", lua_setTile);
	lua_register(Lvl, "cpp_createDynamicObject", lua_createDynamicObject);
	lua_register(Lvl, "cpp_assignPlayerControl", lua_assignPlayerControl);
	lua_register(Lvl, "cpp_moveObject", lua_moveObject);
	lua_register(Lvl, "cpp_moveBullet", lua_moveBullet);
	if (mylua::CheckLua(Lvl, luaL_dofile(Lvl, "assets/lua_scripts/level.lua")))
	{

		lua_getglobal(Lvl, "LoadLevel");
		if (lua_isfunction(Lvl, -1))
		{	lua_pushlightuserdata(Lvl, this); 	lua_pushnumber(Lvl, 1);
				if (mylua::CheckLua(Lvl, lua_pcall(Lvl, 2, 1, 0)))
				{
						std::cout << "Success" << std::endl;
				}
		}
		sf::Clock fpsTimer;	sf::Time elapsed;
		while (mWnd.isOpen())
		{
			sf::Event e;	while (mWnd.pollEvent(e))
									{ switch (e.type)
											{
												case sf::Event::Closed: 	mGameRunning = false; break;
												case sf::Event::KeyReleased: 	if (e.key.code == sf::Keyboard::Escape)  mGameRunning = false;  break;
												default: break;
										   }  
			 }
			elapsed = fpsTimer.restart();
			update(elapsed.asSeconds(), Lvl);
			mWnd.clear(sf::Color::Blue);
			render();
			mWnd.display();
			if (mGameRunning == false) mWnd.close();
		}
    }	lua_close(Lvl);
}