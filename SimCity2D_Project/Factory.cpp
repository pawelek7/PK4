#include "Factory.h"

#pragma region Constructors

Factory::Factory(const unsigned int height, const sf::Texture & texture, 
	const TileSpecialise tileSpecialise, const std::vector<Frames> & frames)
	:Structure(height, tileSpecialise, texture, frames)
{
	this->structureType = TextureBuildManager::TextureType::FACTORY;

	this->heightBuilding = height;

	this->cityOrdinancesStructure = 1000;
	
	this->vehicle1 = new Vehicle(Vehicle::VehicleType::DELIVERY_VAN);
	this->hasVehicle = true;
	vehicle1->SetBuildingOwner(this);

	this->driveToDestination = new DriveToDestination();
}

Factory::~Factory()
{
}

std::unique_ptr<SmallTile> Factory::clone() const
{
	return std::make_unique<Factory>(heightBuilding, texture, tileSpecialise, frames);
}

#pragma endregion

#pragma region Class_Methods

void Factory::NewFactoryDay()
{
	if (this->cityOrdinancesPercentage < this->workers + (this->maxGoodsStorage - this->storedGoods)/100.0f)
	{
		this->strike = true;
	}
	else
	{
		this->strike = false;
	}
}

void Factory::InitializeFactoryParameters(int workers, int maxWorkersPerLvl, int storedGoods, int vehicleCargo, int maxGoodsStorage)
{
	this->workers = workers;
	this->maxWorkersPerLvl = maxWorkersPerLvl;
	this->storedGoods = storedGoods;
	this->vehicleCargo = vehicleCargo;
	this->maxGoodsStorage = maxGoodsStorage;
}

void Factory::Update(float elapsedTime)
{
	this->ProcessDriving(elapsedTime);

	if (this->workers >= this->maxWorkersPerLvl && this->actualLevel < 2)
	{
		this->buildedStructure = false;
		this->maxWorkersPerLvl *= 2;
	}
}

void Factory::ProduceGoods()
{
	if (this->storedGoods < this->maxGoodsStorage)
	{
		this->storedGoods += this->workers * (cityOrdinancesPercentage / 100.0f);
	}
}



bool Factory::CanDeliverGoods()
{
	if (storedGoods > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Factory::UpdateWorkersPopulation(int newEmployees)
{
	int overPeople = 0;

	if (this->actualLevel < 2)
	{
		this->workers += newEmployees;

		if (this->workers > this->maxWorkersPerLvl)
		{
			overPeople = this->workers - this->maxWorkersPerLvl;
			this->workers -= overPeople;
		}
		return overPeople;
	}
	return newEmployees;
}

#pragma endregion

#pragma region Setters


#pragma endregion

#pragma region Getters

int Factory::GetWorkersAmount() const
{
	return this->workers;
}


int Factory::GetDeliveryAmount() 
{
	if (this->storedGoods > this->vehicleCargo)
	{
		this->storedGoods -= vehicleCargo;
		return vehicleCargo;
	}
	else
	{
		int tmpStoredGoods = this->storedGoods;
		this->storedGoods = 0;
		return tmpStoredGoods;
	}
}

int Factory::GetGoodsAmounst() const
{
	return this->storedGoods;
}

int Factory::GetMaxWorkersPerLvl() const
{
	return this->maxWorkersPerLvl;
}

int Factory::GetVehicleCargo() const
{
	return this->vehicleCargo;
}

int Factory::GetMaxGoodsStorage() const
{
	return this->maxGoodsStorage;
}

#pragma endregion