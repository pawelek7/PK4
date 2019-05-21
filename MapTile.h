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

class MapTile : public LoadData
{
	friend class HoldGameplay;

	VectorManager<std::unique_ptr<SmallTile>> tilesVector;
	std::vector<char> selectedTiles;

	MapGenerator *mapGenerator = nullptr;
	LoadData *loadData = nullptr;
	PathFinding *pathRoad = nullptr, *pathVoltagePylons = nullptr;

	int fromX = 0;
	int toX = 0;
	int fromY = 0;
	int toY = 0;
	int dravingDistance = 20;
	int timeSpeed = 50;

	unsigned int sizeOfMap = 0;
	unsigned int nrSelected = 0;
	std::string cityName = "unknown";

	int i = 0;
	bool prevCurFromTwo = false;

	sf::Shader core_shader;
	sf::Vector2f camera_position;
	sf::Sprite cursorSmall, cursorBig;

	void CorrectTheNeighboringOnes(int i, int j);
	void InitialiseMapEnvironment();

public:
	MapTile() = default;
	MapTile(const std::string & filename, std::shared_ptr<AssetsOfGame> ptrGame, unsigned int sizeOfMap, uint64_t seedMap);
	MapTile(const std::string & filename, std::shared_ptr<AssetsOfGame> ptrGame);

	void CreateNewMap(const std::string & filename, unsigned int sizeOfMap, uint64_t seedMap);
	void DrawMap(sf::RenderWindow *window, float elapsedTime, 
		const std::vector<Structure*> & structures, const std::vector<Tornado*> & tornados,
		const std::vector<Fire*> & fires);
	void UpdateTile(int i, int j);


	void SelectTiles(sf::Vector2i from, sf::Vector2i to, TypeOfTile typeOfTile);
	void DeleteSelection();

	void InitializeShaders();
	void ChangeTile(TileSpecialise tileSpecialise, IDvector<Structure*>&, std::vector<ID> & structuresToRemove,
		std::vector<House*> & houseVector, std::vector<Shop*> & shopVector, std::vector<Factory*> & factoryVector,
		std::vector<Hospital*> & hospitalVector, std::vector<PowerHouse*> & powerHouseVector, std::vector<PoliceStation*> & policeStationVector,
		std::vector<FireBrigade*> & fireBrigadeVector, std::vector<HighVoltageLines*> & highVoltageLinesVector,
		IDvector<RequireConnecting*> & IDconnectings, std::vector<ID> & connectionsToRemove);
	void ChangeSpecialTile(TileSpecialise tileSpecialise, IDvector<Structure*>&, std::vector<ID> & structuresToRemove, 
		std::vector<HighVoltageLines*> & highVoltageLinesVector, std::vector<PowerHouse*> & powerHouseVector, 
		IDvector<RequireConnecting*> & IDconnectings);
	std::unique_ptr<SmallTile> CreateTile(TileSpecialise tileSpecialise);

	void RotateMap();
	void MoveUpMap();

	void SaveMap();
	void LoadMap(const std::string & fileName);
	void RememberAnotherFile();

	void SetCameraPosition(sf::Vector2f cameraPosition);
	void SetDravingDistance(int distance);
	void SetTimeFromGameplay(int timeSpeed);

	PathFinding *GetPathVoltagePylons();
	PathFinding *GetPathRoads();

	VectorManager<std::unique_ptr<SmallTile>>& GetSmallTile();
	std::vector<char> GetSelectedTiles() const;

	unsigned int GetNrSelectedTiles() const;
	int GetSizeOfMap() const;
};

#endif // !MapTile_hpp