#ifndef GAME_HPP__
#define GAME_HPP__
#include <string>
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/System/Vector2.hpp>


extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <string>
};

class Game
{
	struct Player
	{
		std::string title = "";
		std::string name = "";
		std::string family = "";
		int level = 0;
	};

	enum class TileType : int
	{
		Empty = 0,
		Solid = 1,
		TL = 2,
		TOP = 3,
		TR = 4,
		L = 5,
		R = 6,
		BL = 7,
		B = 8,
		BR = 9
	};
	sf::Vector2i mLevelSize{};
	std::vector<TileType> mLevelVec{};

	sf::Texture tex{};


	sf::RenderWindow mWnd;
	bool mGameRunning{ false };

	void update(float dt);
	void render();

	Player player{};
	Player player2{};


public:
	Game();
	Game(sf::ContextSettings& settings);
	~Game() = default;
	void run();

	void loadLevel(int w, int h);
	static int lua_loadLevel(lua_State* L)
	{
		if (lua_gettop(L) != 3) return -1;
		Game* obj = static_cast<Game*>(lua_touserdata(L, 1));
		int w = (int)lua_tointeger(L, 2);
		int h = (int)lua_tointeger(L, 3);
		obj->loadLevel(w, h);
		return 0;
	};

	void setTile(int x, int y, int str);

	static int lua_setTile(lua_State* L)
	{
		if (lua_gettop(L) != 4) return -1;
		Game* obj = static_cast<Game*>(lua_touserdata(L, 1));
		int x = (int)lua_tointeger(L, 2);
		int y = (int)lua_tointeger(L, 3);
		int type = (int)lua_tonumber(L, 4);
		obj->setTile(x, y, type);


		return 0;
	};



};

#endif