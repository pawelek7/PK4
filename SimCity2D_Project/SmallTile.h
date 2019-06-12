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


class SmallTile : public AnimationSprite
{
public:
	enum class TypeOfTile
	{
		VOID = 0, DIRT = 1, WATER = 2, STRUCTURE = 3, REQUIRES_CONNECTION = 4, OBSTACLE = 5
	};

	enum class TileSpecialise
	{
		VOID = 0, FLOOR = 1, WATER = 2, HOUSE = 3, FACTORY = 4, SHOP = 5, ROAD = 6, HIGH_VOLTAGE_LINES = 7,
		POWER_HOUSE = 8, ROCK = 9, TREE = 10, SPECTRUM_PLATE = 11, HOSPITAL = 12, RUINS = 13, FIRE_BRIGADE = 14,
		POLICE_STATION = 15, TREE_2 = 16, STATUE = 17
	};

	enum class SelectionProcess
	{
		VOID = 0, SELECTED = 1, ERROR = 2
	};

private:
	int height = 0;
	int tileVariant = 0;

protected:
	TypeOfTile typeOfTile = TypeOfTile::VOID;
	SelectionProcess selectionProcess = SelectionProcess::VOID;
	TileSpecialise tileSpecialise = TileSpecialise::VOID;

	sf::Vector2i position = sf::Vector2i(0, 0);
	sf::Texture texture;

	bool isAnimation = false;
	std::string textureName = "unknown";

public:
	SmallTile() = default;
	SmallTile(const unsigned int height, const
		sf::Texture & texture, const TypeOfTile typeOfTile, const TileSpecialise tileSpecialise, const std::vector<Frames> & frames);
	virtual ~SmallTile() = default;

	virtual std::unique_ptr<SmallTile> clone() const;

	void Draw(sf::RenderWindow& window, float elapsedTime, sf::Shader *shader = nullptr, const sf::Vector2f & camera_position = sf::Vector2f(0,0));
	void UpdateHeight(int height);
	virtual void UpdateInformation();

	virtual void SetNewTileVariant(const SmallTile* neighbourhood[NEIGHBORING][NEIGHBORING]);
	void SetSelectionProcess(SelectionProcess selectionProecess);

	virtual bool Interaction(const sf::Vector2f & position);
	bool SpriteClicked(const sf::Sprite & sprite, const sf::Vector2f & position);

	static TileSpecialise SetStringToTileSpecialise(const std::string & tileSpecialise);
	static std::string SetTileSpecialiseToString(TileSpecialise tileSpecialise);
	void InitializeSmallTileParameters(int height, int tileVariant, TypeOfTile typeOfTile, TileSpecialise tileSpecialise,
		bool isAnimation, const std::string & textureName);

	//setters
	void SetPosition(int x, int y);

	//getters
	SelectionProcess GetSelectionProcess() const;
	TypeOfTile GetTypeOfTile() const;
	TileSpecialise GetTileSpecialise() const;

	bool GetIsBuilding() const;
	bool GetIsRoad() const;
	bool GetIsVoltagePylon() const;
	bool GetIsPowerHouse() const;
	bool GetIsRuins() const;
	bool GetIsTrees() const;
	bool GetIsWater() const;
	bool GetIsFactory() const;
	bool GetIsShops() const;
	bool GetIsAnimation() const;
	bool GetIsHouse() const;
	bool GetIsHospital() const;
	bool GetIsFireBrigade() const;
	bool GetIsPoliceStation() const;
	bool GetIsTressWithGrass() const;
	bool GetIsStatue() const;

	int GetHeight() const;
	int GetTileVariant() const;

	std::string GetTextureName();

	sf::Sprite GetSprite() const;
	sf::Vector2i GetPosition() const;
	sf::Vector2f GetSpritePosition() const;
	sf::Vector2f GetFixedPosition();
};

#endif // !SmallTile_hpp