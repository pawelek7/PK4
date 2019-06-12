#ifndef PoliceStation_hpp
#define PoliceStation_hpp

#include "Structure.h"

class PoliceStation : public Structure
{
public:
	struct Prisoner
	{
		ID idPrisoner;
		int daysOfDetention;
		bool isFree;
	};

private:
	IDvector<Prisoner*> prisonersVector;
	Prisoner *prisoner = nullptr;

	int policemen = 0;
	int maxPolicemen = 15;
	int policeDepartmentStructure = 10000;
	float policeDepartmentPercentage = 0.0f;
	int prisoners = 0;
	int maxPrisoners = 10;

public:
	PoliceStation() = default;
	PoliceStation(const unsigned int height, const sf::Texture & texture, const TileSpecialise, const std::vector<Frames> & frames);
	virtual ~PoliceStation();

	PoliceStation & operator++();
	PoliceStation operator++(int);

	virtual std::unique_ptr<SmallTile> clone() const override;

	void BuildPoliceStation();
	void InitializePoliceStationParameters(IDvector<Prisoner*> & prisonersVector, int policemen, int maxPolicemen,
		int policeDepartmentStructure, float policeDepartmentPercenatge, int prisoners, int maxPrisoners);
	void NewDayInPoliceStation();
	int UpdatePolicemenPopulation(int newPolicemen);
	virtual void Update(float elapsedTime) override;

	//setters
	void SetPoliceDepartmentPercentage(float policeDepartmentPercentage);

	//getters
	int GetMaxPolicemen() const;
	int GetPoliceDepartment() const;
	float GetPoliceDepartmentPercenatge() const;
	IDvector<Prisoner*> & GetPrisonersVector();
	int GetPolicemen() const;
	int GetPrisoners() const;
	int GetMaxPrisoners() const;
};

#endif // !PoliceStation_hpp
