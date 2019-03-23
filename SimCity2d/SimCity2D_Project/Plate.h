#ifndef Plate_hpp
#define Plate_hpp

#include <SFML/Graphics.hpp> //SFML library

#include <vector>

enum class TypeOfTile
{NOTHING = 0, DIRT = 1, HOUSES = 2, SHOPS = 3, FACTORY = 4, CROSS = 5};

//std::string tileTypeToStr(TypeOfTile type);

class Plate
{
	friend class MapTile;
	friend class CreateMap;

public:
	unsigned short _tileVersion = 0;
	unsigned int value = 0;
	unsigned int population = 0;
	unsigned int popToUpgrade = 0;
	unsigned short maxLevelUpgrade = 0;
	TypeOfTile _typeOfTile = TypeOfTile::NOTHING;
	sf::Sprite _sprite;

public:
	Plate() = default;
	Plate(int x, int y, sf::Texture & texture, const TypeOfTile _typeOfTile, unsigned int value, unsigned int popToUpgrade, unsigned short maxLevelUpgrade);

	void Draw(sf::RenderWindow& window, float dt);
	void Update() {}

	int getCost() { return value; }

	TypeOfTile GetTypeOfTile() const;
	sf::Sprite GetSprite() const;

	std::string tileTypeToStr(TypeOfTile type)
	{
		switch (type)
		{
		default:
		case TypeOfTile::NOTHING:				return "Void";
		case TypeOfTile::DIRT:				return "Flatten";
		case TypeOfTile::HOUSES:				return "Forest";
		case TypeOfTile::SHOPS:				return "Water";
		case TypeOfTile::FACTORY:			return "Residential Zone";
		case TypeOfTile::CROSS:			return "Commercial Zone";
		}
	}

	//std::string tileTypeToStr(TypeOfTile type);
};

#endif // !Plate_hpp