#include "Plate.h"

Plate::Plate(int x, int y, sf::Texture & texture, const TypeOfTile _typeOfTile, unsigned int value, unsigned int popToUpgrade, unsigned short maxLevelUpgrade)
	: _typeOfTile(_typeOfTile), value(value), popToUpgrade(popToUpgrade), maxLevelUpgrade(maxLevelUpgrade)
{
	this->_sprite.setTexture(texture);
}

void Plate::Draw(sf::RenderWindow& window, float dt)
{
	window.draw(this->_sprite);
}

TypeOfTile Plate::GetTypeOfTile() const
{
	return this->_typeOfTile;
}

sf::Sprite Plate::GetSprite() const
{
	return this->_sprite;
}
