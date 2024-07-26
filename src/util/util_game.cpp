#include <pch.hpp>



void Game::drawDynamics()
{
	for (const auto& dyno : mDynamicObjects)
	{
		sf::Sprite spr = sf::Sprite{};
		auto& my = *(mDynamicObjects[dyno->id]);

		spr.setTexture(*mDynamicTextures[dyno->id]);
		spr.setPosition(my.pos);
		spr.setTextureRect(my.frames.at(std::pair(my.currentAnim, my.facingLeft)).at(my.index));

		mWnd.draw(spr);
	}
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
				spr.setTextureRect({ {7 * tileSize, 0}, {tileSize, tileSize} });
				spr.setPosition({ (float)tile.x * (float)tileSize, (float)tile.y * (float)tileSize });
				mWnd.draw(spr);
			}	break;
			case TileType::TL:
			{
				sf::Sprite spr{};
				spr.setTexture(tex);
				spr.setTextureRect({ {0 * tileSize, 0}, {tileSize, tileSize} });
				spr.setPosition({ (float)tile.x * (float)tileSize, (float)tile.y * (float)tileSize });
				mWnd.draw(spr);
			}	break;
			case TileType::TOP:
			{
				sf::Sprite spr{};
				spr.setTexture(tex);
				spr.setTextureRect({ {1 * tileSize, 0}, {tileSize, tileSize} });
				spr.setPosition({ (float)tile.x * (float)tileSize, (float)tile.y * (float)tileSize });
				mWnd.draw(spr);
			}
			break;
			case TileType::TR:
			{
				sf::Sprite spr{};
				spr.setTexture(tex);
				spr.setTextureRect({ {2 * tileSize, 0}, {tileSize, tileSize} });
				spr.setPosition({ (float)tile.x * (float)tileSize, (float)tile.y * (float)tileSize });
				mWnd.draw(spr);
			}
			break;
			case TileType::L:
			{
				sf::Sprite spr{};
				spr.setTexture(tex);
				spr.setTextureRect({ {6 * tileSize, 0}, {tileSize, tileSize} });
				spr.setPosition({ (float)tile.x * (float)tileSize, (float)tile.y * (float)tileSize });
				mWnd.draw(spr);
			}
			break;
			case TileType::R:
			{
				sf::Sprite spr{};
				spr.setTexture(tex);
				spr.setTextureRect({ {0 * tileSize, tileSize}, {tileSize, tileSize} });
				spr.setPosition({ (float)tile.x * (float)tileSize, (float)tile.y * (float)tileSize });
				mWnd.draw(spr);
			}
			break;
			case TileType::BL:
			{
				sf::Sprite spr{};
				spr.setTexture(tex);
				spr.setTextureRect({ {3 * tileSize, 2 * tileSize}, {tileSize, tileSize} });
				spr.setPosition({ (float)tile.x * (float)tileSize, (float)tile.y * (float)tileSize });
				mWnd.draw(spr);
			}
			break;
			case TileType::B:
			{
				sf::Sprite spr{};
				spr.setTexture(tex);
				spr.setTextureRect({ {tileSize, 2 * tileSize}, {tileSize, tileSize} });
				spr.setPosition({ (float)tile.x * (float)tileSize, (float)tile.y * (float)tileSize });
				mWnd.draw(spr);
			}
			break;
			case TileType::BR:
			{
				sf::Sprite spr{};
				spr.setTexture(tex);
				spr.setTextureRect({ {2 * tileSize, 2 * tileSize}, {tileSize, tileSize} });
				spr.setPosition({ (float)tile.x * (float)tileSize, (float)tile.y * (float)tileSize });
				mWnd.draw(spr);
			}
			break;
			default:
				break;
			}
		}
	}
}