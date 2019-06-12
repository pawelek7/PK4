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
#include "NoCopyNoMove.h"
#include "GameEventInfo.h"

/*
Class responsible for holding city operations:
time, money, people, structures...

@author
Pawel Salicki
*/

class Newspaper;

class HoldGameplay : public NoCopyNoMove
{
public:
	struct InteractBuilding //if there is interaction with object and mouse
	{
		enum class InterOption //option interaction
		{
			VOID = 0, STRUCTURE = 1
		};

		InterOption interOption;
		Structure *structure = nullptr;

		InteractBuilding();
		InteractBuilding(Structure* structure);
	};

	InteractBuilding Interaction(const sf::Vector2f& position); //check interaction with building and mouse

	enum class TimeSpeed //time speed of game
	{
		SLOW = 300, NORMAL = 200, FAST = 3, UBER = 1
	};

	enum class GameEvent //event in game
	{
		VOID = 0, NEW_CITY = 1, NEW_MONTH = 2
	};

private:
	std::shared_ptr<AssetsOfGame> ptrGame = nullptr; //pointer to game assets

	MapTile *mapTile = nullptr; //pointers to objects
	PictureInformation *pictureInformation = nullptr;
	Tornado *tornado = nullptr;
	Fire *fire = nullptr;
	TaxesInformation *taxesInformation = nullptr;
	Newspaper *newspaper = nullptr;
	Statistics *statistics = nullptr;
	GameEventInfo *gameEventInfo = nullptr;

	RandomEngine randomEngine; //engine of random numbers

	GameEvent gameEvent = GameEvent::VOID; //event of game
	TimeSpeed timeSpeed = TimeSpeed::NORMAL; //speed of game

	IDvector<Structure*> IDstructures; //containers of pointers to structures
	IDvector<RequireConnecting*> IDconnectings;
	std::vector<House*> housesVector;
	std::vector<Shop*> shopVector;
	std::vector<Factory*> factoryVector;
	std::vector<Hospital*> hospitalsVector;
	std::vector<PowerHouse*> powerhousesVector;
	std::vector<PoliceStation*> policeStationVector;
	std::vector<FireBrigade*> fireBrigadeVector;
	std::vector<HighVoltageLines*> highVoltageLinesVector;

	ID id = std::numeric_limits<ID>::max(); //id

	std::vector<PictureInformation*> pictureInformationVector; //containers of events
	std::vector<PictureInformation*>::const_iterator iterPictureInformation;
	std::vector<Tornado*> tornadoVector;
	std::vector<Tornado*>::const_iterator iterTornado;
	std::vector<Fire*> fireVector;
	std::vector<Fire*>::const_iterator iterFire;

	int mapSize = 0; //size of map
	uint64_t gameSeed = 0; //game seed
	std::string cityName = ""; //name of city

	int money = 1000000; //money amount
	int homeless = 50; //homeless
	unsigned int cityPopulation = 0; //population of city
	unsigned int workingPopulation = 0; //working people amount
	unsigned int unemployedPopulation = 0; //unemployed people amount
	unsigned int wantShoppingPopulation = 0; //people who can shopping
	int incomeThisMonth = 0; //income of money 
	int incomePreviousMonth = 0; //income of money last month

	int propertyTaxes = 7; //taxes percentge
	int cityOrdiances = 7;
	int policeDepartment = 7;
	int fireDepartment = 7;
	int healthWelfare = 7;

	float timeInGame = 0.0f; //time management
	float actualTime = 0.0f;

	unsigned int day = 1; //date
	unsigned int month = 0;
	unsigned int year = 2000;

	float happiness = 0.0f; //whole happiness
	float attractivness = 0.0f; //whole attractivness

	void UpdateStatistics(); //update statistics
	void ComputeHappiness(); //calculate whole happiness
	void ComputeAttractivess(); //calculate whole attractivness

	void EventNewDay(); //events in new day
	void EventNewMonth(); //events in new month
	void EventNewYear(); //events in new year

	void ForceRemovePictureIndormation(ID buildingID, PictureInformation::PictureType pictureType = PictureInformation::PictureType::VOID); //remove information
	void DestroyStructureID(std::vector<ID> & structuresToDestroy); //destroy structure
	void DestroyConnectionID(std::vector<ID> & connectionsToDestroy); //destroy connection
	void TaxesManaging(); //manage taxes
	void UpdateStatisticsTable(); //update statistics
	void UpdateDisasters(float elapsedTime); //update disasters
	void DestroyedByDisaster(ID buildingID); //destroy building that was destroyed by disaster
	void TornadoRandomEvent(); //tornado event
	void NewHomelessManaging(); //homeless management
	void InitializeBasicAssets(); //initialize basic assets of resources
	void CalculateMoneyIncome(); //calculate income of money

public:
	HoldGameplay() = default;
	HoldGameplay(std::shared_ptr<AssetsOfGame> ptrGame,
		const std::string & CityName, uint64_t seedMap, unsigned int sizeOfMap, bool loadGame);
	virtual ~HoldGameplay();

	void Draw(sf::RenderWindow *renderTarget, const float elapsedTime); //draw city

	void ChangeTileG(SmallTile::TileSpecialise tileSpecialise, bool specialBuilding); //change tile
	void Update(const float elapsedTime); //update city
	void ChangePictureInformationPosition();

	void SaveCityInformation(); //save city to file
	void LoadCityInformation(); //load city from file

	void DecreaseCityFunds(int totalCost); //decrease money
	void PushPictureInformationToVector(Structure* structure, PictureInformation::PictureType pictureType, bool animationType = false); //push picture to vector

	void ForceCycloneEvent(); //force tornado event
	void ForceEpidemicEvent(); //force epidemic event
	void ForceFireEvent(); //force fire event
	
	//setters
	void SetTimeSpeed(TimeSpeed timeSpeed);
	void SetPropertyTaxes(int propertyTaxes);
	void SetCityOrdiances(int cityOrdiances);
	void SetPoliceDepartment(int policeDepartment);
	void SetFireDepartment(int fireDepartment);
	void SetHealthWelfare(int healthWalfare);

	//getters
	MapTile *GetMaptile();
	Structure* GetStructure(ID _id);
	TaxesInformation *GetTaxesInformation();
	Newspaper *GetNewspaper();
	GameEventInfo *GetGameEventInfo();
	Statistics *GetStatistics();

	std::string GetFromattedMonth() const;
	std::string GetDate();
	std::string GetCityName() const;

	uint64_t GetGameSeed() const;
	unsigned int GetDay() const;
	unsigned int GetMonth() const;
	unsigned int GetYear() const;

	float GetAverageHappiness() const;
	float GetAttractiveness() const;

	int GetCityMoney() const;
	unsigned int GetPopulation() const;
	int GetHomeless() const;
	unsigned int GetUnemployed() const;

	int GetPropertyTaxes() const;
	int GetCityOrdiances() const;
	int GetPoliceDepartment() const;
	int GetFireDepartment() const;
	int GetHealthWelfare() const;
};

#endif // !HoldGameplay_hpp