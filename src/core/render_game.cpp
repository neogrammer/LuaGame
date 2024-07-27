#include <pch.hpp>



void Game::render()
{


	drawDynamics();
	drawTilemap();
	if (mShowBBoxes)
	{
		
		for (int y = 0; y < mLevelSize.y; y++)
		{
			for (int x = 0; x < mLevelSize.x; x++)
			{
				int idx = y * mLevelSize.x + x;
				if (idx >= mLevelVec.size()) break;
				if (mLevelVec.at(idx) == TileType::Empty || mLevelVec.at(idx) == TileType::Solid)
				{
					continue;
				}
				else
				{
					sf::RectangleShape shp;
					shp.setSize({ (float)tileSize - 1.f,(float)tileSize -1.f });
					shp.setPosition({ (float)(x * tileSize), (float)(y * tileSize) });
					shp.setFillColor(sf::Color::Transparent);
					shp.setOutlineThickness(1);
					shp.setOutlineColor(sf::Color::Red);
					mWnd.draw(shp);

			

				}
			}
		}

		for (auto& dyno : mDynamicObjects)
		{
			sf::RectangleShape shp;
			shp.setSize({ dyno->getAABB().width -1.f ,dyno->getAABB().height - 1.f});
			shp.setPosition({ dyno->getAABB().left,dyno->getAABB().top});
			shp.setFillColor(sf::Color::Transparent);
			shp.setOutlineThickness(1);
			shp.setOutlineColor(sf::Color::Red);
		
			mWnd.draw(shp);
		
		}


	}

}