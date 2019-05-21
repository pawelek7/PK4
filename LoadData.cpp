#include "LoadData.h"

#pragma region Constructors

LoadData::LoadData(std::shared_ptr<AssetsOfGame> ptrGame)
	:ptrGame(ptrGame)
{
	this->LoadTextures();
	this->LoadAtlas();
}

#pragma endregion

#pragma region Class_Methods

void LoadData::LoadTextures()
{
	this->ptrGame->textureManager.LoadAsset("dirt", "Resources/Textures/dirt.png");
	this->ptrGame->textureManager.LoadAsset("dirt_blue", "Resources/Textures/dirt_blue.png");
	this->ptrGame->textureManager.LoadAsset("dirt_green", "Resources/Textures/dirt_green.png");
	this->ptrGame->textureManager.LoadAsset("dirt_red", "Resources/Textures/dirt_red.png");
	this->ptrGame->textureManager.LoadAsset("dirt_yellow", "Resources/Textures/dirt_yellow.png");
	this->ptrGame->textureManager.LoadAsset("water", "Resources/Textures/water.png");
	this->ptrGame->textureManager.LoadAsset("cross", "Resources/Textures/cross.png");
	this->ptrGame->textureManager.LoadAsset("roads", "Resources/Textures/roads.png");
	this->ptrGame->textureManager.LoadAsset("high_voltage_lines", "Resources/Textures/high_voltage_lines.png");
	this->ptrGame->textureManager.LoadAsset("rock", "Resources/Textures/rock.png");
	this->ptrGame->textureManager.LoadAsset("tree", "Resources/Textures/tree.png");
	this->ptrGame->textureManager.LoadAsset("power_station", "Resources/Textures/power_station.png");
	this->ptrGame->textureManager.LoadAsset("spectrum_plate", "Resources/Textures/spectrum_plate.png");
	this->ptrGame->textureManager.LoadAsset("hospital", "Resources/Textures/hospital.png");
	this->ptrGame->textureManager.LoadAsset("ruins", "Resources/Textures/ruins.png");
	this->ptrGame->textureManager.LoadAsset("fire_station", "Resources/Textures/fire_station.png");
}

void LoadData::LoadAtlas()
{
	std::vector<Frames> tmp;
	Frames staticAnim(0, 0, 1.0f);
	tmp.push_back({ staticAnim });

	Frames waterAnim1(0, 2, 1.0f);

	std::vector<Frames> waterAnimation;
	waterAnimation.push_back({ waterAnim1 });

	this->tilesMap.emplace_back(std::make_unique<SmallTile>(1, this->ptrGame->textureManager.GetAsset("cross"), TypeOfTile::VOID, TileSpecialise::VOID, tmp)); //VOID = 0
	this->tilesMap.emplace_back(std::make_unique<SmallTile>(1, this->ptrGame->textureManager.GetAsset("dirt"), TypeOfTile::DIRT, TileSpecialise::FLOOR, tmp)); //FLOOR = 1
	this->tilesMap.emplace_back(std::make_unique<SmallTile>(1, this->ptrGame->textureManager.GetAsset("water"), TypeOfTile::WATER, TileSpecialise::WATER, waterAnimation)); //WATER = 2
	this->tilesMap.emplace_back(std::make_unique<House>(1, this->ptrGame->textureManager.GetAsset("dirt_green"), TileSpecialise::HOUSE, tmp, 0)); //HOUSE = 3
	this->tilesMap.emplace_back(std::make_unique<Factory>(1, this->ptrGame->textureManager.GetAsset("dirt_yellow"), TileSpecialise::FACTORY, tmp)); //FACTORY = 4
	this->tilesMap.emplace_back(std::make_unique<Shop>(1, this->ptrGame->textureManager.GetAsset("dirt_blue"), TileSpecialise::SHOP, tmp)); //SHOP = 5
	this->tilesMap.emplace_back(std::make_unique<Road>(this->ptrGame->textureManager.GetAsset("roads"), TileSpecialise::ROAD, tmp, 1)); // ROAD = 6
	this->tilesMap.emplace_back(std::make_unique<HighVoltageLines>(this->ptrGame->textureManager.GetAsset("high_voltage_lines"), TileSpecialise::HIGH_VOLTAGE_LINES, tmp, 2)); // HIGH_VOLTAGE_LINES = 7
	this->tilesMap.emplace_back(std::make_unique<PowerHouse>(3, this->ptrGame->textureManager.GetAsset("power_station"), tmp)); // POWER_HOUSE = 8
	this->tilesMap.emplace_back(std::make_unique<SmallTile>(2, this->ptrGame->textureManager.GetAsset("rock"), TypeOfTile::OBSTACLE, TileSpecialise::ROCK, tmp)); // ROCK = 9
	this->tilesMap.emplace_back(std::make_unique<SmallTile>(2, this->ptrGame->textureManager.GetAsset("tree"), TypeOfTile::OBSTACLE, TileSpecialise::TREE, tmp)); // TREE = 10
	this->tilesMap.emplace_back(std::make_unique<SmallTile>(2, this->ptrGame->textureManager.GetAsset("spectrum_plate"), TypeOfTile::OBSTACLE, TileSpecialise::SPECTRUM_PLATE, tmp)); // SPECTRUM_PLATE = 11
	this->tilesMap.emplace_back(std::make_unique<Hospital>(1, this->ptrGame->textureManager.GetAsset("hospital"), TileSpecialise::HOSPITAL, tmp)); // HOSPITAL = 12
	this->tilesMap.emplace_back(std::make_unique<SmallTile>(1, this->ptrGame->textureManager.GetAsset("ruins"), TypeOfTile::OBSTACLE, TileSpecialise::RUINS, tmp)); // RUINS = 13
	this->tilesMap.emplace_back(std::make_unique<FireBrigade>(1, this->ptrGame->textureManager.GetAsset("fire_station"), TileSpecialise::FIRE_BRIGADE, tmp)); // FIRE_BRIGADE = 14
}

#pragma endregion