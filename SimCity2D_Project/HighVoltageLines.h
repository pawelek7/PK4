#ifndef HighVoltageLines_hpp
#define HighVoltageLines_hpp

#include "RequireConnecting.h"
#include "IDvector.h"
#include "PathFinding.h"

class HighVoltageLines : public RequireConnecting
{
	bool connectedToPowerStation = false;
	ID voltageLineID = UNDEFINED;

	PathFinding *pathPylons = nullptr;

	std::vector<sf::Vector2i> powerStationCoordinates;

	sf::Vector2i pylonCoordinates;

public:
	HighVoltageLines() = default;
	HighVoltageLines(const sf::Texture & texture, TileSpecialise tileSpecialise, const std::vector<Frames> & frames, int height);
	virtual ~HighVoltageLines();

	virtual std::unique_ptr<SmallTile> clone() const  override;

	void AddPowerStationCoordinates(sf::Vector2i powerStationCoordinates);
	void RemovePowerStationMemory(sf::Vector2i position);
	void CheckConnectionToPowerStation();

	void InitializeHighVoltageLinesParameters(bool connectedToPowetStation, ID voltageLineID,
		sf::Vector2i & pylonCoordinates, std::vector<sf::Vector2i> & powerStationCoordinates);

	//setters
	void SetPylonCoordinates(sf::Vector2i pylonCoordinates);
	void SetConnectedToPowerStation(bool connectedToPowerStation);
	void SetPathPylon(PathFinding *pathPylons);
	void SetHighVoltageLinesID(ID id);

	//getters
	std::vector<sf::Vector2i> & GetPowetStationCoordinates();
	ID GetHighVoltageLinesID() const;
	bool GetConnectedToPowerStation() const;
	sf::Vector2i GetPylonCoordinates() const;
};

#endif // !HighVoltageLines_hpp