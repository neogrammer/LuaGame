#include <pch.hpp>
#include <core/Game.hpp>


void Game::setTile(int x, int y, int t)
{

	switch (t)
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

void Game::ummLoadLevel(int w, int h, int level)
{
	if (level == 1)
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
		std::string map;
		map.append("........................................");
		map.append("........................................");
		map.append("........................................");
		map.append("..............................QWWWWWWWWW");
		map.append("............QWWE..............ASSS######");
		map.append("WWWWWE......A##R..................AS####");
		map.append("##SSSD.......A#R....................AS##");
		map.append("#R............LR......................L#");
		map.append("#R............LR......................L#");
		map.append("#R............LR......................L#");
		map.append("#R....QWE.....LR......................L#");
		map.append("#R....L##WWWWW#R......................L#");
		map.append("#R....ASSSSSSSSD......................L#");
		map.append("#R....................................L#");
		map.append("#R....................................L#");
		map.append("#R....................................L#");
		map.append("#R....................................L#");
		map.append("#R....................................L#");
		map.append("#R....................................L#");
		map.append("#R....................................L#");
		map.append("#R....................................L#");
		map.append("#R....................................L#");
		map.append("#R..........QWWWE.....................L#");
		map.append("##WWWWWWWWWW#####WWWWWWWWWWWWWWWWWWWWW##");

		for (int y = 0; y < h; y++)
		{
			for (int x = 0; x < w; x++)
			{
				char c = map.at(y * w + x);

				if (c == '.')
					setTile(x, y, (int)TileType::Empty);
				else if (c == '#')
					setTile(x, y, (int)TileType::Solid);
				else if (c == 'Q')
					setTile(x, y, (int)TileType::TL);
				else if (c == 'W')
					setTile(x, y, (int)TileType::TOP);
				else if (c == 'E')
					setTile(x, y, (int)TileType::TR);
				else if (c == 'L')
					setTile(x, y, (int)TileType::L);
				else if (c == 'R')
					setTile(x, y, (int)TileType::R);
				else if (c == 'A')
					setTile(x, y, (int)TileType::BL);
				else if (c == 'S')
					setTile(x, y, (int)TileType::B);
				else  if (c == 'D')
					setTile(x, y, (int)TileType::BR);
			}
		}
	}
}

int Game::lua_setTile(lua_State* L)
{
	if (lua_gettop(L) != 4) return -1;
	Game* obj = static_cast<Game*>(lua_touserdata(L, 1));
	int x = (int)lua_tointeger(L, 2);
	int y = (int)lua_tointeger(L, 3);
	int type = (int)lua_tonumber(L, 4);
	obj->setTile(x, y, type);


	return 0;
};
