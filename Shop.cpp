#include "Shop.h"

#pragma region Constructors

Shop::Shop(const unsigned int height, const sf::Texture & texture, const TileSpecialise tileSpecialise , const std::vector<Frames> & frames)
	:Structure(height, tileSpecialise, texture, frames)
{
	this->structureType = StructureType::SHOP;

	this->heightBuilding = height;


	this->key = 2;
}

#pragma endregion

#pragma region Class_Methods

std::unique_ptr<SmallTile> Shop::clone() const
{
	return std::make_unique<Shop>(heightBuilding, texture, tileSpecialise, frames);
}

void Shop::Update(float elapsedTime)
{
	if (this->employees >= this->MaxEmployeesPerLvl && this->actualLevel < 2)
	{
		this->buildedStructure = false;
		this->MaxEmployeesPerLvl *= 2;
	}

	if (goods <= 0)
	{
		this->emptyWarehouse = true;
	}
}


int Shop::UpdateWorkersPopulation(int newEmployees)
{
	int overPeople = 0;

	if (this->actualLevel < 2)
	{
		this->employees += newEmployees;

		if (this->employees > this->MaxEmployeesPerLvl)
		{
			overPeople = this->employees - this->MaxEmployeesPerLvl;
			this->employees -= overPeople;
		}
		return overPeople;
	}
	return newEmployees;
}


void Shop::DeliveredGoods(int goodsAmount)
{
	this->goods += goodsAmount;

	if (goods > 0)
	{
		this->emptyWarehouse = false;
	}
}

void Shop::Destroy()
{
	//... SOON
}

void Shop::UpdateInformation()
{
	//... SOON
}

#pragma endregion

#pragma region Setters

void Shop::SetAddedInformation(bool addedInformation)
{
	this->addedInformation = addedInformation;
}

#pragma endregion

#pragma region Getters

int Shop::GetEmployessNr() const
{
	return this->employees;
}

int Shop::GetActualAmountOfCustomets() const
{
	return this->customers;
}

int Shop::GetGoodsAmount() const
{
	return this->goods;
}

bool Shop::GetEmptyWarehouse() const
{
	return this->emptyWarehouse;
}

bool Shop::GetAddedInformation() const
{
	return this->addedInformation;
}

#pragma endregion