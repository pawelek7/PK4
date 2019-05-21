#include "Factory.h"

#pragma region Constructors

Factory::Factory(const unsigned int height, const sf::Texture & texture, 
	const TileSpecialise tileSpecialise, const std::vector<Frames> & frames)
	:Structure(height, tileSpecialise, texture, frames)
{
	this->structureType = StructureType::FACTORY;

	this->heightBuilding = height;

	this->vehicle1 = new Vehicle(VehicleType::AMBULANCE);
	this->hasVehicle = true;
	vehicle1->SetBuildingOwner(this);

	this->driveToDestination = new DriveToDestination();

	this->key = 3;
}

std::unique_ptr<SmallTile> Factory::clone() const
{
	return std::make_unique<Factory>(heightBuilding, texture, tileSpecialise, frames);
}

#pragma endregion

#pragma region Class_Methods

void Factory::Update(float elapsedTime)
{
	this->ProcessDriving(elapsedTime);

	if (this->workers >= this->maxWorkersPerLvl && this->actualLevel < 2)
	{
		this->buildedStructure = false;
		this->maxWorkersPerLvl *= 2;
	}
}

void Factory::Destroy()
{
	//... SOON
}

void Factory::UpdateInformation()
{
	//... SOON
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

std::string Factory::GetInformationAboutVehicle()
{
	if (this->vehicleInUse)
	{
		return "Working";
	}
	else
	{
		return "Available";
	}
}

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

#pragma endregion