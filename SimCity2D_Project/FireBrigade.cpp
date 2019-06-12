#include "FireBrigade.h"

#pragma region Constructors

FireBrigade::FireBrigade(const unsigned int height, const sf::Texture & texture,
	const TileSpecialise tileSpecialise, const std::vector<Frames> & frames)
	:Structure(height, tileSpecialise, texture, frames)
{
	this->heightBuilding = height;

	this->vehicle1 = new Vehicle(Vehicle::VehicleType::FIRE_TRUCK);
	this->hasVehicle = true;

	this->BuildFireBrigade();
	this->driveToDestination = new DriveToDestination();
}

FireBrigade::~FireBrigade()
{
}

std::unique_ptr<SmallTile> FireBrigade::clone() const
{
	return std::make_unique<FireBrigade>(heightBuilding, texture, tileSpecialise, frames);
}

#pragma endregion

#pragma region Operators

FireBrigade & FireBrigade::operator++()
{
	this->extinguishedFires++;

	return *this;
}

FireBrigade FireBrigade::operator++(int)
{
	FireBrigade moreFire(*this);
	++(*this);

	return moreFire;
}

#pragma endregion

#pragma region Class_Methods

void FireBrigade::BuildFireBrigade()
{
	if (this->buildDays == 0)
	{
		this->sprite.setTexture(this->textureBuildManager.GetBuildingTexture());
		this->heightBuilding = this->textureBuildManager.GetBuildingProcessHeight();
		this->buildedStructure = false;
	}

	this->buildDays++;

	if (this->buildDays > 5)
	{
		this->sprite.setTexture(this->textureBuildManager.GetAppropriateTexture("fire_station"));
		this->heightBuilding = 2;
		this->buildedStructure = true;
	}
}

void FireBrigade::InitializeFireBrigadeParameters(int fireFighters, int maxFireFighters, int fireDepartamentStructure, 
	int fireDepartamentPercentage, int extinguishedFires)
{
	this->firefFighters = fireFighters;
	this->maxFirefighters = maxFireFighters;
	this->fireDepartmentStructure = fireDepartamentStructure;
	this->fireDepartmentPercentage = fireDepartamentPercentage;
	this->extinguishedFires = extinguishedFires;
}

int FireBrigade::UpdateFirefightersPopulation(int newFirefighters)
{
	int overPeople = 0;

	if (this->firefFighters < this->maxFirefighters)
	{
		this->firefFighters += maxFirefighters;

		if (this->firefFighters > this->maxFirefighters)
		{
			overPeople = this->firefFighters - this->maxFirefighters;
			this->firefFighters -= overPeople;
		}
		return overPeople;
	}
	return newFirefighters;
}

void FireBrigade::Update(float elapsedTime)
{
	this->ProcessDriving(elapsedTime);
}

void FireBrigade::NewDayFireBrigade()
{
	if (this->fireDepartmentPercentage < this->firefFighters)
	{
		this->strike = true;
	}
	else
	{
		this->strike = false;
	}
}

#pragma endregion

#pragma region Getters

int FireBrigade::GetExtinguishedFires() const
{
	return this->extinguishedFires;
}

int FireBrigade::GetMaxFireFighters() const
{
	return this->maxFirefighters;
}

int FireBrigade::GetFireDepartment() const
{
	return this->fireDepartmentStructure * this->fireDepartmentPercentage / 100.0f;
}

float FireBrigade::GetFireDepartamentPercentage() const
{
	return this->fireDepartmentPercentage;
}

void FireBrigade::SetFireDepartmentPercentage(float fireDepartmentPercentage)
{
	this->fireDepartmentPercentage = fireDepartmentPercentage;
}

int FireBrigade::GetFirefightersAmount() const
{
	return this->firefFighters;
}

#pragma endregion