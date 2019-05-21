#include "Fire.h"

#include <iostream>

#pragma region Constructors

Fire::Fire(const sf::Texture & texture, const std::vector<Frames> & frames)
	:Disaster(texture, frames, DisasterType::FIRE)
{ }

#pragma endregion

#pragma region Class_Methods

void Fire::UpdateDisaster(float elapsedTime)
{
	this->FireIntelligence();

	if (fireCoordinates.empty())
	{
		this->disasterEnd = true;
	}

	this->counterLife++;
	if (this->counterLife > this->disasterLifetime/5)
	{
		if (fireCoordinates.empty())
		{
			this->disasterEnd = true;
			return;
		}

		this->burnedArea = this->fireCoordinates.back();

		assert(!fireCoordinates.empty());
		fireCoordinates.front() = std::move(fireCoordinates.back());
		fireCoordinates.pop_back();

		assert(!spriteVectorFire.empty());
		spriteVectorFire.front() = std::move(spriteVectorFire.back());
		spriteVectorFire.pop_back();

		this->counterLife = 0;
		this->fireLoops++;
	}

	if (fireLoops > 6)
	{
		this->disasterEnd = true;
	}
}

void Fire::FireIntelligence()
{
	this->movementCounter++;

	if (this->movementCounter >= 50)
	{
		sf::Vector2i tmpPosition;
		tmpPosition = sf::Vector2i(this->randomEngine.RandomiseEvent(-2, 2), this->randomEngine.RandomiseEvent(-2, 2));

		std::vector<sf::Vector2i>::iterator it = std::find(this->fireCoordinates.begin(), this->fireCoordinates.end(), tmpPosition + this->fireCoordinates.back());

		if (it == this->fireCoordinates.end())
		{
			this->fireCoordinates.push_back(this->fireCoordinates.back() +
				sf::Vector2i(this->randomEngine.RandomiseEvent(-2, 2), this->randomEngine.RandomiseEvent(-2, 2)));
			this->movementCounter = 0;

			if (this->fireCoordinates.back().x > this->sizeMap -1 || this->fireCoordinates.back().y > this->sizeMap -1  ||
				this->fireCoordinates.back().x < 0 || this->fireCoordinates.back().y < 0)
			{
				this->fireCoordinates.pop_back();
				return;
			}

			this->ChangeFirePosition(this->fireCoordinates.back());

			std::cout << fireCoordinates.back().x << " " << fireCoordinates.back().y << std::endl;

			this->spriteVectorFire.push_back(this->sprite);
		}
	}
}

void Fire::ChangeFirePosition(sf::Vector2i firePosition)
{
	sf::Vector2f position;

	position.x = (firePosition.y - firePosition.x) * TILE_SIZE + this->sizeMap * TILE_SIZE;
	position.y = (firePosition.y + firePosition.x) * TILE_SIZE * 0.5f;

	this->SetSpritePosition(position);
}

void Fire::InitializeFire(int positionX, int positionY)
{
	this->fireCoordinates.push_back(sf::Vector2i(positionX,positionY));
	this->fireHeart = sf::Vector2i(positionX, positionY);
	this->ChangeFirePosition(sf::Vector2i(positionX, positionY));
	
	this->spriteVectorFire.push_back(this->sprite);
	//this->spriteVectorFire.push_back()
}

void Fire::FireBrigadeEvent(sf::Vector2i extinguishedArea)
{
	std::vector<sf::Vector2i>::iterator removeFire = std::find(fireCoordinates.begin(), fireCoordinates.end(), extinguishedArea);
	int iterator = 0;
	for (std::vector<sf::Vector2i>::iterator removeFire = this->fireCoordinates.begin();
		removeFire != fireCoordinates.end(); removeFire++, iterator++)
	{
		if (fireCoordinates[iterator] == extinguishedArea)
		{
			fireCoordinates.erase(removeFire);

			this->spriteVectorFire.erase(this->spriteVectorFire.begin() + iterator);
			break;
		}
	}
}

void Fire::Draw(sf::RenderWindow& window, float elapsedTime,
	sf::Shader *shader, const sf::Vector2f & camera_position)
{
	this->UpdateAnimation(elapsedTime);

	for (auto & it : this->spriteVectorFire)
	{
		it.setTextureRect(currentSection);
		window.draw(it);
	}
}

#pragma endregion

#pragma region Getters

std::vector<sf::Vector2i> Fire::GetFireVectorCoordinates() const
{
	return this->fireCoordinates;
}

std::vector<sf::Sprite> Fire::GetFireSpritesVector() const
{
	return this->spriteVectorFire;
}

sf::Vector2i Fire::GetReturnedBurnedArea() const
{
	return this->burnedArea;
}

sf::Vector2i Fire::GetFireHearth() const
{
	return this->fireHeart;
}

#pragma endregion