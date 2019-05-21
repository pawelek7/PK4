#ifndef Structure_hpp
#define Structure_hpp

#include "SmallTile.h"
#include "IDvector.h"
#include "Vehicle.h"
#include "TextureBuildManager.h"
#include "PathFinding.h"
#include "DriveToDestination.h"

class Vehicle;
class DriveToDestination;

enum class VehicleVisible
{
	VOID = 0, VISIBLE = 1, INVISIBLE = 2
};

class Structure : public SmallTile
{
	unsigned int versionOfBuilding = 0;
	unsigned int maxLevel = 0;
	unsigned int sizeOfFloor = TILE_SIZE;

protected:

	ID buildingID = UNDEFINED;
	TextureBuildManager textureBuildManager;

	VehicleVisible vehicleVisible = VehicleVisible::INVISIBLE;
	StructureType structureType;

	Vehicle *vehicle1 = nullptr;
	DriveToDestination *driveToDestination = nullptr;
	PathFinding *roadPath = nullptr;
//	PathFinding *energyPath = nullptr;

	unsigned int actualLevel = 0;
	unsigned int heightBuilding = 0;
	int buildDays = 0;
	float happiness = 100.0f;

	bool informationNoEnergy = false;
	bool hasEnergy = false;
	bool buildedStructure = false;
	bool vehicleInUse = false;
	bool callBackVehicle = false;
	bool travelDestinationSuccess = false;
	bool structureOnFire = false;

public:
	int key;
	bool hasVehicle = false; //temporay public, make it protected in future

	bool operator()(const Structure & lx, const Structure &rx) const
	{
		return lx.key < rx.key;
	}

	bool operator<(Structure const &r) const
	{
		return key < r.key;
	}

	bool rememberRoute = false;

	Structure() = default;
	Structure(const unsigned int heightBuilding, TileSpecialise tileSpecialise,
		const sf::Texture & texture, const std::vector<Frames> & frames, ID buildingID = UNDEFINED);
	virtual ~Structure();

	virtual std::unique_ptr<SmallTile> clone() const override;

	virtual void Draw(sf::RenderWindow& window, float elapsedTime, sf::Shader *shader = nullptr, const sf::Vector2f & camera_position = sf::Vector2f(0, 0)) override;
	virtual void SetNewTileVariant(const SmallTile * neighbourghood[NEIGHBORING][NEIGHBORING]) override;
	virtual void UpdateInformation() override;

	virtual void Update(float elapsedTime);
	virtual void Destroy();

	virtual bool Interaction(const sf::Vector2f& position) override;
	void DriveToBuildingStart(Structure *structure);
	void ProcessDriving(float elapsedTime);

	void BuildStructure();
	bool GetBuildStatus();

	float RandomiseEvent(int from, int to);

	void SetTravelDestinationSuccess(bool deliverySuccess);
	void SetID(ID id);
	void SetPathRoad(PathFinding *roadPath);
	void SetHasEnergy(bool hasEnergy);
	void SetInformationNoEnergy(bool informationNoEnergy);
	void SetStructureOnFire(bool onFire);

	bool GetTravelDestinationSuccess();
	bool GetHasEnergy() const;
	VehicleVisible GetVehicleVisible() const;
	Vehicle *GetVehicle();
	const Vehicle *GetVehicle() const;
	PathFinding *GetPatchRoad();
	ID GetID();
	float GetHappiness() const;
	bool GetInformationNoEnergy() const;
	bool GetStructureOnFire() const;
};

#endif // !Structure_hpp
