#include "Shop.h"

#pragma region Constructors

Shop::Shop(const unsigned int height, const sf::Texture & texture, const TileSpecialise tileSpecialise , const std::vector<Frames> & frames)
	:Structure(height, tileSpecialise, texture, frames)
{
	this->structureType = TextureBuildManager::TextureType::SHOP;
	this->heightBuilding = height;
}

#pragma endregion

#pragma region Operators

Shop & Shop::operator+(int deliveredGoods)
{
	this->goods += deliveredGoods;

	return *this;
}

Shop & Shop::operator++()
{
	this->goods++;

	return *this;
}

Shop Shop::operator++(int)
{
	Shop moreGoods(*this);
	++(*this);
	return moreGoods;
}

Shop Shop::operator--(int)
{
	Shop sellGoods(*this);
	--(*this);
	return sellGoods;
}

Shop & Shop::operator--()
{

	if (this->goods > 0 && this->customers < this->maxCustomersPerLvl)
	{
		this->goods--;
		this->customers++;
		this->propertyTaxesStructure += 10;
	}

	return *this;
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
		this->maxCustomersPerLvl *= 3;
	}

	if (goods <= 0)
	{
		this->emptyWarehouse = true;
	}
}

void Shop::InitializeShopParameters(int employess, int maxEmployeesOnLvl, int customers, int maxCustomersPerLvl,
	int goods, int maxGoodsInShop, bool emptyWarehouse, bool addedInformation)
{
	this->employees = employess;
	this->maxCustomersPerLvl = maxEmployeesOnLvl;
	this->customers = customers;
	this->maxCustomersPerLvl = maxCustomersPerLvl;
	this->goods = goods;
	this->maxGoodsInShop = maxGoodsInShop;
	this->emptyWarehouse = emptyWarehouse;
	this->addedInformation = addedInformation;
}

void Shop::NewDayInShop()
{
	this->customers = 0;
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

void Shop::EmptyTheMoney()
{
	this->propertyTaxesStructure = 0;
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

int Shop::GetMaxCustomersOnLvl() const
{
	return this->maxCustomersPerLvl;
}

int Shop::GetMaxGoodsInShop() const
{
	return this->maxGoodsInShop;
}

int Shop::GetCustomers() const
{
	return this->customers;
}

int Shop::GetMaxEmployessOnLvl() const
{
	return this->MaxEmployeesPerLvl;
}

bool Shop::GetEmptyWarehouse() const
{
	return this->emptyWarehouse;
}

bool Shop::GetAddedInformation() const
{
	return this->addedInformation;
}

bool Shop::GetIsClosedToday() const
{
	if (this->customers >= this->maxCustomersPerLvl)
	{
		return true;
	}

	return false;
}

#pragma endregion