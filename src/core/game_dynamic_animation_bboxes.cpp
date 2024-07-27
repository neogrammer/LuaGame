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

void Game::Dynamic::setAABB()
{
	sf::IntRect bbox = this->animData[std::pair(this->currentAnim, this->facingLeft)].getBBox();
	this->aabb.left = this->pos.x + (float)bbox.left;
	this->aabb.top = this->pos.y + (float)bbox.top;
	this->aabb.width = (float)bbox.width;
	this->aabb.height = (float)bbox.height;
}

sf::FloatRect Game::Dynamic::getAABBNoChange()
{
	sf::IntRect bbox = this->animData[std::pair(this->currentAnim, this->facingLeft)].getBBox();
	sf::FloatRect tmp{};
	tmp.left = this->pos.x + (float)bbox.left;
	tmp.top = this->pos.y + (float)bbox.top;
	tmp.width = (float)bbox.width;
	tmp.height = (float)bbox.height;

	return tmp;
}

sf::FloatRect& Game::Dynamic::getAABB()
{
	sf::IntRect bbox = this->animData[std::pair(this->currentAnim, this->facingLeft)].getBBox();
	this->aabb.left = this->pos.x + (float)bbox.left;
	this->aabb.top = this->pos.y + (float)bbox.top;
	this->aabb.width = (float)bbox.width;
	this->aabb.height = (float)bbox.height;

	return aabb;
}

sf::Vector2f Game::Dynamic::getAABBCenter()
{
	return { this->getAABB().getPosition().x + (this->getAABB().getSize().x / 2.f), this->getAABB().getPosition().y + (this->getAABB().getSize().y / 2.f) };
}

sf::Vector2f Game::Dynamic::getAABBHalfSize()
{
	return { this->getAABB().getSize().x / 2.f, this->getAABB().getSize().y / 2.f };
}

sf::Vector2f Game::Dynamic::getCenterOffset()
{
	
	sf::Sprite spr = sf::Sprite{};
	auto& my = *this;
	
	spr.setTexture(Cfg::textures.get(my.id));
	spr.setPosition(my.pos);
	spr.setTextureRect(my.frames.at(std::pair(my.currentAnim, my.facingLeft)).at(my.index));

		sf::CircleShape circ{ 5.f };
		circ.setFillColor(sf::Color::Yellow);
		circ.setOrigin({ 2.5f, 2.5f });
		circ.setPosition({ ((float)spr.getTextureRect().width / 2.f) + spr.getPosition().x - spr.getOrigin().x, ((float)spr.getTextureRect().height / 2.f) + spr.getPosition().y - spr.getOrigin().y });

		sf::CircleShape circ2{ 5.f };
		circ2.setFillColor(sf::Color::Green);
		circ2.setOrigin({ 2.5f, 2.5f });
		circ2.setPosition({ my.getAABB().left + (my.getAABB().width / 2.f) , my.getAABB().top + (my.getAABB().height / 2.f) });

		sf::Vector2f offset = { circ2.getPosition().x - circ.getPosition().x, circ2.getPosition().y - circ.getPosition().y };

		return offset;
}



