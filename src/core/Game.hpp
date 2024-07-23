#ifndef GAME_HPP__
#define GAME_HPP__
#include <string>
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/System/Vector2.hpp>

extern "C"
{
	struct lua_State;
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
		Solid
	};
	sf::Vector2i mLevelSize{};
	std::vector<TileType> mLevelVec{};


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
	static int lua_loadLevel(lua_State* L);
	
};

#endif