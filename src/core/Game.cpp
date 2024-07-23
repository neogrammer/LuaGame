#include <pch.hpp>

void Game::update(float dt)
{
}
void Game::render()
{
	sf::Text player1Text;
	player1Text.setFont(Cfg::fonts.get((int)Cfg::Fonts::FriskyPuppy));
	player1Text.setCharacterSize(44U);
	player1Text.setFillColor(sf::Color::White);
	player1Text.setString(player.name + ' ' + player.title + ' ' + player.name + ' ' + std::to_string(player.level));
	player1Text.setPosition({ 200.f, 378.f });
	sf::Text player2Text;
	player2Text.setFont(Cfg::fonts.get((int)Cfg::Fonts::FriskyPuppy));
	player2Text.setCharacterSize(44U);
	player2Text.setFillColor(sf::Color::White);
	player2Text.setString(player2.name + ' ' + player2.title + ' ' + player2.name + ' ' + std::to_string(player2.level));
	player2Text.setPosition({ 200.f, 422.f });

	mWnd.draw(player1Text);
	mWnd.draw(player2Text);

}

Game::Game()
	: mWnd{ sf::VideoMode{1600U,900U,32U},"LuaGame",sf::Style::Close }
	, player{}
	, player2{}
{
	mWnd.setPosition({ 100,55 });
	mGameRunning = true;
}

Game::Game(sf::ContextSettings& settings)
	: mWnd{ sf::VideoMode{1600U,900U,32U},"LuaGame",sf::Style::Close, settings}
	, player{}
	, player2{}
{
	mWnd.setPosition({ 100,55 });
	mGameRunning = true;

	
}

void Game::run()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	lua_register(L, "cpp_HostFunction", mylua::lua_HostFunction);
	if (mylua::CheckLua(L, luaL_dofile(L, "src/script-Main.lua")))
	{
		lua_getglobal(L, "DoAThing");
		if (lua_isfunction(L, -1))
		{
			lua_pushnumber(L, 5);
			lua_pushnumber(L, 6);

			if (mylua::CheckLua(L, lua_pcall(L, 2, 1, 0)))
			{
				std::cout << "Did a thing" << std::endl;
			}
			lua_pop(L, 1);

		}



	}
	lua_pop(L, 1);

	lua_close(L);

	lua_State* N = luaL_newstate();
	luaL_openlibs(N);
	if (mylua::CheckLua(N, luaL_dofile(N, "src/script-Main.lua")))
	{
		lua_getglobal(N, "GetPlayer");
		if (lua_isfunction(N, -1))
		{
			lua_pushnumber(N, 0);
			if (mylua::CheckLua(N, lua_pcall(N, 1, 1, 0)))
			{
				if (lua_istable(N, -1))
				{
					lua_pushstring(N, "Name");
					lua_gettable(N, -2);
					player.name = lua_tostring(N, -1);
					lua_pop(N, 1);

					lua_pushstring(N, "Family");
					lua_gettable(N, -2);
					player.family = lua_tostring(N, -1);
					lua_pop(N, 1);

					lua_pushstring(N, "Title");
					lua_gettable(N, -2);
					player.title = lua_tostring(N, -1);
					lua_pop(N, 1);

					lua_pushstring(N, "Level");
					lua_gettable(N, -2);
					player.level = (int)lua_tonumber(N, -1);
					lua_pop(N, 1);
				}

			}
			lua_pop(N, 1);
		}


		lua_getglobal(N, "GetPlayer");
		if (lua_isfunction(N, -1))
		{
			lua_pushnumber(N, 1);
			if (mylua::CheckLua(N, lua_pcall(N, 1, 1, 0)))
			{
				if (lua_istable(N, -1))
				{
					lua_pushstring(N, "Name");
					lua_gettable(N, -2);
					player2.name = lua_tostring(N, -1);
					lua_pop(N, 1);

					lua_pushstring(N, "Family");
					lua_gettable(N, -2);
					player2.family = lua_tostring(N, -1);
					lua_pop(N, 1);

					lua_pushstring(N, "Title");
					lua_gettable(N, -2);
					player2.title = lua_tostring(N, -1);
					lua_pop(N, 1);

					lua_pushstring(N, "Level");
					lua_gettable(N, -2);
					player2.level = (int)lua_tonumber(N, -1);
					lua_pop(N, 1);
				}
			}
			lua_pop(N, 1);

		}


	}
	lua_pop(N, 1);
	lua_close(N);

	lua_State* Lvl = luaL_newstate();
	luaL_openlibs(Lvl);
	lua_register(L, "cpp_loadLevel", lua_loadLevel);
	if (mylua::CheckLua(Lvl, luaL_dofile(Lvl, "assets/lua_scripts/level.lua")))
	{
		lua_getglobal(Lvl, "LoadLevel");
		if (lua_isfunction(Lvl, -1))
		{
			lua_pushlightuserdata(Lvl,this);
			lua_pushnumber(Lvl, 1);
			if (mylua::CheckLua(Lvl, lua_pcall(Lvl, 2, 1, 0)))
			{
				std::cout << "Success" << std::endl;
			}
			lua_pop(Lvl, 1);
		}
	}
	lua_pop(Lvl, 1);
	lua_close(Lvl);


	sf::Clock fpsTimer;
	sf::Time elapsed;
	while (mWnd.isOpen())
	{
		sf::Event e;
		while (mWnd.pollEvent(e))
		{
			switch (e.type)
			{
			case sf::Event::Closed:
				mGameRunning = false;
				break;
			case sf::Event::KeyReleased:
				if (e.key.code == sf::Keyboard::Escape)
					mGameRunning = false;
				break;
			default:
				break;
			}
		}



		elapsed += fpsTimer.restart();
		bool repaint = false;
		while (elapsed >= sf::seconds(0.016666667f))
		{
			repaint = true;
			elapsed -= sf::seconds(0.016666667f);
			update(0.016666667f);
			elapsed += fpsTimer.restart();
		}

		if (repaint)
		{
			//render game frame
			mWnd.clear(sf::Color::Blue);
			render();
			mWnd.display();
		}

		if (mGameRunning == false) mWnd.close();
	}
}

int Game::lua_loadLevel(lua_State* L)
{
	if (lua_gettop(L) != 3) return -1;
	Game* obj = static_cast<Game*>(lua_touserdata(L, 1));
	int w = lua_tointeger(L, 2);
	int h = lua_tointeger(L, 3);
	obj->loadLevel(w, h);
	return 0;
}

void Game::loadLevel(int w, int h)
{
	mLevelSize = { w, h };
	mLevelVec.clear();
	mLevelVec.resize(w*h);

	std::cout << w << " " << h << std::endl;
}
