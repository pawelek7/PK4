#ifndef MapTile_hpp
#define MapTile_hpp

#include <SFML/Graphics.hpp>

#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>

#include "defines.h"
#include "LoadData.h"
#include "MapGenerator.h"
#include "SeedGenerator.h"
#include "VectorManager.h"
#include "Tornado.h"
#include "Fire.h"
#include "PoliceStation.h"
#include "FireBrigade.h"

/*
Class responsible for magaging map.

@author
Pawel Salicki
*/

class MapTile : public LoadData
{
	friend class HoldGameplay; //friendship with HoldGameplay class

	VectorManager<std::unique_ptr<SmallTile>> tilesVector; //vector of tiles
	std::vector<char> selectedTiles; //selected tiels

	MapGenerator *mapGenerator = nullptr;
//	LoadData *loadData = nullptr;
	PathFinding *pathRoad = nullptr, *pathVoltagePylons = nullptr;

	int fromX = 0; //selection range
	int toX = 0;
	int fromY = 0;
	int toY = 0;
	int dravingDistance = 20; //drawing distance
	int timeSpeed = 50; //time speed

	unsigned int sizeOfMap = 0; //size of map
	unsigned int nrSelected = 0; //amount of selected tiles
	std::string cityName = "unknown"; //city name

	int i = 0; //iterator for cursor
	bool prevCurFromTwo = false; //prevent from drawing cursor on two tiles

	sf::Shader core_shader; //shader
	sf::Vector2f camera_position; //camera postion
	sf::Sprite cursorSmall, cursorBig; //cursor sprites

	void CorrectTheNeighboringOnes(int i, int j); //correct neighbourhooding tiles
	void InitialiseMapEnvironment(); //initialize map

public:
	MapTile() = default;
	MapTile(const std::string & filename, std::shared_ptr<AssetsOfGame> ptrGame, unsigned int sizeOfMap, uint64_t seedMap);
	MapTile(const std::string & filename, std::shared_ptr<AssetsOfGame> ptrGame);
	virtual ~MapTile();

	void CreateNewMap(const std::string & filename, unsigned int sizeOfMap, uint64_t seedMap); //create new map
	void DrawMap(sf::RenderWindow *window, float elapsedTime, 
		const std::vector<Structure*> & structures, const std::vector<Tornado*> & tornados,
		const std::vector<Fire*> & fires); //draw tiles
	void UpdateTile(int i, int j); //update tile coordinates

	void SelectTiles(sf::Vector2i from, sf::Vector2i to, SmallTile::TypeOfTile typeOfTile); //tiles selection
	void DeleteSelection(); //delete selection tiles

	void InitializeShaders(); //initialize shaders

	//change tile or structure
	void ChangeTile(SmallTile::TileSpecialise tileSpecialise, IDvector<Structure*>&, std::vector<ID> & structuresToRemove,
		std::vector<House*> & houseVector, std::vector<Shop*> & shopVector, std::vector<Factory*> & factoryVector,
		std::vector<Hospital*> & hospitalVector, std::vector<PowerHouse*> & powerHouseVector, std::vector<PoliceStation*> & policeStationVector,
		std::vector<FireBrigade*> & fireBrigadeVector, std::vector<HighVoltageLines*> & highVoltageLinesVector,
		IDvector<RequireConnecting*> & IDconnectings, std::vector<ID> & connectionsToRemove);

	//change 2x2 structure
	void ChangeSpecialTile(SmallTile::TileSpecialise tileSpecialise, IDvector<Structure*>&, std::vector<ID> & structuresToRemove, 
		std::vector<HighVoltageLines*> & highVoltageLinesVector, std::vector<PowerHouse*> & powerHouseVector, 
		IDvector<RequireConnecting*> & IDconnectings);
	std::unique_ptr<SmallTile> CreateTile(SmallTile::TileSpecialise tileSpecialise);

	//rptate or move up map
	void RotateMap();
	void MoveDownMap();
	void MoveUpMap();

	void SaveMap(); //save map and structures

	//load map and structures
	void LoadMap(const std::string & fileName, IDvector<Structure*> & structuresWithID,
		std::vector<House*> & houseVector, std::vector<Shop*> & shopVector, std::vector<Factory*> & factoryVector,
		std::vector<Hospital*> & hospitalVector, std::vector<PowerHouse*> & powerHouseVector, std::vector<PoliceStation*> & policeStationVector,
		std::vector<FireBrigade*> & fireBrigadeVector, std::vector<HighVoltageLines*> & highVoltageLinesVector,
		IDvector<RequireConnecting*> & IDconnectings);
	void RememberAnotherFile(); //remember save files

	//setters
	void SetCameraPosition(sf::Vector2f cameraPosition);
	void SetDravingDistance(int distance);
	void SetTimeFromGameplay(int timeSpeed);

	//getters
	PathFinding *GetPathVoltagePylons();
	PathFinding *GetPathRoads();

	VectorManager<std::unique_ptr<SmallTile>>& GetSmallTile();
	std::vector<char> GetSelectedTiles() const;

	unsigned int GetNrSelectedTiles() const;
	int GetSizeOfMap() const;
};

#endif // !MapTile_hpp