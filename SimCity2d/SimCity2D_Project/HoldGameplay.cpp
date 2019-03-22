#include <cmath>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>

#include "HoldGameplay.h"
#include "Plate.h"

double HoldGameplay::distributePool(double &pool, Plate & plate, double rate = 0.0)
{
	const static int moveRate = 4;
	unsigned int maxPop = plate.popToUpgrade * (plate._tileVersion + 1);

	if (pool > 0)
	{
		int moving = maxPop - plate.population;
		if (moving > moveRate)
		{
			moving = moveRate;
		}
		if (pool - moving < 0)
		{
			moving = pool;
		}
		pool -= moving;
		plate.population += moving;
	}

	plate.population += plate.population * rate;

	if (plate.population > maxPop)
	{
		pool += plate.population - maxPop;
		plate.population = maxPop;
	}

	return plate.population;
}

void HoldGameplay::bulldoze(const Plate & plate)
{
	for (int i = 0; i < this->mapTile.width * this->mapTile.height; i++)
	{
		if (this->mapTile.selectedTiles[i] == 1)
		{
			if (this->mapTile._plate[i]._typeOfTile == TypeOfTile::HOUSES)
			{
				this->populationPool += this->mapTile._plate[i].population;
			}
			else if (this->mapTile._plate[i]._typeOfTile == TypeOfTile::FACTORY)
			{
				this->employmentPool += this->mapTile._plate[i].population;
			}
			else if (this->mapTile._plate[i]._typeOfTile == TypeOfTile::SHOPS)
			{
				this->employmentPool += this->mapTile._plate[i].population;
			}
			this->mapTile._plate[i] = plate;
		}
	}

	return;
}
	

void HoldGameplay::shuffleTiles()
{
	while (this->shuffledTiles.size() < this->mapTile._plate.size())
	{
		this->shuffledTiles.push_back(0);
	}

	std::iota(shuffledTiles.begin(), shuffledTiles.end(), 1);
	std::random_shuffle(shuffledTiles.begin(), shuffledTiles.end());
}

void HoldGameplay::tileChanged()
{
	/*
	this->map.updateDirection(TileType::ROAD);
	this->map.findConnectedRegions(
		{
			TileType::ROAD, TileType::RESIDENTIAL,
			TileType::COMMERCIAL, TileType::INDUSTRIAL
		}, 0);
		*/
}

void HoldGameplay::update(float dt)
{
	double popTital = 0;
	double commercialRevenue = 0;
	double industrialRevenue = 0;
	
	this->currentTime += dt;
	if (this->currentTime < this->timePerDay) return;

	++day;
	this->currentTime = 0.0;

	if (day % 30 == 0)
	{
		this->funds += this->earnings;
		this->earnings = 0;
	}

	for (int i = 0; i < this->mapTile._plate.size(); ++i)
	{
		Plate& tile = this->mapTile._plate[this->shuffledTiles[i]];

		if (tile._typeOfTile == TypeOfTile::HOUSES)
		{
			/* Redistribute the pool and increase the population total by the tile's population */
			this->distributePool(this->populationPool, tile, this->birthRate - this->deathRate);

			popTital += tile.population;
		}
		else if (tile._typeOfTile == TypeOfTile::SHOPS)
		{
			/* Hire people. */
			if (rand() % 100 < 15 * (1.0 - this->commercialTax))
				this->distributePool(this->employmentPool, tile, 0.00);
		}
		else if (tile._typeOfTile == TypeOfTile::FACTORY)
		{
			/* Extract resources from the ground. */
			if (this->mapTile.resources[i] > 0 && rand() % 100 < this->population)
			{
				//++tile.prpduction;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				--this->mapTile.resources[i];
			}
			/* Hire people. */
			if (rand() % 100 < 15 * (1.0 - this->industrialTax))
				this->distributePool(this->employmentPool, tile, 0.0);
		}
		tile.Update(); //NOT IMPLEMENTED FUNCTION!!!!!!!!!!!
	}
	
	/* Run second pass. Mostly handles goods manufacture */
	/*
	for (int i = 0; i < this->mapTile._plate.size(); ++i)
	{
		Plate& tile = this->mapTile._plate[this->shuffledTiles[i]];

		if (tile._typeOfTile == TypeOfTile::FACTORY)
		{
			int receivedResources = 0;
			// Receive resources from smaller and connected zones 
			for (auto& tile2 : this->mapTile._plate)
			{
				if (tile2.regions[0] == tile.regions[0] && tile2.tileType == TileType::INDUSTRIAL)
				{
					if (tile2.production > 0)
					{
						++receivedResources;
						--tile2.production;
					}
					if (receivedResources >= tile.tileVariant + 1) break;
				}
			}
			//  Turn resources into goods 
			tile.storedGoods += (receivedResources + tile.production)*(tile.tileVariant + 1);
		}
	}
	*/
	/* Run third pass. Mostly handles goods distribution. */
	/*
	for (int i = 0; i < this->map.tiles.size(); ++i)
	{
		Tile& tile = this->map.tiles[this->shuffledTiles[i]];

		if (tile.tileType == TileType::COMMERCIAL)
		{
			int receivedGoods = 0;
			double maxCustomers = 0.0;
			for (auto& tile2 : this->map.tiles)
			{
				if (tile2.regions[0] == tile.regions[0] &&
					tile2.tileType == TileType::INDUSTRIAL &&
					tile2.storedGoods > 0)
				{
					while (tile2.storedGoods > 0 && receivedGoods != tile.tileVariant + 1)
					{
						--tile2.storedGoods;
						++receivedGoods;
						industrialRevenue += 100 * (1.0 - industrialTax);
					}
				}
				else if (tile2.regions[0] == tile.regions[0] &&
					tile2.tileType == TileType::RESIDENTIAL)
				{
					maxCustomers += tile2.population;
				}
				if (receivedGoods == tile.tileVariant + 1) break;
			}
			// Calculate the overall revenue for the tile. 
			tile.production = (receivedGoods*100.0 + rand() % 20) * (1.0 - this->commercialTax);

			double revenue = tile.production * maxCustomers * tile.population / 100.0;
			commercialRevenue += revenue;
		}
	}
	*/


	/* Adjust population pool for births and deaths. */
	//this->populationPool = this->adjustPopulation(this->populationPool, this->birthRate - this->deathRate);
	//popTotal += this->populationPool;

	/* Adjust the employment pool for the changing population. */
	float newWorkers = (popTital - this->population) * this->propCanWork;
	newWorkers *= newWorkers < 0 ? -1 : 1;
	this->employmentPool += newWorkers;
	this->employable += newWorkers;
	if (this->employmentPool < 0) this->employmentPool = 0;
	if (this->employable < 0) this->employable = 0;

	/* Update the city population. */
	this->population = popTital;

	/* Calculate city income from tax. */

	/*
	this->earnings = (this->population - this->populationPool) * 15 * this->residentialTax;
	this->earnings += commercialRevenue * this->commercialTax;
	this->earnings += industrialRevenue * this->industrialTax; for (int i = 0; i < this->mapTile._plate.size(); ++i)
	{
		Plate& tile = this->mapTile._plate[this->shuffledTiles[i]];

		if (tile._typeOfTile == TypeOfTile::SHOPS)
		{
			int receivedGoods = 0;
			double maxCustomers = 0.0;
			for (auto& tile2 : this->mapTile._plate)
			{
				if (tile2.regions[0] == tile.regions[0] &&
					tile2.tileType == TileType::INDUSTRIAL &&
					tile2.storedGoods > 0)
				{
					while (tile2.storedGoods > 0 && receivedGoods != tile.tileVariant + 1)
					{
						--tile2.storedGoods;
						++receivedGoods;
						industrialRevenue += 100 * (1.0 - industrialTax);
					}
				}
				else if (tile2.regions[0] == tile.regions[0] &&
					tile2.tileType == TileType::RESIDENTIAL)
				{
					maxCustomers += tile2.population;
				}
				if (receivedGoods == tile.tileVariant + 1) break;
			}
			// Calculate the overall revenue for the tile. 
			tile.production = (receivedGoods*100.0 + rand() % 20) * (1.0 - this->commercialTax);

			double revenue = tile.production * maxCustomers * tile.population / 100.0;
			commercialRevenue += revenue;
		}
	}
	*/


}