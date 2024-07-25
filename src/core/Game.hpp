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
	{  
		Dynamic() = default;
		Dynamic(const Dynamic&) = default;
		Dynamic& operator=(const Dynamic&) = default;
		Dynamic& operator=(Dynamic&&) = default;
		Dynamic(Dynamic&&) = default;
		virtual ~Dynamic() = default;
		void initMembers();
		void loadAnimations();
		std::vector<sf::IntRect> loadAnimation(int numFrames, int startCol, int startRow, int  pitch, int pitchColBegin);
		DynamicType dType{ DynamicType::NotSet };
		sf::Vector2f pos{0.f,0.f};
		sf::Vector2f size = { 1.f,1.f };
		sf::Vector2f vel{0.f,0.f};
		sf::Vector2f speed{ 0.f,0.f };
		int numAnims{ 0 };
		std::string currentAnim{ "none" };
		bool facingLeft{ true };

		// if true, then the map only has a single oriented animation map, all set to true for the second part of the key
		bool unidirectional{ false };
		int index{ 0 };
		// animation name, and direction facing of the image
		std::map<std::pair<std::string, bool>, std::vector<sf::IntRect>> frames{};
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
			Game() = default;
			Game(sf::ContextSettings& settings);
			~Game();
			void run();
		
    public:  // Lua Visible functions
			static int lua_loadLevel(lua_State* L);
			static int lua_setTile(lua_State* L);
			static int lua_createDynamicObject(lua_State* L);
			static int lua_assignPlayerControl(lua_State* L);
			static int lua_moveBullet(lua_State* L);
			static int lua_moveObject(lua_State* L);

    private: // Lua non-visible counterparts
			void setTile(int x, int y, int str);
			void loadLevel(int w, int h);
			void assignPlayerControl(Dynamic& dyno);
			void drawTilemap();
			void moveObject(Dynamic& dyno, float x, float y, float time);
			Dynamic* createDynamicObject(int type, float x, float y, float w, float h, int dir);
	
	private:  // internal use only
			void manipulate(float dt, lua_State* L);
			void input(float dt, lua_State* L);
			void update(float dt, lua_State* L);
			void render();
			void drawDynamics();
			void cleanupManipluators(std::vector<Manipulator*>& vec);
			void destroyAllManipluators(std::vector<Manipulator*>& vec);
			bool isManipulatorCompleted(std::vector<Manipulator*>& vec);

private:  // hidden members
				sf::Vector2i mLevelSize{};
				std::vector<TileType> mLevelVec{};
				std::vector<Dynamic*> mDynamicObjects;
				std::vector<sf::Texture*> mDynamicTextures;


				Dynamic* underPlayerControl{};
				std::vector<Dynamic*> friendlyProjectiles;
				std::vector<Dynamic*> enemyProjectiles;


				std::vector<Manipulator*> mManipulators;
				std::vector<Manipulator*> mNewManipulators;
				sf::Texture tex{};
				sf::RenderWindow mWnd;
				bool mGameRunning{ false };
};

#endif