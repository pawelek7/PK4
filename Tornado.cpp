#include "Tornado.h"

#pragma Constructors

Tornado::Tornado(const sf::Texture & texture, const std::vector<Frames> & frames)
	:Disaster(texture, frames, DisasterType::TORNADO)
{ }

#pragma endregion

#pragma region Class_Methods

void Tornado::UpdateDisaster(float elapsedTime)
{
	this->ThornadoIntelligence(elapsedTime);

	this->counterLife++;
	if (this->counterLife > this->disasterLifetime)
	{
		this->disasterEnd = true;
	}
}

void Tornado::UpdateActualTornadoXY()
{
//FIX LATER
	this->mapY = -((this->sizeMap * TILE_SIZE - this->sprite.getPosition().x) / TILE_SIZE - (this->sprite.getPosition().y / TILE_SIZE * 0.5));
	this->mapX = ((this->sizeMap * TILE_SIZE - this->sprite.getPosition().x) / TILE_SIZE) + this->mapY;
}

void Tornado::ReverseThornado(int e_direction)
{
	switch (e_direction)
	{
	case 1:
		moveUp = false;
		sprite.move(0, 10);
		break;
	case 2:
		moveDown = false;
		sprite.move(0, -10);
		break;
	case 3:
		moveLeft = false;
		sprite.move(10, 0);
		break;
	case 4:
		moveRight = false;
		sprite.move(-10, 0);
		break;
	default:
		moveUp = false;
		moveDown = false;
		moveLeft = false;
		moveRight = false;
		sprite.move(0, 0);
		break;
	}
	this->UpdateActualTornadoXY();
}

void Tornado::ResetMovement()
{
	moveUp = true;
	moveDown = true;
	moveRight = true;
	moveLeft = true;
}

void Tornado::InitializeTornado()
{
	this->mapX = this->randomEngine.RandomiseEvent(0, this->sizeMap);
	this->mapY = this->randomEngine.RandomiseEvent(0, this->sizeMap);

	tornadoPosition.x = (this->mapY - this->mapX) * TILE_SIZE + this->sizeMap * TILE_SIZE;
	tornadoPosition.y = (this->mapY + this->mapX) * TILE_SIZE * 0.5f;

	this->SetSpritePosition(tornadoPosition);
}

void Tornado::ThornadoIntelligence(float elapsedTime)
{
	this->UpdateActualTornadoXY();

	while (this->mapX < 0 || this->mapY < 0 || this->mapX > this->sizeMap || this->mapY > this->sizeMap)
	{
		this->ReverseThornado(this->tornadoDirection);
	}
	
	this->movementCounter++;

	if (this->movementCounter >= 30)
	{
		this->tornadoDirection = this->randomEngine.RandomiseEvent(0, 5);
		this->movementCounter = 0;
	}

	double movement = this->tornadoSpeed * elapsedTime;

	sf::Vector2f move(0.0f, 0.0f);

	switch (this->tornadoDirection)
	{
	case 1:
		if (moveUp == true)
		move.y -= movement;
		break;
	case 2:
		if(moveDown == true)
		move.y += movement;
		break;
	case 3:
		if(moveLeft == true)
		move.x -= movement;
		break;
	case 4:
		if(moveRight == true)
		move.x += movement;
		break;
	}

	this->ResetMovement();

	this->sprite.move(move);
}

#pragma endregion

#pragma region Setters

void Tornado::SetTornadoSpeed(int speed)
{
	this->tornadoSpeed = speed;
}

void Tornado::SetTornadoLifeTime(int lifeTime)
{
	this->disasterLifetime = lifeTime;
}

#pragma endregion

#pragma region Getters

sf::Vector2i Tornado::GetTornadoCoordinates() const
{
	return sf::Vector2i(this->mapX, this->mapY);
}

sf::Vector2f Tornado::GetTornadoPosition() const
{
	return this->tornadoPosition;
}

int Tornado::GetTornadoDirection() const
{
	return this->tornadoDirection;
}

sf::Vector2f Tornado::GetTornadoSpritePosition() const
{
	return this->sprite.getPosition();
}

sf::FloatRect Tornado::GetTornadoGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

#pragma endregion