#include "House.h"

#pragma region Constructors

House::House(const unsigned int height, const
	sf::Texture & texture, const TileSpecialise tileSpecialise, const std::vector<Frames> & frames,
	float household)
	:Structure(height, tileSpecialise, texture, frames)
{
	this->heightBuilding = height;
	this->household = household;
	this->propertyTaxesStructure = 100;
	this->happiness = 50.0f;

	this->hasVehicle = true;
	this->vehicle1 = new Vehicle(Vehicle::VehicleType::CYVILIAN);
	vehicle1->SetBuildingOwner(this);
	this->driveToDestination = new DriveToDestination();
}

House::~House()
{
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

void House::Update(float elapsedTime)
{
	if (this->household >= this->maxPopOnLvl && this->actualLevel <3)
	{
		this->buildedStructure = false;
		
		maxPopOnLvl *= 2;
		propertyTaxesStructure *= 2;
	}

	if (this->happiness < 0)
	{
		this->happiness = 0;
	}

	this->ProcessDriving(elapsedTime);
	this->SickPeopleEvent();
	this->HouseThiefEvent();
}

void House::InitializeHouseParameters(int household, int maxPopOnLvl, int buildingDays, int sickDomators, int reservedSpace,
	bool abandonedHouse, bool connectedToPower, bool addedNewDomators, bool epidemic, bool informationAboutEpidemic,
	HappinessEvent happinessEvent)
{
	this->household = household;
	this->maxPopOnLvl = maxPopOnLvl;
	this->buildingDays = buildingDays;
	this->sickDomators = sickDomators;
	this->reservedSpace = reservedSpace;
	this->abandonedHouse = abandonedHouse;
	this->connectedToPower = connectedToPower;
	this->addedNewDomators = addedNewDomators;
	this->epidemic = epidemic;
	this->informationAboutEpidemic = informationAboutEpidemic;
	this->happinessEvent = happinessEvent;
}

void House::HouseThiefEvent()
{
	int thief = this->RandomiseEvent(0, 10000);

	if(thief == 1)
	{
		this->thiefInBuilding = true;
	}

	if (thiefInBuilding == true)
	{
		this->robberyCounter++;

		if (this->robberyCounter > 1000)
		{
			this->thiefInBuilding = false;
			this->thiefCaught = true;

			this->happiness -= 10.0f;
			this->happinessEvent = HappinessEvent::ANGRY;
		}
	}
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

void House::ResetHappinessEvent()
{
	this->happinessEvent = HappinessEvent::NOTHING;
}

void House::AddOldDomatorToHouse()
{
	this->reservedSpace--;
	this->household++;
}

void House::SickPeopleToHospitalProcess()
{
	this->sickDomators--;
	this->household--;
	this->reservedSpace++;
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

void House::NewDayInHouse()
{
	if (this->propertyTaxesPercentage > this->household  * actualLevel && this->household > 5 && this->happiness > 0)
	{
		this->happinessEvent = HappinessEvent::ANGRY;
		this->happiness -= 5;
	}

	if (this->hasEnergy == false)
	{
		this->happiness -= 1;
	}
	else
	{
		if (happiness < 50)
		{
			this->happiness++;
		}
	}

	if (this->happiness < 10.0f && this->household>0)
	{
		this->household -= 2;

		if (this->household < 0)
		{
			this->household = 0;
		}
	}

	if (this->household <= 0 && this->happiness <= 10.0f)
	{
		this->abandonedHouse = true;
	}
}


#pragma endregion

#pragma region Setters

void House::SetInformationAboutEpidemic(bool informationAboutEpidemic)
{
	this->informationAboutEpidemic = informationAboutEpidemic;
}

#pragma endregion

#pragma region Getters

House::HappinessEvent House::GetHappinessEvent() const
{
	return this->happinessEvent;
}

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

int House::GetReservedSpace() const
{
	return this->reservedSpace;
}

bool House::GetInformationAboutEpidemic() const
{
	return this->informationAboutEpidemic;
}

bool House::GetAbandonedHouse() const
{
	return this->abandonedHouse;
}
#pragma endregion