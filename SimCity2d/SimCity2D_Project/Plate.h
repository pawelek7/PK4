#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

enum class TypeOfTile
{NOTHING = 0, DIRT = 1, HOUSES = 2, SHOPS = 3, FACTORY = 4, CROSS = 5};

class Plate
{
	friend class MapTile;

private:
	unsigned short _tileVersion = 0;
	unsigned int value = 0;
	unsigned int population = 0;
	unsigned int popToUpgrade = 0;
	unsigned short maxLevelUpgrade = 0;
	
	sf::Sprite _sprite;

public:
	Plate() = default;
	Plate(int x, int y, sf::Texture & texture, const TypeOfTile _typeOfTile, unsigned int value, unsigned int popToUpgrade, unsigned short maxLevelUpgrade);

	void Draw(sf::RenderWindow& window, float dt);
	void Update();

	TypeOfTile GetTypeOfTile() const;
	sf::Sprite GetSprite() const;


	TypeOfTile _typeOfTile = TypeOfTile::NOTHING;
};