#include "PoliceStation.h"

#pragma region Constructors

PoliceStation::PoliceStation(const unsigned int height, const sf::Texture & texture,
	const TileSpecialise tileSpecialise, const std::vector<Frames> & frames)
	:Structure(height, tileSpecialise, texture, frames)
{
	this->heightBuilding = height;

	this->vehicle1 = new Vehicle(Vehicle::VehicleType::POLICE);
	this->hasVehicle = true;
	this->vehicle1->SetBuildingOwner(this);

	this->BuildPoliceStation();
	this->driveToDestination = new DriveToDestination();
}

PoliceStation::~PoliceStation()
{
	try {

		for (int i = 0; i < this->prisonersVector.GetSize(); i++)
		{
			if (this->prisonersVector.GetObjects().at(i) != nullptr)
			{
				delete this->prisonersVector.GetObjects().at(i);
				this->prisonersVector.GetObjects().at(i) = nullptr;
			}
		}
	}
	catch (const std::out_of_range& e) {
	}
}

std::unique_ptr<SmallTile> PoliceStation::clone() const
{
	return std::make_unique<PoliceStation>(heightBuilding, texture, tileSpecialise, frames);
}

#pragma endregion

#pragma region Operators

PoliceStation & PoliceStation::operator++()
{
	if (this->prisoners < this->maxPrisoners)
	{
		this->prisoner = new Prisoner;
		prisoner->idPrisoner = UNDEFINED;
		prisoner->daysOfDetention = 5;
		prisoner->isFree = false;

		ID id = this->prisonersVector.Push(this->prisoner);
		this->prisoner->idPrisoner = id;

		this->prisoners++;
	}

	return *this;
}

PoliceStation PoliceStation::operator++(int)
{
	PoliceStation morePrisoners(*this);
	++(*this);
	return morePrisoners;
}

#pragma endregion

#pragma region Class_Methods

void PoliceStation::InitializePoliceStationParameters(IDvector<Prisoner*> & prisonersVector, int policemen, int maxPolicemen,
	int policeDepartmentStructure, float policeDepartmentPercenatge, int prisoners, int maxPrisoners)
{
	this->prisonersVector = prisonersVector;
	this->policemen = policemen;
	this->maxPolicemen = maxPolicemen;
	this->policeDepartmentStructure = policeDepartmentStructure;
	this->prisoners = prisoners;
	this->maxPrisoners = maxPrisoners;
}

void PoliceStation::NewDayInPoliceStation()
{
	for (auto & prisoner : this->prisonersVector.GetObjects())
	{
		prisoner->daysOfDetention--;

		if (prisoner->daysOfDetention < 0)
		{
			prisoner->isFree = true;
		}

		if (prisoner->isFree == true)
		{
			this->prisonersVector.PopID(prisoner->idPrisoner);
			this->prisoners--;
		}
	}

	if (this->policeDepartmentPercentage < this->policemen + this->prisoners)
	{
		this->strike = true;
	}
	else
	{
		this->strike = false;
	}

	if (this->prisoners < 0)
	{
		this->prisoners = 0;
	}
}

int PoliceStation::UpdatePolicemenPopulation(int newPolicemen)
{
	int overPeople = 0;

	if (this->policemen < this->maxPolicemen)
	{
		this->policemen += newPolicemen;

		if (this->policemen > this->maxPolicemen)
		{
			overPeople = this->policemen - this->maxPolicemen;
			this->policemen -= overPeople;
		}
		return overPeople;
	}
	return newPolicemen;
}

void PoliceStation::BuildPoliceStation()
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
		this->sprite.setTexture(this->textureBuildManager.GetAppropriateTexture("police_station"));
		this->heightBuilding = 2;
		this->buildedStructure = true;
	}
}

void PoliceStation::Update(float elapsedTime)
{
	this->ProcessDriving(elapsedTime);
}

#pragma endregion

#pragma region Setters

void PoliceStation::SetPoliceDepartmentPercentage(float policeDepartmentPercentage)
{
	this->policeDepartmentPercentage = policeDepartmentPercentage;
}

#pragma endregion

#pragma region Getters

IDvector<PoliceStation::Prisoner*> & PoliceStation::GetPrisonersVector()
{
	return this->prisonersVector;
}

int PoliceStation::GetPolicemen() const
{
	return this->policemen;
}

int PoliceStation::GetMaxPolicemen() const
{
	return this->maxPolicemen;
}

float PoliceStation::GetPoliceDepartmentPercenatge() const
{
	return this->policeDepartmentPercentage;
}

int PoliceStation::GetMaxPrisoners() const
{
	return this->maxPrisoners;
}

int PoliceStation::GetPrisoners() const
{
	return this->prisoners;
}

int PoliceStation::GetPoliceDepartment() const
{
	return this->policeDepartmentStructure * this->policeDepartmentPercentage / 100.0f;
}

#pragma endregion