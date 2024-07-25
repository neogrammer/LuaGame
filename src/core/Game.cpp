#include <pch.hpp>
#include "util/lua_util.hpp"

void Game::input(float dt, lua_State* L)
{
	if (underPlayerControl)
	{

		underPlayerControl->vel = { 0.f, 0.f };
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			underPlayerControl->vel += { 0.f, -50.f};
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			underPlayerControl->vel += { -50.f, 0.f};
			underPlayerControl->facingLeft = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			underPlayerControl->vel += { 0.f, 50.f};
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			underPlayerControl->vel += { 50.f, 0.f};
			underPlayerControl->facingLeft = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{

		}
		// DO PLAYER COLLISIONS HERE
		underPlayerControl->pos += underPlayerControl->vel * dt;

	}

}

void Game::update(float dt, lua_State* L)
{
	manipulate(dt, L);
	input(dt, L);
	for (auto& dyno : mDynamicObjects)
	{
		dyno->update(dt);
	}
}

	

Game::Game(sf::ContextSettings& settings)
	: mWnd{ sf::VideoMode{1280U,768U,32U},"LuaGame",sf::Style::Close, settings }
	, tex{}
	, mDynamicObjects{ std::vector<Dynamic*>{} }
	, mDynamicTextures{ std::vector<sf::Texture*>{} }
	, underPlayerControl{nullptr}
{
	mWnd.setPosition({ 100,55 });
	mGameRunning = true;
	tex.loadFromFile("assets/textures/tilesets/map1/platformer1.png");
	mDynamicObjects.clear();
	mDynamicTextures.clear();
	mDynamicTextures.reserve(4);
	mDynamicObjects.reserve(4);
	mDynamicTextures.push_back(&Cfg::textures.get((int)Cfg::Textures::PlayerAtlas));
	mDynamicTextures.push_back(&Cfg::textures.get((int)Cfg::Textures::MetalBird));
	mDynamicTextures.push_back(&Cfg::textures.get((int)Cfg::Textures::BusterShot_Normal));
	mDynamicTextures.push_back(&Cfg::textures.get((int)Cfg::Textures::FlyPad));
}

Game::~Game()
{
	underPlayerControl = nullptr;
	for (auto& dyno : mDynamicObjects)
	{
		if (dyno)
			delete dyno;
	}

	for (auto& dyno : mDynamicTextures)
	{
		if (dyno)
			dyno = nullptr;
	}

	destroyAllManipluators(mManipulators);
	destroyAllManipluators(mNewManipulators);

	bool found = false;
	auto it = std::find_if(mManipulators.begin(), mManipulators.end(), [&found](Manipulator* m)->bool { if (m->complete == true) found = true; return found; });
	while (found)
	{
		delete (*it);
		*it = nullptr;
		mManipulators.erase(it);
		mManipulators.shrink_to_fit();
		auto it = std::find_if(mManipulators.begin(), mManipulators.end(), [&found](Manipulator* m)->bool { if (m->complete == true) found = true; return found; });
	}
}

void Game::cleanupManipluators(std::vector<Manipulator*>& vec)
{
	bool scrubbed = false;

	while(!scrubbed)
	{ 
			if (isManipulatorCompleted(vec))
			{
				scrubbed = false;
			}

			if (scrubbed == false)
			{
				bool found = false;
				auto it = std::find_if(vec.begin(), vec.end(), [&found](Manipulator* m)->bool { if (m->complete == true) found = true; return found; });

				if (found)
				{
					delete (*it);
					*it = nullptr;
					vec.erase(it);
					vec.shrink_to_fit();
				}
				else
				{
					scrubbed = true;
				}
			}
	}
}

void Game::destroyAllManipluators(std::vector<Manipulator*>& vec)
{

	bool scrubbed = false;

	while (!scrubbed)
	{
		if (vec.size() > 0 && vec.begin() != vec.end())
		{
			scrubbed = false;
		}
		else
		{
			scrubbed = true;
		}

		if (scrubbed == false)
		{
				auto it = vec.begin();
				delete (*it);
				*it = nullptr;
				vec.erase(it);
				vec.shrink_to_fit();
		}
	}
}

bool Game::isManipulatorCompleted(std::vector<Manipulator*>& vec)
{
	bool found = false;
	auto it = std::find_if(vec.begin(), vec.end(), [&found](Manipulator* m)->bool { if (m->complete == true) found = true; return found; });
	return found;
}

void Game::loadLevel(int w, int h)
{
	mLevelSize = { w, h };
	mLevelVec.clear();
	mLevelVec.reserve((uint8_t)w * h);
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			mLevelVec.emplace_back(TileType::Empty);
		}
	}



	std::cout << w << " " << h << std::endl;
}

Game::Dynamic* Game::createDynamicObject(int type, float x, float y, float w, float h, int dir)
{
	Dynamic* tmp{ nullptr };
	if (type == 0)
	{
		tmp = new Dynamic{};
		tmp->dType = DynamicType::Player;
	}
	else if (type == 1)
	{
		tmp = new Dynamic{};
		tmp->dType = DynamicType::MetalBird;
	}
	else if (type == 2)
	{
		tmp = new DynBullet{};

		tmp->dType = DynamicType::BusterShot_Normal;

		if (dir == 0)
		{
			// move left
			dynamic_cast<DynBullet*>(tmp)->dir = { -1.f, 0.f };
		}
		else
		{
			// move right
			dynamic_cast<DynBullet*>(tmp)->dir = { 1.f, 0.f };

		}
		dynamic_cast<DynBullet*>(tmp)->maxDist =  Cfg::ScrW + (int)(dynamic_cast<DynBullet*>(tmp)->dir.x * (int)x);
	}
	else if (type == 3)
	{
		tmp = new Dynamic{};
		tmp->dType = DynamicType::FlyPad;
	}
	else
	{
		tmp = new Dynamic{};
		tmp->dType = DynamicType::NotSet;
	}
	tmp->id = type;
	tmp->pos = { x, y };
	tmp->size = { w, h };

	mDynamicObjects.emplace_back( std::move(tmp) );
	mDynamicObjects.back()->initMembers();
	return mDynamicObjects[(std::size_t)(mDynamicObjects.size() - 1)];
	
}

void Game::assignPlayerControl(Dynamic& dyno)
{
	Dynamic* ptr = &dyno; //auto ptr = std::find_if(mDynamicObjects.begin(), mDynamicObjects.end(), [&dyno](const std::shared_ptr<Dynamic>& p) { return p.get() == dyno; });
	underPlayerControl = ptr;
	ptr = nullptr;
}

void Game::moveObject(Dynamic& dyno, float x, float y, float time)
{
	Dynamic* tmp = &dyno;
	mNewManipulators.emplace_back(new ManInterpPos{ std::move(tmp), x, y, time });
	tmp = nullptr;
}