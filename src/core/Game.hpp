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
	enum class TileType : int
	{  Empty = 0,  	Solid = 1, 	TL = 2,	TOP = 3,TR = 4,
		L = 5, R = 6, BL = 7,B = 8, BR = 9
	};

	enum class DynamicType : int
	{  Player = 0, MetalBird = 1, 	BusterShot_Normal = 2, FlyPad = 3,
		Count, NotSet
	};

	// Dynamic Objects
	struct Dynamic
	{  	virtual ~Dynamic() = default;
		DynamicType dType{ DynamicType::NotSet };
		sf::Vector2f pos{0.f,0.f};
		sf::Vector2f size = { 1.f,1.f };
		sf::Vector2f vel{0.f,0.f};
		int id{ -1 };
		bool dead{false};
	};

	struct DynBullet : Dynamic
	{	int maxDist{0};
		sf::Vector2f dir{ 0.f,0.f };
	};

	struct Manipulator
	{   Dynamic* dyno;
		virtual bool update(float dt) = 0;
		bool complete{ false };
	};

	struct ManInterpPos : Manipulator
	{	sf::Vector2f startPos;
		sf::Vector2f targetPos;
		float completionTime;
		float elapsed;
		ManInterpPos(Dynamic* obj, float x, float y, float time);
		bool update(float dt) override final;
	};
	

	

public:
	Game();
	Game(sf::ContextSettings& settings);
	~Game();
	void run();

	void cleanupManipluators(std::vector<Manipulator*>& vec);
	void destroyAllManipluators(std::vector<Manipulator*>& vec);


	bool isManipulatorCompleted(std::vector<Manipulator*>& vec);
	void loadLevel(int w, int h);
	static int lua_loadLevel(lua_State* L);

	void setTile(int x, int y, int str);

	static int lua_setTile(lua_State* L);

	Dynamic* createDynamicObject(int type, float x, float y, float w, float h, int dir);

	static int lua_createDynamicObject(lua_State* L);
	

	void assignPlayerControl(Dynamic& dyno);
	void drawTilemap();

	static int lua_assignPlayerControl(lua_State* L);
	

	void moveObject(Dynamic& dyno, float x, float y, float time);


	static int lua_moveBullet(lua_State* L);


	static int lua_moveObject(lua_State* L);
	
	private:
		void manipulate(float dt, lua_State* L);
		void input(float dt, lua_State* L);
		void update(float dt, lua_State* L);
		void render();
		void drawDynamics();

		sf::Vector2i mLevelSize{};
		std::vector<TileType> mLevelVec{};
		std::vector<Dynamic*> mDynamicObjects;
		std::vector<sf::Texture*> mDynamicTextures;
		Dynamic* underPlayerControl{};
		std::vector<Manipulator*> mManipulators;
		std::vector<Manipulator*> mNewManipulators;
		sf::Texture tex{};
		sf::RenderWindow mWnd;
		bool mGameRunning{ false };
};

#endif