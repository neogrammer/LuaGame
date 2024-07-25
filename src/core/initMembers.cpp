#include <pch.hpp>

void Game::Dynamic::initMembers()
{
	
	switch ((DynamicType)this->id)
	{
	case DynamicType::NotSet:
		throw std::runtime_error("DynamicType not set!  Cant init");
		break;
	case DynamicType::Player:
		this->size = {130.f,160.f};
		this->unidirectional = false;
		this->speed = {200.f,200.f};
		break;
	case DynamicType::MetalBird:
		this->size = {220.f,296.f};
		this->unidirectional = true;
		this->speed = {0.f,0.f};
		break;
	case DynamicType::FlyPad:
		this->size = {67.f,40.f};
		this->unidirectional = true;
		this->speed = {200.f, 200.f};
		break;
	case DynamicType::BusterShot_Normal:
		this->size = {24.f,18.f};
		this->unidirectional = false;
		this->speed = {600.f, 0.f};
		break;
	default:
		throw std::runtime_error("DynamicType does not exist!  Cant init");
		break;
	}
	loadAnimations();
}