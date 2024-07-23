#ifndef GAME_HPP__
#define GAME_HPP__
#include <string>
#include <vector>
#include <memory>
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

	enum class DynTexType : int
	{
		Player = 0,
		MetalBird = 1,
		BusterShot_Normal = 2
	};

	// Dynamic Objects
	struct Dynamic
	{
		sf::Vector2f pos{0.f,0.f};
		sf::Vector2f size = { 1.f,1.f };
		sf::Vector2f vel{0.f,0.f};

		int id{ -1 };
		bool dead{false};
	};



	std::vector<Dynamic*> mDynamicObjects;
	std::vector<sf::Texture*> mDynamicTextures;

	Dynamic* underPlayerControl{};
	
	struct Manipulator
	{
		Dynamic* dyno;
		virtual bool update(float dt) = 0;
		bool complete{ false };
	};

	struct manInterpPos : Manipulator
	{
		sf::Vector2f startPos{};
		sf::Vector2f targetPos{};
		float completionTime{};
		float elapsed{};

		manInterpPos(Dynamic* obj, sf::Vector2f target, float time)
		{
			dyno = obj;
			targetPos = target;
			completionTime = time;
		}

		bool update(float dt) override final
		{
			elapsed += dt;
			dyno->pos = { (targetPos.x - startPos.x) * (elapsed / completionTime) + startPos.x, (targetPos.y - startPos.y) * (elapsed / completionTime) + startPos.y ) };

			if (elapsed >= completionTime)
			{
				dyno->pos = targetPos;
				complete = true;
			}

			return complete;
		}
	};


	std::vector<Manipulator*> mManipulators;
	std::vector<Manipulator*> mNewManipulators;

	sf::Texture tex{};


	sf::RenderWindow mWnd;
	bool mGameRunning{ false };

	void manipulate(float dt);
	void input(float dt);
	void update(float dt);
	void render();

	Player player{};
	Player player2{};


public:
	Game();
	Game(sf::ContextSettings& settings);
	~Game();
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

	Dynamic* createDynamicObject(int type, float x, float y, float w, float h);

	static int lua_createDynamicObject(lua_State* L)
	{
		if (lua_gettop(L) != 6) return -1;
		Game* object = static_cast<Game*>(lua_touserdata(L, 1));
		int type = (int)lua_tointeger(L, 2);
		float x = (float)lua_tonumber(L, 3);
		float y = (float)lua_tonumber(L, 4);
		float w = (float)lua_tonumber(L, 5);
		float h = (float)lua_tonumber(L, 6);
		lua_pushlightuserdata(L, std::move(object->createDynamicObject(type, x, y, w, h)));
		return 1;
	};

	void assignPlayerControl(Dynamic& dyno);

	static int lua_assignPlayerControl(lua_State* L)
	{
		if (lua_gettop(L) != 2) return -1;
		Game* object = static_cast<Game*>(lua_touserdata(L, 1));
		Dynamic* dyno = static_cast<Dynamic*>(lua_touserdata(L, 2));
		object->assignPlayerControl(*dyno);
		return 0;
	}

};

#endif