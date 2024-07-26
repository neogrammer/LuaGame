#include <pch.hpp>



void Game::render()
{
	drawTilemap();

	drawDynamics();
	
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
					shp.setSize({ (float)tileSize,(float)tileSize });
					shp.setPosition({ (float)(x * tileSize), (float)(y * tileSize) });
					shp.setFillColor(sf::Color::Transparent);
					shp.setOutlineThickness(2);
					shp.setOutlineColor(sf::Color::Red);
					mWnd.draw(shp);
				}
			}
		}

		for (auto& dyno : mDynamicObjects)
		{
			sf::RectangleShape shp;
			shp.setSize({ dyno->getAABB().width,dyno->getAABB().height});
			shp.setPosition({ dyno->getAABB().left,dyno->getAABB().top});
			shp.setFillColor(sf::Color::Transparent);
			shp.setOutlineThickness(2);
			shp.setOutlineColor(sf::Color::Red);
		
			mWnd.draw(shp);
		}


	}

}