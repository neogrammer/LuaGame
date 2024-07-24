#include <pch.hpp>

int main(int argc, char* argv[])
{
	Cfg::Initialize();

	sf::ContextSettings settings{};
	settings.antialiasingLevel = 8;
	Game demo{ settings };
	demo.run();

	return 0;
}
