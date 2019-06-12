#ifndef House_hpp
#define House_hpp

#include <unordered_map>
#include <utility>

#include "Structure.h"

class House : public Structure
{
public:
	enum class HappinessEvent
	{
		NOTHING = 0, HAPPY = 1, ANGRY = 2
	};

private:
	int household = 0;
	int maxPopOnLvl = 10;
	int buildingDays = 3;
	int sickDomators = 0;
	int reservedSpace = 0;

	bool abandonedHouse = false;
	bool connectedToPower = false;
	bool addedNewDomators = false;
	bool up_people = false;
	bool epidemic = false;
	bool informationAboutEpidemic = false;

	HappinessEvent happinessEvent = HappinessEvent::NOTHING;

	void HouseThiefEvent();
	void SickPeopleEvent();

public:
	House() = default;
	House(const unsigned int height, const
		sf::Texture & texture, const TileSpecialise tileSpecialise, const std::vector<Frames> & frames,
		float population);
	virtual ~House();

	virtual std::unique_ptr<SmallTile> clone() const override;

	virtual void Update(float elapsedTime) override;
	void NewDayInHouse();
	void AddNewResidents(int residents);
	int UpdatePopulationHouse(int newHouseholdMembers);
	void SickPeopleToHospitalProcess();
	void ForceEpidemic();
	void AddOldDomatorToHouse();
	void ResetHappinessEvent();
	void InitializeHouseParameters(int household, int maxPopOnLvl, int buildingDays, int sickDomators, int reservedSpace,
		bool abandonedHouse, bool connectedToPower, bool addedNewDomators, bool epidemic, bool informationAboutEpidemic, 
		HappinessEvent happinessEvent);

	//setters
	void SetInformationAboutEpidemic(bool informationAboutEpidemic);
	
	//getters
	HappinessEvent GetHappinessEvent() const;
	int GetReservedSpace() const;
	float GetHappiness() const;
	int GetMaxPopOnLvl() const;
	int GetHousehold() const;
	bool GetIsAddedNewDomators() const;
	bool GetIsEpidemic() const;
	int GetSickPeopleNr() const;
	bool GetInformationAboutEpidemic() const;
	bool GetAbandonedHouse() const;
};

#endif // !House_hpp