#include <pch.hpp>

void Game::manipulate(float dt, lua_State* L)
{
	for (auto& m : mNewManipulators)
	{
		Manipulator* man{ std::move(m) };
		mManipulators.emplace_back(std::move(man));
		man = nullptr;
		m = nullptr;

	}
	mNewManipulators.clear();
	mNewManipulators.shrink_to_fit();
	for (auto& m : mManipulators)
	{
		if (m->update(dt))
		{
			if (m->dyno->dType == DynamicType::BusterShot_Normal)
			{
				lua_getglobal(L, "IssueNextHorizTask");
				if (L, lua_isfunction(L, -1))
				{
					lua_pushlightuserdata(L, this);
					lua_pushlightuserdata(L, m->dyno);
					lua_pushnumber( L, dynamic_cast<DynBullet*>(m->dyno)->maxDist);
					lua_pushnumber(L, m->dyno->pos.y);
					if (!mylua::CheckLua(L, lua_pcall(L, 4, 1, 0)))
					{
						// script bad
					}
				}
			}
			else
			{
				lua_getglobal(L, "IssueNextTask");
				if (L, lua_isfunction(L, -1))
				{
					lua_pushlightuserdata(L, this);
					lua_pushlightuserdata(L, m->dyno);
					if (!mylua::CheckLua(L, lua_pcall(L, 2, 1, 0)))
					{
						// script bad
					}
				}
			}
		}
	}

	std::erase_if(mManipulators, [](Manipulator* m)
		{ return m->complete; });
}


void Game::input(float dt)
{
	if (underPlayerControl)
	{

		underPlayerControl->vel = { 0.f, 0.f };
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) underPlayerControl->vel += { 0.f, -50.f};
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) underPlayerControl->vel += { -50.f, 0.f};
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) underPlayerControl->vel += { 0.f, 50.f};
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) underPlayerControl->vel += { 50.f, 0.f};
		// DO PLAYER COLLISIONS HERE
		underPlayerControl->pos += underPlayerControl->vel * dt;

	}

}

void Game::update(float dt, lua_State* L)
{
	manipulate(dt, L);
	

	input(dt);
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

	

	for (const auto& dyno : mDynamicObjects)
	{
		sf::Sprite spr = sf::Sprite{};
		auto& my = *(mDynamicObjects[dyno->id]);

		spr.setTexture(*mDynamicTextures[dyno->id]);
		spr.setPosition(my.pos);
		spr.setTextureRect({ {0 , 0}, {(int)my.size.x, (int)my.size.y} });

		mWnd.draw(spr);
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
	, mDynamicObjects{ std::vector<Dynamic*>{} }
	, mDynamicTextures{ std::vector<sf::Texture*>{} }	
	, underPlayerControl{nullptr}
{
	mWnd.setPosition({ 100,55 });
	mGameRunning = true;
	tex.loadFromFile("assets/textures/tilesets/map1/platformer1.png");



	mDynamicObjects.clear();
	mDynamicTextures.clear();
	mDynamicTextures.reserve(3);
	mDynamicObjects.reserve(3);
	
	mDynamicTextures.push_back(&Cfg::textures.get((int)Cfg::Textures::PlayerAtlas));
	
	mDynamicTextures.push_back(&Cfg::textures.get((int)Cfg::Textures::MetalBird));
	
	mDynamicTextures.push_back(&Cfg::textures.get((int)Cfg::Textures::BusterShot_Normal));

	mDynamicTextures.push_back(&Cfg::textures.get((int)Cfg::Textures::FlyPad));


}

Game::Game(sf::ContextSettings& settings)
	: mWnd{ sf::VideoMode{1280U,768U,32U},"LuaGame",sf::Style::Close, settings }
	, player{}
	, player2{}
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
			

		}



	}
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
			

		}


	}
	lua_close(N);

	lua_State* Lvl = luaL_newstate();
	luaL_openlibs(Lvl);
	lua_register(Lvl, "cpp_loadLevel", lua_loadLevel);
	lua_register(Lvl, "cpp_setTile", lua_setTile);
	lua_register(Lvl, "cpp_createDynamicObject", lua_createDynamicObject);
	lua_register(Lvl, "cpp_assignPlayerControl", lua_assignPlayerControl);
	lua_register(Lvl, "cpp_moveObject", lua_moveObject);
	
	if (mylua::CheckLua(Lvl, luaL_dofile(Lvl, "assets/lua_scripts/level.lua")))
	{
		lua_getglobal(Lvl, "LoadLevel");
		if(lua_isfunction(Lvl, -1))
		{
			lua_pushlightuserdata(Lvl, this);
			lua_pushnumber(Lvl, 1);
			if (mylua::CheckLua(Lvl, lua_pcall(Lvl, 2, 1, 0)))
			{
				std::cout << "Success" << std::endl;
			}
		}







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
					elapsed = fpsTimer.restart();

					

			
						update(elapsed.asSeconds(), Lvl);
						

				
						//render game frame
						mWnd.clear(sf::Color::Blue);
						render();
						mWnd.display();
					

					if (mGameRunning == false) mWnd.close();
				}

			
		


	}
	lua_close(Lvl);
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
	return tmp;
	
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

