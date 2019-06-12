#include "Tornado.h"

#pragma Constructors

Tornado::Tornado(const sf::Texture & texture, const std::vector<Frames> & frames)
	:MovableDisaster(texture, frames, DisasterType::TORNADO)
{ 
	//nothing
}

#pragma endregion

#pragma region Class_Methods

void Tornado::UpdateTornado(const float elapsedTime)
{
	this->ThornadoIntelligence(elapsedTime); //tornado behaviour

	this->counterLife++;
	if (this->counterLife > this->disasterLifetime) //if the lifetime of the tornado ends, inform about its completion
	{
		this->disasterEnd = true;
	}
}


void Tornado::InitializeTornado()
{
	//randomise tornado position
	this->mapX = this->randomEngine.RandomiseEvent(0, this->sizeMap);
	this->mapY = this->randomEngine.RandomiseEvent(0, this->sizeMap);

	//set tornado on map
	this->actualPositionDisaster.x = (this->mapY - this->mapX) * TILE_SIZE + this->sizeMap * TILE_SIZE;
	this->actualPositionDisaster.y = (this->mapY + this->mapX) * TILE_SIZE * 0.5f;

	this->SetSpritePosition(this->actualPositionDisaster);
}


void Tornado::ThornadoIntelligence(const float elapsedTime)
{
	this->UpdateActualCoordinates(); //update tornado coordinates

	//if the tornado is off the map, turn it back
	if (this->mapX < 0 || this->mapY < 0 || this->mapX > this->sizeMap || this->mapY > this->sizeMap)
	{
		this->ReverseDisaster(this->disasterDirection);
	}
	
	this->movementCounter++;

	//change the trajectory of the tornado
	if (this->movementCounter >= 30)
	{
		this->disasterDirection = this->randomEngine.RandomiseEvent(0, 5);
		this->movementCounter = 0;
	}

	double movement = this->disasterSpeed * elapsedTime;

	sf::Vector2f move(0.0f, 0.0f);

	switch (this->disasterDirection) //move tordado depending of direction
	{
	case 1:
		if (this->moveUp == true)
		move.y -= movement;
		break;
	case 2:
		if(this->moveDown == true)
		move.y += movement;
		break;
	case 3:
		if(this->moveLeft == true)
		move.x -= movement;
		break;
	case 4:
		if(this->moveRight == true)
		move.x += movement;
		break;
	}

	this->ResetMovement(); 

	this->sprite.move(move); //move sprite
}

#pragma endregion