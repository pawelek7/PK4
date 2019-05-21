#include "House.h"

#pragma region Constructors

House::House(const unsigned int height, const
	sf::Texture & texture, const TileSpecialise tileSpecialise, const std::vector<Frames> & frames,
	float household)
	:Structure(height, tileSpecialise, texture, frames)
{
	this->heightBuilding = height;
	this->household = household;

	if (tileData.texture_name != "unknown")
	{
		sprite.setTexture(this->textureBuildManager.GetAppropriateTexture(tileData.texture_name));
	}

	this->hasVehicle = true;
	this->vehicle1 = new Vehicle(VehicleType::CYVILIAN);
	vehicle1->SetBuildingOwner(this);
	this->driveToDestination = new DriveToDestination();

	this->key = 1;
}

std::unique_ptr<SmallTile> House::clone() const
{
	return std::make_unique<House>(heightBuilding, texture, tileSpecialise, frames, household);
}

#pragma endregion

#pragma region Class_Methods

void House::ForceEpidemic()
{
	if ((int)this->RandomiseEvent(0, 2) == 1)
	{
		if (this->household - this->sickDomators - 2 > 0)
		{
			this->sickDomators += 2;

			this->epidemic = true;
		}
	}
}

void House::UpdateInformation()
{
	this->household = tileData.population;
	this->actualLevel = tileData.level;
	this->heightBuilding = tileData.height;

	this->SetID(tileData.buildingID);

	if (tileData.texture_name != "unknown")
	{
		this->sprite.setTexture(textureBuildManager.GetAppropriateTexture(tileData.texture_name));
	}

	this->sprite.setOrigin(sf::Vector2f(0.0f, TILE_SIZE*(heightBuilding - 1)));
	this->frameSize = sf::IntRect(0, 0, TILE_SIZE * 2, TILE_SIZE*heightBuilding);
}

void House::Update(float elapsedTime)
{
	if (this->household >= this->maxPopOnLvl && this->actualLevel <3)
	{
		this->buildedStructure = false;
		
		maxPopOnLvl *= 2;

		tileData.level = this->actualLevel;
		tileData.population = household;
		tileData.height = heightBuilding;
	}

	this->ProcessDriving(elapsedTime);
	this->SickPeopleEvent();
}

void House::SickPeopleEvent()
{
	int sick = this->RandomiseEvent(0, 100000);

	if (sick == 1 && this->sickDomators < this->household)
	{
		this->sickDomators++;
		this->epidemic = true;
	}

	if (this->sickDomators <= 0)
	{
		this->epidemic = false;
	}
}

int House::SickPeopleToHospitalProcess()
{
	int sick_tmp = this->sickDomators;
	this->household -= sickDomators;
	this->reservedSpace = sickDomators;
	this->sickDomators = 0;

	return sick_tmp;
}

int House::UpdatePopulationHouse(int newHouseholdMembers)
{
	if (this->RandomiseEvent(0, 10) < 5)
	{
		this->addedNewDomators = false;
		return newHouseholdMembers;
	}

	int overPeople = 0;

	if (this->actualLevel < 3)
	{
		this->household += newHouseholdMembers;
		if (this->household + this->reservedSpace > this->maxPopOnLvl)
		{
			overPeople = (this->household + this->reservedSpace) - maxPopOnLvl;
			household -= overPeople;
		}
		if (overPeople < newHouseholdMembers)
		{
			this->addedNewDomators = true;
		}

		return overPeople;
	}

	this->addedNewDomators = false;
	return newHouseholdMembers;
}

void House::Destroy()
{
	//... SOON
}

#pragma endregion

#pragma region Setters

void House::SetInformationAboutEpidemic(bool informationAboutEpidemic)
{
	this->informationAboutEpidemic = informationAboutEpidemic;
}

#pragma endregion

#pragma region Getters

float House::GetHappiness() const
{
	return happiness;
}

void House::AddNewResidents(int residents)
{
	household += residents;
}

int House::GetMaxPopOnLvl() const
{
	return this->maxPopOnLvl;
}

int House::GetHousehold() const
{
	return this->household;
}

bool House::GetIsAddedNewDomators() const
{
	return this->addedNewDomators;
}

bool House::GetIsEpidemic() const
{
	return this->epidemic;
}

int House::GetSickPeopleNr() const
{
	return this->sickDomators;
}

bool House::GetInformationAboutEpidemic() const
{
	return this->informationAboutEpidemic;
}

#pragma endregion