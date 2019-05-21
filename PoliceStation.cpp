#include "PoliceStation.h"

PoliceStation::PoliceStation(const unsigned int height, const sf::Texture & texture,
	const TileSpecialise tileSpecialise, const std::vector<Frames> & frames)
	:Structure(height, tileSpecialise, texture, frames)
{

}

std::unique_ptr<SmallTile> PoliceStation::clone() const
{
	return std::make_unique<PoliceStation>(heightBuilding, texture, tileSpecialise, frames);
}

void PoliceStation::Update(float elapsedTime)
{

}

void PoliceStation::Destroy()
{

}

void PoliceStation::UpdateInformation()
{

}