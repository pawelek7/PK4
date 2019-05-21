#ifndef HoldGameplay_hpp
#define HoldGameplay_hpp

#include <vector>
#include <map>

#include "MapTile.h"
#include "SmallTile.h"
#include "IDvector.h"
#include "Structure.h"
#include "PictureInformation.h"
#include "Tornado.h"
#include "TaxesInformation.h"
#include "Fire.h"
#include "Newspaper.h"
#include "RandomEngine.h"
#include "HighVoltageLines.h"
#include "Statistics.h"

#include "PoliceStation.h"
#include "FireBrigade.h"

class Newspaper;

enum class TimeSpeed
{
	SLOW = 300, NORMAL = 200, FAST = 3, UBER = 1
};

enum class GameEvent
{
	VOID = 0, NEW_CITY = 1, NEW_MONTH = 2
};

class HoldGameplay 
{
public:
	struct InteractBuilding
	{
		enum class InterOption
		{
			VOID = 0, STRUCTURE = 1
		};

		InterOption interOption;
		Structure *structure = nullptr;

		InteractBuilding();
		InteractBuilding(Structure* structure);
	};

	InteractBuilding Interaction(const sf::Vector2f& position);

private:

	std::shared_ptr<AssetsOfGame> ptrGame = nullptr;

	MapTile *mapTile = nullptr;
	PictureInformation *pictureInformation = nullptr;
	Tornado *tornado = nullptr;
	Fire *fire = nullptr;
	TaxesInformation *taxesInformation = nullptr;
	Newspaper *newspaper = nullptr;
	Statistics *statistics = nullptr;
	RandomEngine randomEngine;

	GameEvent gameEvent = GameEvent::VOID;

	int mapSize = 0;
	TimeSpeed timeSpeed = TimeSpeed::NORMAL;

	IDvector<Structure*> IDstructures;
	IDvector<RequireConnecting*> IDconnectings;
	std::vector<House*> housesVector;
	std::vector<Shop*> shopVector;
	std::vector<Factory*> factoryVector;
	std::vector<Hospital*> hospitalsVector;
	std::vector<PowerHouse*> powerhousesVector;
	std::vector<PoliceStation*> policeStationVector;
	std::vector<FireBrigade*> fireBrigadeVector;
	std::vector<HighVoltageLines*> highVoltageLinesVector;

	ID id = std::numeric_limits<ID>::max();

	std::vector<PictureInformation*> pictureInformationVector;
	std::vector<PictureInformation*>::const_iterator iterPictureInformation;
	std::vector<Tornado*> tornadoVector;
	std::vector<Tornado*>::const_iterator iterTornado;
	std::vector<Fire*> fireVector;
	std::vector<Fire*>::const_iterator iterFire;

	uint64_t gameSeed = 0;
	std::string cityName = "";
	int money = 1000000;
	int homeless = 50;
	unsigned int cityPopulation = 0;
	unsigned int workingPopulation = 0;
	unsigned int unemployedPopulation = 0;
	unsigned int wantShoppingPopulation = 0;

	int propertyTaxes = 7;
	int cityOrdiances = 7;
	int policeDepartment = 7;
	int fireDepartment = 7;
	int healthWelfare = 7;

	float timeInGame = 0.0f;
	float actualTime = 0.0f;

	unsigned int day = 1;
	unsigned int month = 0;
	unsigned int year = 2000;

	float happiness = 0.0f;
	float attractivness = 0.0f;

	void UpdateStatistics();
	void ComputeHappiness();
	void ComputeAttractivess();

	void EventNewDay();
	void EventNewMonth();
	void EventNewYear();

	void ForceRemovePictureIndormation(ID buildingID);
	void DestroyStructureID(std::vector<ID> & structuresToDestroy);
	void DestroyConnectionID(std::vector<ID> & connectionsToDestroy);
	void RandomiseBuildings();
	void TaxesManaging();
	void UpdateStatisticsTable();
	void UpdateDisasters(float elapsedTime);
	void DestroyedByDisaster(ID buildingID);
	void TornadoRandomEvent();
	void NewHomelessManaging();

public:
	HoldGameplay() = default;
	HoldGameplay(std::shared_ptr<AssetsOfGame> ptrGame,
		const std::string & CityName, uint64_t seedMap, unsigned int sizeOfMap, bool loadGame);
	virtual ~HoldGameplay();

	void Draw(sf::RenderWindow *renderTarget, float elapsedTime);

	void ChangeTileG(TileSpecialise tileSpecialise, bool specialBuilding);
	void Update(float elapsedTime);

	void SaveCityInformation();
	void LoadCityInformation();

	void DecreaseCityFunds(int totalCost);

	void ForceCycloneEvent();
	void ForceEpidemicEvent();
	void ForceFireEvent();

	void SetTimeSpeed(TimeSpeed timeSpeed);
	void PushPictureInformationToVector(Structure* structure, PictureType pictureType, bool animationType = false);

	MapTile *GetMaptile();
	Structure* GetStructure(ID _id);
	TaxesInformation *GetTaxesInformation();
	Newspaper *GetNewspaper();
	Statistics *GetStatistics();

	std::string GetFromattedMonth() const;;
	std::string GetDate();
	GameEvent GetEventName() const;
	std::string GetCityName() const;

	uint64_t GetGameSeed() const;
	unsigned int GetDay() const;
	unsigned int GetMonth() const;
	unsigned int GetYear() const;

	float GetAverageHappiness() const;
	float GetAttractiveness() const;

	int GetCityMoney() const;
	int GetPopulation() const;
	int GetHomeless() const;
	int GetUnemployed() const;

	void SetPropertyTaxes(int propertyTaxes);
	void SetCityOrdiances(int cityOrdiances);
	void SetPoliceDepartment(int policeDepartment);
	void SetFireDepartment(int fireDepartment);
	void SetHealthWelfare(int healthWalfare);

	int GetPropertyTaxes() const;
	int GetCityOrdiances() const;
	int GetPoliceDepartment() const;
	int GetFireDepartment() const;
	int GetHealthWelfare() const;
};

#endif // !HoldGameplay_hpp