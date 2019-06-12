#include "Fire.h"

#pragma region Constructors

#pragma region Description of the method
/*
Multiparameter constructor setting basic values.
This constructor calls the constructor of the Disaster base class.

method parameters:
____________________
texture - disaster texture
frames - vector holding animation frames (Frames class)

the return value:
____________________
no return value

@author
Pawel Salicki
*/

#pragma endregion

Fire::Fire(const sf::Texture & texture, const std::vector<Frames> & frames)
	:Disaster(texture, frames, DisasterType::FIRE)
{
	//nothing
}

#pragma endregion

#pragma region Class_Methods

#pragma region Description of the method
/*
A method that supports the spread of fire on the map and make sure
that it does not go beyond the map border.

method parameters:
____________________
elaspedTime - number indicating the animation time

the return value:
____________________
no return value

@author
Pawel Salicki
*/

#pragma endregion

void Fire::UpdateDisaster(const float elapsedTime)
{
	this->FireIntelligence(); //function that maps fire behavior

	if (this->fireCoordinates.empty()) //if the flame container is empty, notify the end of the disaster
	{
		this->disasterEnd = true;
	}

	this->counterLife++;
	if (this->counterLife > this->disasterLifetime / 5) //this instruction block clears 
														//the oldest flame from containers 
														//after a specified time
	{
		if (this->fireCoordinates.empty()) //if vector of fire is empty call delete variable
		{
			this->disasterEnd = true;
			return;
		}

		this->burnedArea = this->fireCoordinates.back(); //delete the oldest fire

		assert(!this->fireCoordinates.empty());
		this->fireCoordinates.front() = std::move(this->fireCoordinates.back());
		this->fireCoordinates.pop_back();

		assert(!this->spriteVectorFire.empty());
		this->spriteVectorFire.front() = std::move(this->spriteVectorFire.back());
		this->spriteVectorFire.pop_back();

		this->counterLife = 0;
		this->fireLoops++;
	}

	if (this->fireLoops > MAX_FLAMES)
	{
		this->disasterEnd = true;
	}
}

#pragma region Description of the method
/*
A method that supports the movement of fire on the map.

method parameters:
____________________
no parameters

the return value:
____________________
no return value

@author
Pawel Salicki
*/

#pragma endregion

void Fire::FireIntelligence()
{
	this->movementCounter++;

	if (this->movementCounter >= MOVEMENT_FIRE)
	{
		sf::Vector2i tmpPosition; //random next fire position on the map
		tmpPosition = sf::Vector2i(this->randomEngine.RandomiseEvent(POSITION_FROM, POSITION_TO), this->randomEngine.RandomiseEvent(POSITION_FROM, POSITION_TO));

		std::vector<sf::Vector2i>::iterator it = std::find(this->fireCoordinates.begin(), this->fireCoordinates.end(), tmpPosition + this->fireCoordinates.back());

		//if the given fire does not exist on the given position on the map, create a new one for this position
		if (it == this->fireCoordinates.end())
		{
			this->fireCoordinates.push_back(this->fireCoordinates.back() +
				sf::Vector2i(this->randomEngine.RandomiseEvent(POSITION_FROM, POSITION_TO), this->randomEngine.RandomiseEvent(POSITION_FROM, POSITION_TO)));
			this->movementCounter = 0;

			if (this->fireCoordinates.back().x > this->sizeMap - 1 || this->fireCoordinates.back().y > this->sizeMap - 1 ||
				this->fireCoordinates.back().x < 0 || this->fireCoordinates.back().y < 0)
			{
				this->fireCoordinates.pop_back();
				return;
			}

			this->ChangeFirePosition(this->fireCoordinates.back());

			this->spriteVectorFire.push_back(this->sprite);
		}
	}
}

#pragma region Description of the method
/*
The method changes the position of the fire on the map.

method parameters:
____________________
firePosition - coordinates of fire

the return value:
____________________
no return value

@author
Pawel Salicki
*/

#pragma endregion

void Fire::ChangeFirePosition(sf::Vector2i firePosition)
{
	sf::Vector2f position;

	//calculate the position of the fire depending on the size of the map
	position.x = (firePosition.y - firePosition.x) * TILE_SIZE + this->sizeMap * TILE_SIZE;
	position.y = (firePosition.y + firePosition.x) * TILE_SIZE * 0.5f;

	this->SetSpritePosition(position); //set new sprite position
}

#pragma region Description of the method
/*
The method initiates fire at the given position.
Sets the heart of the fire and initiates the spread.

method parameters:
____________________
positionX - x position fire
positionY - y positon fire

the return value:
____________________
no return value

@author
Pawel Salicki
*/

#pragma endregion

void Fire::InitializeFire(int positionX, int positionY)
{
	this->fireCoordinates.push_back(sf::Vector2i(positionX, positionY)); //set coordinates
	this->fireHeart = sf::Vector2i(positionX, positionY);
	this->ChangeFirePosition(sf::Vector2i(positionX, positionY));

	this->spriteVectorFire.push_back(this->sprite);
}

#pragma region Description of the method
/*
A method that deletes fire on specyfic coordinates.

method parameters:
____________________
extinguishedArea - coordinates where the fire was extinguished

the return value:
____________________
no return value

@author
Pawel Salicki
*/

#pragma endregion

void Fire::FireBrigadeEvent(sf::Vector2i extinguishedArea)
{
	if (extinguishedArea == this->fireHeart) //if heart of fire is destroyed, call delete whole fire
	{
		this->fireCoordinates.clear();
		this->spriteVectorFire.clear();
		this->disasterEnd = true;
	}
	else
	{
		//check if the coordinate data in the container exists
		std::vector<sf::Vector2i>::iterator removeFire = std::find(this->fireCoordinates.begin(), this->fireCoordinates.end(), extinguishedArea);

		int iterator = 0;

		//remove the fire from the container
		for (std::vector<sf::Vector2i>::iterator removeFire = this->fireCoordinates.begin();
			removeFire != this->fireCoordinates.end(); removeFire++, iterator++)
		{
			if (this->fireCoordinates[iterator] == extinguishedArea) //remove extinguished fire
			{
				this->fireCoordinates.erase(removeFire);

				this->spriteVectorFire.erase(this->spriteVectorFire.begin() + iterator);
				break;
			}
		}
	}
}


#pragma region Description of the method
/*
A method that supports drawing fire on the system window

method parameters:
____________________
window - object of the SFML library class that supports the system window
elapsedTime - a number that specifies the time between the frames of the animation
shader - an SFML library object responsible for handling shaders
camera_position - coordinates of game's camera

the return value:
____________________
no return value

@author
Pawel Salicki
*/

#pragma endregion

void Fire::Draw(sf::RenderWindow& window, float elapsedTime,
	sf::Shader *shader, const sf::Vector2f & camera_position)
{
	this->UpdateAnimation(elapsedTime); //update animation depending on elapsed time

	for (auto & it : this->spriteVectorFire) //draw all fires from container
	{
		it.setTextureRect(this->currentSection);
		window.draw(it);
	}
}

#pragma endregion

#pragma region Getters
//getters

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