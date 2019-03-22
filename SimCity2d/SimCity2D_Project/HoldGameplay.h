#pragma once

#include <vector>
#include <map>
#include <numeric>

#include "MapTile.h"

class HoldGameplay
{
	float currentTime;
	float timePerDay;

	std::vector<int> shuffledTiles;

	double populationPool;
	double employmentPool;
	float propCanWork;

	double birthRate;
	double deathRate;

	double distributePool(double & pool, Plate & plate, double rate);

public:
	MapTile mapTile;

	double population;
	double employable;

	double residentialTax;
	double industrialTax;
	double commercialTax;

	double earnings;
	double funds;

	int day;

	HoldGameplay()
	{
		this->birthRate = 0.00055;
		this->deathRate = 0.00023;
		this->propCanWork = 0.50;
		this->populationPool = 0;
		this->population = populationPool;
		this->employmentPool = 0;
		this->employable = employmentPool;
		this->residentialTax = 0.05;
		this->commercialTax = 0.05;
		this->industrialTax = 0.05;
		this->earnings = 0;
		this->funds = 0;
		this->currentTime = 0.0;
		this->timePerDay = 1.0;
		this->day = 0;
	}

	HoldGameplay(std::string cityName, int tileSize, std::map<std::string, Plate>&tileAtlas)
		:HoldGameplay()
	{
		this->mapTile.tileSize = tileSize;
		//load(cityName, tileAtlas);
	}

	//void load(std::string cityName, std::map<std::string, Plate>& tileAtlas);
	//void save(std::string cityName);

	void update(float dt);
	void bulldoze(const Plate& plate);
	void shuffleTiles();
	void tileChanged();

	double getHomeless()
	{
		return this->populationPool;
	}

	double getUnemployed()
	{
		return this->employmentPool;
	}
};