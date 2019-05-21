#ifndef House_hpp
#define House_hpp

#include <unordered_map>
#include <utility>
#include <chrono>
#include <random>

#include "Structure.h"

class House : public Structure
{
	int household = 0;
	int maxPopOnLvl = 10;
	int buildingDays = 3;
	int sickDomators = 0;
	int reservedSpace = 0;

	int power = 0;
	float happiness = 0.0f;

	bool connectedToPower = false;
	bool addedNewDomators = false;
	bool up_people = false;
	bool epidemic = false;
	bool informationAboutEpidemic = false;

	void SickPeopleEvent();

public:
	House() = default;
	House(const unsigned int height, const
		sf::Texture & texture, const TileSpecialise tileSpecialise, const std::vector<Frames> & frames,
		float population);

	virtual std::unique_ptr<SmallTile> clone() const override;

	virtual void Update(float elapsedTime) override;
	virtual void Destroy() override;

	void AddNewResidents(int residents);
	int UpdatePopulationHouse(int newHouseholdMembers);
	int SickPeopleToHospitalProcess();
	void ForceEpidemic();

	virtual void UpdateInformation() override;

	void SetInformationAboutEpidemic(bool informationAboutEpidemic);

	float GetHappiness() const;
	int GetMaxPopOnLvl() const;
	int GetHousehold() const;
	bool GetIsAddedNewDomators() const;
	bool GetIsEpidemic() const;
	int GetSickPeopleNr() const;
	bool GetInformationAboutEpidemic() const;
};

#endif // !House_hpp