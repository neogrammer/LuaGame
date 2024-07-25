#include <pch.hpp>
#include "Game.hpp"


void Game::Dynamic::loadBBoxes(const std::string& filename)
{
	std::ifstream file;
	file.open(filename);
	if (!file.is_open() || !file.good()) { throw std::runtime_error("File opened for loadin bboxes is no bueno!"); }
	int numberOfFrames;

	while (file >> numberOfFrames) // any more left in the file to read?
	{
		std::string animname{}, facingleft{};
		file >> animname >> facingleft;
		bool left = ((facingleft == "left") ? true : false );

		this->animData.at(std::pair(animname, left)).bbox.clear();
		this->animData.at(std::pair(animname, left)).bbox.reserve(numberOfFrames);
		for (int i = 0; i < numberOfFrames; i++)
		{
			int l{}, t{}, w{}, h{};
			file >> l >> t >> w >> h;
			this->animData.at(std::pair(animname, left)).bbox.emplace_back(sf::IntRect{ {l,t},{w,h} });
			this->animData.at(std::pair(animname, left)).numFrames++;
		}
		if (!hasBBoxesSet(animname, left))
		{
			throw std::runtime_error("BBoxes for " + animname + facingleft + " is not adequate for its corresponding animation!");
		}
	}
	// bounding boxes loaded successfully for all animations depicted in filename
	
}

bool Game::Dynamic::hasBBoxesSet(const std::string animname, bool facingleft)
{
	if (animData.at(std::pair(animname, facingleft)).bbox.size() > 0)
	{
		if (animData.at(std::pair(animname, facingleft)).bbox.size() != animData.at(std::pair(animname, facingleft)).numFrames)
		{
			throw std::runtime_error("animation " + animname + (facingleft ? " left " : " right ") + " exists, but does not have enough bboxes for the frames of animation set!");
		}
		else
		{
			return true;
		}
	}

	return false;
}



