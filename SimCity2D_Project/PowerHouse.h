#ifndef PowerHouse_hpp
#define PowerHouse_hpp

#include "Structure.h"
#include "PathFinding.h"

class PowerHouse : public Structure
{
	int producedEnergy = 500;
	int maxEnergyStorage = 1000;
	int employess = 0;
	int maxEmployess = 20;
	bool canShareEnergy = false;

public:
	PowerHouse() = default;
	PowerHouse(const unsigned int height, const sf::Texture & texture,
		const std::vector<Frames> & frames);
	virtual ~PowerHouse();

	virtual std::unique_ptr<SmallTile> clone() const override;

	PowerHouse & operator++ ();
	PowerHouse operator++ (int);
	PowerHouse & operator--();
	PowerHouse operator--(int);

	int UpdateWorkersPopulation(int workers);
	int GetMaxEnergyStorage() const;
	int GetMaxEmployess() const;
	virtual void Update(float elapsedTime) override;
	void NewPowerHouseDay();
	void InitializePowerHouseParameters(int producedEnergy, int maxEnergyStorage, int employess, int maxEmployess, bool canShareEnergy);

	//setters
	void SetCanShareEnergy(bool canShareEnergy);

	//getters
	int GetEnergyAmount() const;
	bool GetCanShareEnergy() const;
	int GetEmployessAmount() const;
	int GetProducedEnergy() const;
	std::string GetProductionSharing() const;
	std::string GetEnergyProductionStatus() const;
};

#endif // !PowerHouse_hpp
