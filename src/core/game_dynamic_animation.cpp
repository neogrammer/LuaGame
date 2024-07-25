#include <pch.hpp>
#include "Game.hpp"


bool Game::Dynamic::AnimData::isOnLastFrame()
{
	return false;
}



int Game::Dynamic::AnimData::getIndex()
{
	return index;
}

sf::IntRect Game::Dynamic::AnimData::getBBox()
{
	return bbox.at(index);
}


void Game::Dynamic::AnimData::animate()
{
	if (index + 1  >= numFrames && this->looping == false)
	{
		index = numFrames - 1;
		onLastFrame = true;
	}
	else if (index + 1 >= numFrames && this->looping == true)
	{
		onLastFrame = false;
		index = 0;
	}
	else if (index + 1 == numFrames - 1)
	{
		index++;
		onLastFrame = true;
	}
	else if (index + 1 < 0)
	{
		throw std::runtime_error("index negative!");
	}
	else
	{
		index++;
		onLastFrame = false;
	}
}

void Game::Dynamic::AnimData::resetData()
{
	this->index = 0;
	onLastFrame = false;
	playing = true;

}

void Game::Dynamic::AnimData::play()
{
	playing = true;
	this->index = 0;
}

void Game::Dynamic::AnimData::stop()
{
	playing = false;
	this->index = 0;
}

void Game::Dynamic::AnimData::pause()
{
	playing = false;
}

void Game::Dynamic::AnimData::resume()
{
	playing = true;
}



