#ifndef LoadData_hpp
#define LoadData_hpp

#include "SmallTile.h"
#include "AssetsOfGame.h"
#include "House.h"
#include "Factory.h"
#include "Shop.h"
#include "HighVoltageLines.h"
#include "Road.h"
#include "PowerHouse.h"
#include "Hospital.h"
#include "FireBrigade.h"
#include "PoliceStation.h"
#include "NoCopyNoMove.h"

/*
Class responsible for load basic assets of map tile.

@author
Pawel Salicki
*/

using TilesMap = std::vector<std::unique_ptr<SmallTile>>; //smart pointer on tiles

class LoadData 
{
protected:
	std::shared_ptr<AssetsOfGame> ptrGame = nullptr; //smart pointer of game assets
	TilesMap tilesMap; //map of tiles

public:
	LoadData() = default;
	LoadData(std::shared_ptr<AssetsOfGame> ptrGame);
	virtual ~LoadData() = default;

	void LoadAtlas(); //load tiles to atlas
	void LoadTextures(); //load textures of tiles
};

#endif // !LoadData_hpp