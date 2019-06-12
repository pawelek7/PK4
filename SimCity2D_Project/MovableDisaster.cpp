#include "MovableDisaster.h"

MovableDisaster::MovableDisaster(const sf::Texture & texture, const std::vector<Frames> & frames, DisasterType disasterType)
	:Disaster(texture, frames, disasterType)
{
	//nothing
}


void MovableDisaster::ReverseDisaster(int direction)
{
	switch (direction) //reverse depending on actual position
	{
	case 1:
		this->moveUp = false;
		this->sprite.move(0, 10);
		break;
	case 2:
		this->moveDown = false;
		this->sprite.move(0, -10);
		break;
	case 3:
		this->moveLeft = false;
		this->sprite.move(10, 0);
		break;
	case 4:
		this->moveRight = false;
		this->sprite.move(-10, 0);
		break;
	default:
		this->moveUp = false;
		this->moveDown = false;
		this->moveLeft = false;
		this->moveRight = false;
		this->sprite.move(0, 0);
		break;
	}

	this->UpdateActualCoordinates();
}

void MovableDisaster::UpdateActualCoordinates()
{
	this->mapY = -((this->sizeMap * TILE_SIZE - this->sprite.getPosition().x) / TILE_SIZE - (this->sprite.getPosition().y / TILE_SIZE * 0.5));
	this->mapX = ((this->sizeMap * TILE_SIZE - this->sprite.getPosition().x) / TILE_SIZE) + this->mapY;
}

void MovableDisaster::ResetMovement()
{
	this->moveUp = true; 
	this->moveDown = true;
	this->moveRight = true;
	this->moveLeft = true;
}

void MovableDisaster::SetDisasterMovableSpeed(int speed)
{
	this->disasterSpeed = speed;
}

void MovableDisaster::SetDisasterMovableLifeTime(int lifeTime)
{
	this->disasterLifetime = lifeTime;
}

int MovableDisaster::GetDisasterMovableDirection() const
{
	return this->disasterDirection;
}

sf::FloatRect MovableDisaster::GetDisasterMovableGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

sf::Vector2i MovableDisaster::GetDisasterMovableCoordinates() const
{
	return sf::Vector2i(this->mapX, this->mapY);
}

sf::Vector2f MovableDisaster::GetDisasterMovablePosition() const
{
	return this->sprite.getPosition();
}