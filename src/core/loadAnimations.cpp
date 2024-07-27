#include <pch.hpp>
#include "Game.hpp"

void Game::Dynamic::loadAnimations()
{
	frames.clear();

	switch ((DynamicType)this->id)
	{
	case DynamicType::NotSet:
		throw std::runtime_error("DynamicType  not set!  Cant animate");
		break;
	case DynamicType::Player:
	{
		this->currentAnim = "idle";
		this->facingLeft = false;
			// right animations
		this->frames.emplace(std::pair{ "idle", false }, std::move(loadAnimation(3, 0, 1, 3, 0)));
		this->animData.emplace(std::pair{ "idle", false }, AnimData{});
		this->animData[std::pair("idle", false)].animDelay = 0.3f;
		this->animData[std::pair("idle", false)].pauseDelay = 0.f;
		  // left animations
		  this->frames.emplace(std::pair{ "idle", true }, std::move(loadAnimation(3, 0, 14, 3, 0)));
		  this->animData.emplace(std::pair{ "idle", true }, AnimData{});
		  this->animData[std::pair("idle", true)].animDelay = 0.3f;
		  this->animData[std::pair("idle", true)].pauseDelay = 0.f;
		  this->loadBBoxes("assets/bboxes/player/player.bbox");
		//... 
	}
		break;

	case DynamicType::MetalBird:
	{
		//  animations
		this->currentAnim = "idle";
		this->facingLeft = true;
		this->frames.emplace(std::pair{ "idle", true }, std::move(loadAnimation(7, 0, 0, 7, 0)));
		this->animData.emplace(std::pair{ "idle", true }, AnimData{});
		this->animData[std::pair("idle", true)].animDelay = 0.3f;
		this->animData[std::pair("idle", true)].pauseDelay = 4.f;
		this->loadBBoxes("assets/bboxes/enemies/metal_bird.bbox");
	}
		break;

	case DynamicType::FlyPad:
	{
		//  animations
		this->currentAnim = "idle";
		this->facingLeft = true;
		this->frames.emplace(std::pair{ "idle", true }, std::move(loadAnimation(3, 0, 0, 3, 0)));
		this->animData.emplace(std::pair{ "idle", true }, AnimData{});
		this->animData[std::pair("idle", true)].animDelay = 0.3f;
		this->animData[std::pair("idle", true)].pauseDelay = 0.f;
		this->loadBBoxes("assets/bboxes/platforms/fly_pad.bbox");
	}
		break;

	case DynamicType::BusterShot_Normal:
	{
		// right animations
		this->currentAnim = "idle";
		this->facingLeft = false;
		this->frames.emplace(std::pair{ "idle", false }, std::move(loadAnimation(5, 0, 0, 5, 0)));
		this->animData[std::pair("idle", false)].animDelay = 0.3f;
		this->animData[std::pair("idle", false)].pauseDelay = 0.f;
		this->animData.emplace(std::pair{ "idle", false }, AnimData{});

		// left animations
		this->frames.emplace(std::pair{ "idle", true }, std::move(loadAnimation(5, 0, 1, 5, 0)));
		this->animData.emplace(std::pair{ "idle", true }, AnimData{});
		this->animData[std::pair("idle", true)].animDelay = 0.3f;
		this->animData[std::pair("idle", true)].pauseDelay = 0.f;
		this->loadBBoxes("assets/bboxes/projectiles/buster_shot_normal.bbox");
	}
		break;
	default:
		throw std::runtime_error("DynamicType does not exist!  Cant animate");
		break;
	}
	this->index = 0;
}




std::vector<sf::IntRect> Game::Dynamic::loadAnimation(int numFrames, int startCol, int startRow, int  pitch, int pitchColBegin)
{
	int colsFirst = pitch - startCol; 
	float rowsAfter = ((float)numFrames - (float)colsFirst) / (float)pitch;
	int rowsBetween = static_cast<int>(rowsAfter);
	int colsLast = static_cast<int>(round((rowsAfter * (float)pitch) / this->size.x));

	std::vector<sf::IntRect> temp={};
	temp.clear();
	temp.reserve(numFrames);

	// first row
	for (int x = startCol + pitchColBegin; x < pitch; x++)
	{
		temp.emplace_back(sf::IntRect{ {x * (int)this->size.x, startRow * (int)this->size.y},{(int)this->size.x,(int)this->size.y} });
	}
	//  middle full rows
	for (int y = 1; y < rowsBetween; y++)
	{
		for (int x = pitchColBegin; x < pitch; x++)
		{
			temp.emplace_back(sf::IntRect{ {x * (int)this->size.x, (startRow + y) * (int)this->size.y},{(int)this->size.x,(int)this->size.y} });
		}
	}
	// final partial row
	for (int x = pitchColBegin; x < colsLast; x++)
	{
		temp.emplace_back(sf::IntRect{ {x * (int)this->size.x, ( startRow + rowsBetween + 1 ) * (int)this->size.y },{ (int)this->size.x,(int)this->size.y} });
	}
	//handled like a pimp
	this->numAnims++;

	return temp;
}

sf::Vector2f Game::Dynamic::getNextPos(float dt)
{
	return { pos.x + (vel.x * dt), pos.y + (vel.y * dt) };
}

sf::Vector2f Game::Dynamic::getLastPos()
{
	return prevPosition;
}



