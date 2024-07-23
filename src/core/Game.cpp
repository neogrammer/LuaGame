#include <pch.hpp>

void Game::update(float dt)
{
}
void Game::render()
{
	sf::Vector2i tile = { 0, 0 };
	for (tile.y = 0; tile.y < mLevelSize.y; tile.y++)
	{
		for (tile.x = 0; tile.x < mLevelSize.x; tile.x++)
		{
			TileType b = mLevelVec[(uint8_t)tile.y * mLevelSize.x + tile.x];


			switch (b)
			{
			case TileType::Empty:
				break;
			case TileType::Solid:
			{
				sf::Sprite spr{};
				spr.setTexture(tex);
				spr.setTextureRect({ {7 * 32, 0}, {32, 32} });
				spr.setPosition({ (float)tile.x * 32.f, (float)tile.y * 32.f });
				mWnd.draw(spr);
			}
			break;
			case TileType::TL:
			{
				sf::Sprite spr{};
				spr.setTexture(tex);
				spr.setTextureRect({ {0 * 32, 0}, {32, 32} });
				spr.setPosition({ (float)tile.x * 32.f, (float)tile.y * 32.f });
				mWnd.draw(spr);
			}
			break;
			case TileType::TOP:
			{
				sf::Sprite spr{};
				spr.setTexture(tex);
				spr.setTextureRect({ {1 * 32, 0}, {32, 32} });
				spr.setPosition({ (float)tile.x * 32.f, (float)tile.y * 32.f });
				mWnd.draw(spr);
			}
			break;
			case TileType::TR:
			{
				sf::Sprite spr{};
				spr.setTexture(tex);
				spr.setTextureRect({ {2 * 32, 0}, {32, 32} });
				spr.setPosition({ (float)tile.x * 32.f, (float)tile.y * 32.f });
				mWnd.draw(spr);
			}
			break;
			case TileType::L:
			{
				sf::Sprite spr{};
				spr.setTexture(tex);
				spr.setTextureRect({ {6 * 32, 0}, {32, 32} });
				spr.setPosition({ (float)tile.x * 32.f, (float)tile.y * 32.f });
				mWnd.draw(spr);
			}
			break;
			case TileType::R:
			{
				sf::Sprite spr{};
				spr.setTexture(tex);
				spr.setTextureRect({ {0 * 32, 32}, {32, 32} });
				spr.setPosition({ (float)tile.x * 32.f, (float)tile.y * 32.f });
				mWnd.draw(spr);
			}
			break;
			case TileType::BL:
			{
				sf::Sprite spr{};
				spr.setTexture(tex);
				spr.setTextureRect({ {96, 64}, {32, 32} });
				spr.setPosition({ (float)tile.x * 32.f, (float)tile.y * 32.f });
				mWnd.draw(spr);
			}
			break;
			case TileType::B:
			{
				sf::Sprite spr{};
				spr.setTexture(tex);
				spr.setTextureRect({ {32, 64}, {32, 32} });
				spr.setPosition({ (float)tile.x * 32.f, (float)tile.y * 32.f });
				mWnd.draw(spr);
			}
			break;
			case TileType::BR:
			{
				sf::Sprite spr{};
				spr.setTexture(tex);
				spr.setTextureRect({ {64, 64}, {32, 32} });
				spr.setPosition({ (float)tile.x * 32.f, (float)tile.y * 32.f });
				mWnd.draw(spr);
			}
			break;
			default:
				break;
			}
		}
	}
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
	: mWnd{ sf::VideoMode{1280U,768U,32U},"LuaGame",sf::Style::Close }
	, player{}
	, player2{}
	, tex{}
{
	mWnd.setPosition({ 100,55 });
	mGameRunning = true;
	tex.loadFromFile("assets/textures/tilesets/map1/platformer1.png");
}

Game::Game(sf::ContextSettings& settings)
	: mWnd{ sf::VideoMode{1280U,768U,32U},"LuaGame",sf::Style::Close, settings }
	, player{}
	, player2{}
	, tex{}
{
	mWnd.setPosition({ 100,55 });
	mGameRunning = true;
	tex.loadFromFile("assets/textures/tilesets/map1/platformer1.png");


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
	lua_register(Lvl, "cpp_loadLevel", lua_loadLevel);
	lua_register(Lvl, "cpp_setTile", lua_setTile);

	if (mylua::CheckLua(Lvl, luaL_dofile(Lvl, "assets/lua_scripts/level.lua")))
	{
		lua_getglobal(Lvl, "LoadLevel");
		if (lua_isfunction(Lvl, -1))
		{
			lua_pushlightuserdata(Lvl, this);
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


void Game::loadLevel(int w, int h)
{
	mLevelSize = { w, h };
	mLevelVec.clear();
	mLevelVec.resize((uint8_t)w * h);
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			mLevelVec.push_back(TileType::Empty);
		}
	}

	std::cout << w << " " << h << std::endl;
}

void Game::setTile(int x, int y, int str)
{

	switch (str)
	{
	case 0:
		mLevelVec[(uint8_t)y * mLevelSize.x + x] = TileType::Empty;
		break;
	case 1:
		mLevelVec[(uint8_t)y * mLevelSize.x + x] = TileType::Solid;
		break;
	case 2:
		mLevelVec[(uint8_t)y * mLevelSize.x + x] = TileType::TL;
		break;
	case 3:
		mLevelVec[(uint8_t)y * mLevelSize.x + x] = TileType::TOP;
		break;
	case 4:
		mLevelVec[(uint8_t)y * mLevelSize.x + x] = TileType::TR;
		break;
	case 5:
		mLevelVec[(uint8_t)y * mLevelSize.x + x] = TileType::L;
		break;
	case 6:
		mLevelVec[(uint8_t)y * mLevelSize.x + x] = TileType::R;
		break;
	case 7:
		mLevelVec[(uint8_t)y * mLevelSize.x + x] = TileType::BL;
		break;
	case 8:
		mLevelVec[(uint8_t)y * mLevelSize.x + x] = TileType::B;
		break;
	case 9:
		mLevelVec[(uint8_t)y * mLevelSize.x + x] = TileType::BR;
		break;
	default:
		break;
	}
}
