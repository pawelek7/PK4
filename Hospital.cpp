#include "Hospital.h"

#pragma region Constructors

Hospital::Hospital(const unsigned int height, const sf::Texture & texture, const TileSpecialise tileSpecialise, const std::vector<Frames> & frames)
	:Structure(height, tileSpecialise, texture, frames)
{
	this->heightBuilding = height;

	this->vehicle1 = new Vehicle(VehicleType::AMBULANCE);
	this->hasVehicle = true;
	this->vehicle1->SetBuildingOwner(this);

	this->BuildHospital();
	this->driveToDestination = new DriveToDestination();


	this->key = 4;
}

#pragma endregion

#pragma region Class_Methods

std::unique_ptr<SmallTile> Hospital::clone() const
{
	return std::make_unique<Hospital>(heightBuilding, texture, tileSpecialise, frames);
}

void Hospital::BuildHospital()
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
		this->sprite.setTexture(this->textureBuildManager.GetAppropriateTexture("hospital"));
		this->heightBuilding = 2;
		this->buildedStructure = true;
	}
}

void Hospital::AddPatients(int patients)
{
	this->patients += patients;
}

void Hospital::Update(float elapsedTime)
{
	
}

void Hospital::Destroy()
{

}

void Hospital::UpdateInformation()
{

}

#pragma endregion