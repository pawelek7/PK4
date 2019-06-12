#include "HighVoltageLines.h"

#pragma region Constructors

HighVoltageLines::HighVoltageLines(const sf::Texture & texture, TileSpecialise tileSpecialise, const std::vector<Frames> & frames, int height)
	:RequireConnecting(texture, tileSpecialise, frames, height)
{
	this->height = height;
}

HighVoltageLines::~HighVoltageLines()
{

}

std::unique_ptr<SmallTile> HighVoltageLines::clone() const
{
	return std::make_unique<HighVoltageLines>(texture, tileSpecialise, frames, height);
}

#pragma endregion

#pragma region Class_Methods

void HighVoltageLines::CheckConnectionToPowerStation()
{
	for (auto & connection : powerStationCoordinates)
	{
		std::pair<int, int> A = std::make_pair(connection.x, connection.y);
		std::pair<int, int> B = std::make_pair(pylonCoordinates.x, pylonCoordinates.y);
		if (pathPylons->aStarSearch(A, B))
		{
			this->connectedToPowerStation = true;
			break;
		}
		else
		{
			this->connectedToPowerStation = false;
		}
	}
}

void HighVoltageLines::InitializeHighVoltageLinesParameters(bool connectedToPowerStation, ID voltageLineID,
	sf::Vector2i & pylonCoordinates, std::vector<sf::Vector2i> & powerStationCoordinates)
{
	this->connectedToPowerStation = connectedToPowerStation;
	this->voltageLineID = voltageLineID;
	this->pylonCoordinates = pylonCoordinates;
	this->powerStationCoordinates = powerStationCoordinates;
}

void HighVoltageLines::AddPowerStationCoordinates(sf::Vector2i powerStationCoordinates)
{
	this->powerStationCoordinates.push_back(powerStationCoordinates);
}

void HighVoltageLines::RemovePowerStationMemory(sf::Vector2i position)
{
	this->powerStationCoordinates.erase(std::remove(this->powerStationCoordinates.begin(),
		powerStationCoordinates.end(), position), this->powerStationCoordinates.end());
}

#pragma endregion

#pragma region Setters

void HighVoltageLines::SetPylonCoordinates(sf::Vector2i pylonCoordinates)
{
	this->pylonCoordinates = pylonCoordinates;
}

void HighVoltageLines::SetConnectedToPowerStation(bool connectedToPowerStation)
{
	this->connectedToPowerStation = connectedToPowerStation;
}

void HighVoltageLines::SetHighVoltageLinesID(ID id)
{
	this->voltageLineID = id;
}

sf::Vector2i HighVoltageLines::GetPylonCoordinates() const
{
	return this->pylonCoordinates;
}

void HighVoltageLines::SetPathPylon(PathFinding *pathPylons)
{
	this->pathPylons = pathPylons;
}

#pragma endregion

#pragma region Getters

std::vector<sf::Vector2i> & HighVoltageLines::GetPowetStationCoordinates() 
{
	return this->powerStationCoordinates;
}

bool HighVoltageLines::GetConnectedToPowerStation() const
{
	return this->connectedToPowerStation;
}

ID HighVoltageLines::GetHighVoltageLinesID() const
{
	return this->voltageLineID;
}

#pragma endregion