#include "Disaster.h"

#pragma region Constructors

Disaster::Disaster(const sf::Texture & texture, const std::vector<Frames> & frames, DisasterType disasterType)
	:AnimationSprite(frames)
{
	this->sprite.setTexture(texture);
	this->disasterType = disasterType;

	if (disasterType == DisasterType::TORNADO)
	{
		this->frameSize = sf::IntRect(0, 0, TILE_SIZE * 2, TILE_SIZE * 3);
		this->sprite.setOrigin(sf::Vector2f(0.0f, TILE_SIZE*2));
	}
	else if (disasterType == DisasterType::FIRE)
	{
		this->frameSize = sf::IntRect(0, 0, TILE_SIZE * 2, TILE_SIZE * 2);
		this->sprite.setOrigin(sf::Vector2f(0.0f, TILE_SIZE*1));
	}

	this->ChangeFrame(0);
	this->UpdateAnimation(0.0f);
}

#pragma endregion

#pragma region Class_Methods

void Disaster::Draw(sf::RenderWindow& window, float elapsedTime,
	sf::Shader *shader , const sf::Vector2f & camera_position )
{
	this->UpdateAnimation(elapsedTime);
	this->sprite.setTextureRect(currentSection);

	window.draw(this->sprite);
}

#pragma endregion

#pragma region Setters

void Disaster::SetSizeMapInformation(int sizeMap)
{
	this->sizeMap = sizeMap;
}

#pragma endregion

#pragma region Getters

bool Disaster::GetIsDisasterActive() const
{
	return this->disasterActive;
}

bool Disaster::GetIsDisasterEnd() const
{
	return this->disasterEnd;
}

#pragma endregion