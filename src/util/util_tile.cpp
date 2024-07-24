#include <pch.hpp>


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
