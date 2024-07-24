#include <pch.hpp>



void Game::drawDynamics()
{
	for (const auto& dyno : mDynamicObjects)
	{
		sf::Sprite spr = sf::Sprite{};
		auto& my = *(mDynamicObjects[dyno->id]);

		spr.setTexture(*mDynamicTextures[dyno->id]);
		spr.setPosition(my.pos);
		spr.setTextureRect({ {0 , 0}, {(int)my.size.x, (int)my.size.y} });

		mWnd.draw(spr);
	}
}

int Game::lua_loadLevel(lua_State* L)
{
	if (lua_gettop(L) != 3) return -1;
	Game* obj = static_cast<Game*>(lua_touserdata(L, 1));
	int w = (int)lua_tointeger(L, 2);
	int h = (int)lua_tointeger(L, 3);
	obj->loadLevel(w, h);
	return 0;
}

int Game::lua_assignPlayerControl(lua_State* L)
{
	if (lua_gettop(L) != 2) return -1;
	Game* object = static_cast<Game*>(lua_touserdata(L, 1));
	Dynamic* dyno = static_cast<Dynamic*>(lua_touserdata(L, 2));
	object->assignPlayerControl(*dyno);
	return 0;
}


void Game::drawTilemap()
{

	sf::Vector2i tile = { 0, 0 };
	for (tile.y = 0; tile.y < mLevelSize.y; tile.y++)
	{
		for (tile.x = 0; tile.x < mLevelSize.x; tile.x++)
		{
			TileType b = mLevelVec[(uint8_t)tile.y * mLevelSize.x + tile.x];
			switch (b)
			{
			case TileType::Empty:		break;
			case TileType::Solid:
			{
				sf::Sprite spr{};
				spr.setTexture(tex);
				spr.setTextureRect({ {7 * 32, 0}, {32, 32} });
				spr.setPosition({ (float)tile.x * 32.f, (float)tile.y * 32.f });
				mWnd.draw(spr);
			}	break;
			case TileType::TL:
			{
				sf::Sprite spr{};
				spr.setTexture(tex);
				spr.setTextureRect({ {0 * 32, 0}, {32, 32} });
				spr.setPosition({ (float)tile.x * 32.f, (float)tile.y * 32.f });
				mWnd.draw(spr);
			}	break;
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
}