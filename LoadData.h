#ifndef LoadData_hpp
#define LoadData_hpp

#include "SmallTile.h"
#include "AssetsOfGame.h"
#include "House.h"
#include "Factory.h"
#include "Shop.h"
#include"HighVoltageLines.h"
#include "Road.h"
#include "PowerHouse.h"
#include "Hospital.h"
#include "FireBrigade.h"

using TilesMap = std::vector<std::unique_ptr<SmallTile>>;

class LoadData
{
protected:
	std::shared_ptr<AssetsOfGame> ptrGame = nullptr;
	TilesMap tilesMap;

public:
	LoadData() = default;
	LoadData(std::shared_ptr<AssetsOfGame> ptrGame);

	void LoadAtlas();
	void LoadTextures();
};

#endif // !LoadData_hpp