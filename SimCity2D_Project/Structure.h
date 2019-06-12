#ifndef Structure_hpp
#define Structure_hpp

#include "SmallTile.h"
#include "IDvector.h"
#include "Vehicle.h"
#include "TextureBuildManager.h"
#include "PathFinding.h"
#include "DriveToDestination.h"
#include "RandomEngine.h"

class Vehicle;
class DriveToDestination;

class Structure : public SmallTile
{
public:
	enum class VehicleVisible
	{
		VOID = 0, VISIBLE = 1, INVISIBLE = 2
	};

private:
	unsigned int versionOfBuilding = 0;

protected:
	ID buildingID = UNDEFINED;
	TextureBuildManager textureBuildManager;

	VehicleVisible vehicleVisible = VehicleVisible::INVISIBLE;
	TextureBuildManager::TextureType structureType;

	Vehicle *vehicle1 = nullptr;
	DriveToDestination *driveToDestination = nullptr;
	PathFinding *roadPath = nullptr;

	unsigned int actualLevel = 0;
	unsigned int heightBuilding = 0;
	int buildDays = 0;
	float happiness = 100.0f;
	int propertyTaxesStructure = 0;
	int cityOrdinancesStructure = 0;
	int robberyCounter = 0;
	float propertyTaxesPercentage = 0.0f;
	float cityOrdinancesPercentage = 0.0f;
	
	bool strike = false;
	bool thiefCaught = false;
	bool informationNoEnergy = false;
	bool informationThief = false;
	bool informationStrike = false;
	bool hasEnergy = false;
	bool buildedStructure = false;
	bool vehicleInUse = false;
	bool callBackVehicle = false;
	bool travelDestinationSuccess = false;
	bool structureOnFire = false;
	bool thiefInBuilding = false;
	bool hasVehicle = false;
	bool rememberRoute = false;

public:
	Structure() = default;
	Structure(const unsigned int heightBuilding, TileSpecialise tileSpecialise,
		const sf::Texture & texture, const std::vector<Frames> & frames, ID buildingID = UNDEFINED);
	virtual ~Structure();

	virtual std::unique_ptr<SmallTile> clone() const override;

	void ChangeTexture();
	virtual void Draw(sf::RenderWindow& window, float elapsedTime, sf::Shader *shader = nullptr, const sf::Vector2f & camera_position = sf::Vector2f(0, 0)) override;
	virtual void SetNewTileVariant(const SmallTile * neighbourghood[NEIGHBORING][NEIGHBORING]) {}
	virtual void Update(float elapsedTime) {}

	void InitializeStructureParameters(ID buildingID, VehicleVisible vehicleVisible, unsigned int actualLevel, unsigned int heightBuilding,
		int buildDays, float happiness, int propertyTaxesStructure, int cityOrdinancesStructure, int robberyCounter, float propertyTaxesPercentage,
		float cityOrdinancesPercentage, bool strike, bool thiefCaught, bool informationNoEnergy, bool informationThief, bool informationStrike,
		bool hasEnergy, bool buildedStructure, bool vehicleInUse, bool callBackVehicle, bool travelDestinationSuccess, bool structureOnFire,
		bool thiefInBuilding, bool hasVehicle);

	virtual bool Interaction(const sf::Vector2f& position) override;
	void DriveToBuildingStart(Structure *structure);
	void ProcessDriving(float elapsedTime);

	void BuildStructure();
	bool GetBuildStatus();

	float RandomiseEvent(int from, int to);

	//setters
	void SetCityOrdinancesPercentage(float cityOrdinancePercentage);
	void SetPropertyTaxesPercentage(float propertyTaxesPercentage);
	void SetTravelDestinationSuccess(bool deliverySuccess);
	void SetID(ID id);
	void SetPathRoad(PathFinding *roadPath);
	void SetHasEnergy(bool hasEnergy);
	void SetInformationNoEnergy(bool informationNoEnergy);
	void SetStructureOnFire(bool onFire);
	void SetVehicleInUse(bool vehicleInUse);
	void SetThiefInBuilding(bool thief);
	void SetInformationThief(bool informationThief);
	void SetThiefCaught(bool thiefCaught);
	void SetInformationStrike(bool informationStrike);
	void SetHasVehicle(bool hasVehicle);

	//getters

	std::string GetInformationAboutVehicle() const;
	bool GetInformationStrike() const;
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
	bool GetVehicleInUse() const;
	bool GetThiefInBuilding() const;
	int GetStructureHeight() const;
	bool GetInformationThief() const;
	bool GetThiefCaught() const;
	bool GetCallBackVehicle() const;
	bool GetIsStrike() const;
	bool GetHasVehicle() const;
	int GetBuildDays() const;
	float GetCityOrdinancesPercentage() const;
	float GetPropertyTaxesPercentage() const;
	unsigned int GetActualLevel() const;
	int GetPropertyTaxesStructure() const;
	int GetCityOrdinancesStructure() const;
	int GetRobberryCounter() const;
};

#endif // !Structure_hpp