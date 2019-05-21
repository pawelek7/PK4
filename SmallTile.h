#ifndef SmallTile_hpp
#define SmallTile_hpp

#include <SFML/Graphics.hpp>

#include <vector>
#include <map>
#include <iostream>

#include "defines.h"
#include "IDvector.h"
#include "AnimationSprite.h"
#include "AssetManager.h"


enum class TypeOfTile
{
	VOID = 0, DIRT = 1, WATER = 2, STRUCTURE = 3, REQUIRES_CONNECTION = 4, OBSTACLE = 5
};

enum class TileSpecialise
{
	VOID = 0, FLOOR = 1, WATER = 2, HOUSE = 3, FACTORY = 4, SHOP = 5, ROAD = 6, HIGH_VOLTAGE_LINES = 7,
	POWER_HOUSE = 8, ROCK = 9, TREE = 10, SPECTRUM_PLATE = 11, HOSPITAL = 12, RUINS = 13, FIRE_BRIGADE = 14,
	POLICE_STATION = 15
};

enum class SelectionProcess
{
	VOID = 0, SELECTED = 1, ERROR = 2
};

struct TileData
{
	TileSpecialise tileSpecialise;
	int population;
	int level;
	int height;
	std::string texture_name;
	ID buildingID;
};

class SmallTile : public AnimationSprite
{
	int height = 0;
	int tileVariant = 0;

	std::string textureName;

protected:
	TileData tileData;
	TypeOfTile typeOfTile = TypeOfTile::VOID;
	SelectionProcess selectionProcess = SelectionProcess::VOID;
	TileSpecialise tileSpecialise = TileSpecialise::VOID;

	sf::Vector2i position = sf::Vector2i(0, 0);
	sf::Texture texture;

	const sf::Image *image = nullptr;

	bool isAnimation = false;

public:
	SmallTile(const unsigned int height, const
		sf::Texture & texture, const TypeOfTile typeOfTile, const TileSpecialise tileSpecialise, const std::vector<Frames> & frames);
	virtual ~SmallTile();

	virtual std::unique_ptr<SmallTile> clone() const;

	void Draw(sf::RenderWindow& window, float elapsedTime, sf::Shader *shader = nullptr, const sf::Vector2f & camera_position = sf::Vector2f(0,0));
	void UpdateHeight(int height);
	virtual void UpdateInformation();

	virtual void SetNewTileVariant(const SmallTile* neighbourhood[NEIGHBORING][NEIGHBORING]);
	void SetSelectionProcess(SelectionProcess selectionProecess);

	virtual bool Interaction(const sf::Vector2f & position);
	bool SpriteClicked(const sf::Sprite & sprite, const sf::Image & image, const sf::Vector2f & position);

	static TileSpecialise SetStringToTileSpecialise(const std::string & tileSpecialise);
	static std::string SetTileSpecialiseToString(TileSpecialise tileSpecialise);

	void SetTileData(TileData tileData);
	void SetPosition(int x, int y);

	SelectionProcess GetSelectionProcess() const;
	TypeOfTile GetTypeOfTile() const;
	TileSpecialise GetTileSpecialise() const;
	TileData GetTileData() const;

	bool GetIsBuilding() const;
	bool GetIsRoad() const;
	bool GetIsVoltagePylon() const;
	bool GetIsPowerHouse() const;
	bool GetIsRuins() const;
	bool GetIsTrees() const;
	bool GetIsWater() const;
	bool GetIsFactory() const;
	bool GetIsShops() const;

	sf::Sprite GetSprite() const;
	sf::Vector2i GetPosition() const;
	sf::Vector2f GetSpritePosition() const;
	sf::Vector2f GetFixedPosition();
};

#endif // !SmallTile_hpp