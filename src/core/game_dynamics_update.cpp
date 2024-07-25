#include <pch.hpp>
#include "Game.hpp"

void Game::Dynamic::update(float dt)
{
	// Handle animation frame switching and pause at the start of an animation if it has a pause delay of more than 0.f
	this->pauseElapsed += dt;
	if (this->pauseElapsed >= this->animData.at(std::pair(this->currentAnim, this->facingLeft)).pauseDelay && this->animPaused == true)
	{
		this->elapsed = std::min(this->pauseElapsed - dt, 0.f);
		this->animPaused = false;
	}
	if (this->animPaused)
	{
		if (pauseElapsed > this->animData.at(std::pair(this->currentAnim, this->facingLeft)).animDelay)
		{
			if (this->animData.at(std::pair(this->currentAnim, this->facingLeft)).looping)
			{
				index = 0;
				this->animData.at(std::pair(this->currentAnim, this->facingLeft)).index = 0;
			}
		 }
	}

	if (this->animPaused == false)
	{
		this->elapsed += dt;
		if (this->index < 0 || this->index > this->animData.at(std::pair(this->currentAnim, this->facingLeft)).numFrames)
		{
			throw std::runtime_error("Oh no! index for dynamic is out of range of the current animation selected to run");
		}

		if (this->elapsed >= this->animData.at(std::pair(this->currentAnim, this->facingLeft)).animDelay)
		{
			this->elapsed = 0.f;
			this->animData.at(std::pair(this->currentAnim, this->facingLeft)).animate();
			this->index = this->animData.at(std::pair(this->currentAnim, this->facingLeft)).index;

			if (this->animData.at(std::pair(this->currentAnim, this->facingLeft)).onLastFrame)
			{
				this->animPaused = true;
				this->pauseElapsed = 0.f;
			}
		}
	}

}