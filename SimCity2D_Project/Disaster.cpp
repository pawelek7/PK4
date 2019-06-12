#include "Disaster.h"

#pragma region Constructors

#pragma region Description of the method

/*
Multiparameter constructor setting basic values.

method parameters:
____________________
texture - disaster texture
frames - vector holding animation frames (Frames class)
disasterType - type of disaster

the return value:
____________________
no return value

@author
Pawel Salicki
*/

#pragma endregion

Disaster::Disaster(const sf::Texture & texture, const std::vector<Frames> & frames, DisasterType disasterType)
	:AnimationSprite(frames)
{
	this->sprite.setTexture(texture); //set sprite texture
	this->disasterType = disasterType;

	if (disasterType == DisasterType::TORNADO) //adjust the size of the animation to the appropriate phenomenon
	{
		this->frameSize = sf::IntRect(0, 0, TILE_SIZE * 2, TILE_SIZE * 3);
		this->sprite.setOrigin(sf::Vector2f(0.0f, TILE_SIZE * 2));
	}
	else if (disasterType == DisasterType::FIRE)
	{
		this->frameSize = sf::IntRect(0, 0, TILE_SIZE * 2, TILE_SIZE * 2);
		this->sprite.setOrigin(sf::Vector2f(0.0f, TILE_SIZE));
	}

	this->ChangeFrame(0); //initiate the animation
	this->UpdateAnimation(0.0f);
}

#pragma endregion

#pragma region Class_Methods

#pragma region Description of the method

/*
The function responsible for drawing animation frames on the screen.

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

void Disaster::Draw(sf::RenderWindow & window, const float elapsedTime,
	sf::Shader *shader, const sf::Vector2f & camera_position)
{
	this->UpdateAnimation(elapsedTime); //update animation
	this->sprite.setTextureRect(this->currentSection); //set the appropriate animation frame

	window.draw(this->sprite); //draw sprite on window
}

#pragma endregion

#pragma region Setters
//setters

void Disaster::SetSizeMapInformation(int sizeMap)
{
	this->sizeMap = sizeMap;
}

#pragma endregion

#pragma region Getters
//getters

bool Disaster::GetIsDisasterActive() const
{
	return this->disasterActive;
}

bool Disaster::GetIsDisasterEnd() const
{
	return this->disasterEnd;
}

#pragma endregion