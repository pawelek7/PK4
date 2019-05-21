#include "FireBrigade.h"

FireBrigade::FireBrigade(const unsigned int height, const sf::Texture & texture,
	const TileSpecialise tileSpecialise, const std::vector<Frames> & frames)
	:Structure(height, tileSpecialise, texture, frames)
{
	this->heightBuilding = height;

	this->vehicle1 = new Vehicle(VehicleType::FIRE_TRUCK);
	this->hasVehicle = true;

	this->BuildFireBrigade();
	this->driveToDestination = new DriveToDestination();
}

std::unique_ptr<SmallTile> FireBrigade::clone() const
{
	return std::make_unique<FireBrigade>(heightBuilding, texture, tileSpecialise, frames);
}

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

void FireBrigade::Update(float elapsedTime)
{
	this->ProcessDriving(elapsedTime);
}

void FireBrigade::Destroy()
{

}

void FireBrigade::UpdateInformation()
{

}