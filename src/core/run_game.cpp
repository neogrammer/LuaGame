#include <pch.hpp>
#include "util/lua_util.hpp"

void Game::run()
{

	sol::state L{};
	L.open_libraries(sol::lib::base, sol::lib::bit32, sol::lib::coroutine, sol::lib::debug, sol::lib::ffi, sol::lib::io, sol::lib::jit, sol::lib::math, sol::lib::os, sol::lib::package, sol::lib::string, sol::lib::table, sol::lib::utf8);
	L.safe_script_file("assets/lua_scripts/level.lua");
	{

		

		L.set_function("cpp_setTile", &Game::setTile, this);
		L.set_function("cpp_loadLevel", &Game::ummLoadLevel, this);
		L.set_function("cpp_createDynamicObject", &Game::createDynamicObject, this);
		L.set_function("cpp_assignPlayerControl", &Game::assignPlayerControl, this);
		L.set_function("cpp_moveObject", &Game::moveObject, this);

	    L["LoadLevel"](1);
		


		sol::coroutine loop_coroutine = L["loop"];
		L["counter"] = 20;

		for (int counter = 0; counter < 10 && loop_coroutine; ++counter)
		{
			int value = loop_coroutine();
			std::cout << "In C++: " << value << std::endl;
		}

		sf::Clock fpsTimer;	
		sf::Time elapsed;
		while (mWnd.isOpen())
		{
			sf::Event e;	while (mWnd.pollEvent(e))
			{
				switch (e.type)
				{
				case sf::Event::Closed: 	mGameRunning = false; break;
				case sf::Event::KeyReleased: 	
					if (e.key.code == sf::Keyboard::Escape)  mGameRunning = false; 
					if (e.key.code == sf::Keyboard::B) mShowBBoxes = !mShowBBoxes;
					break;
				default: break;
				}
			}
			elapsed = fpsTimer.restart();
			update(elapsed.asSeconds(), L);
			mWnd.clear(sf::Color::Blue);
			render();
			mWnd.display();
			if (mGameRunning == false) mWnd.close();
		}
	}
	
}