#ifndef FireBrigade_hpp
#define FireBrigade_hpp

#include "Structure.h"

class FireBrigade : public Structure
{
	int firefFighters = 0;
	int maxFirefighters = 10;
	int fireDepartmentStructure = 10000;
	float fireDepartmentPercentage = 0.0f;
	int extinguishedFires = 0;

public:
	FireBrigade() = default;
	FireBrigade(const unsigned int height, const sf::Texture & texture, const TileSpecialise, const std::vector<Frames> & frames);
	virtual ~FireBrigade();

	virtual std::unique_ptr<SmallTile> clone() const override;

	FireBrigade & operator++();
	FireBrigade operator++(int);

	int UpdateFirefightersPopulation(int newFirefighter);
	void NewDayFireBrigade();
	void InitializeFireBrigadeParameters(int fireFighters, int maxFireFighters, int fireDepartamentStructure, int fireDepartamentPercentage, int extinguishedFires);
	void BuildFireBrigade();
	virtual void Update(float elapsedTime) override;

	//setters
	void SetFireDepartmentPercentage(float fireDepartmentPercentage);

	//getters
	int GetFireDepartment() const;
	int GetFirefightersAmount() const;
	int GetMaxFireFighters() const;
	int GetExtinguishedFires() const;
	float GetFireDepartamentPercentage() const;
};

#endif // !FireBrigade_hpp
