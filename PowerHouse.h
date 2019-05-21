#ifndef PowerHouse_hpp
#define PowerHouse_hpp

#include "Structure.h"
#include "PathFinding.h"

class PowerHouse : public Structure
{
	int producedEnergy = 50;
	int maxEnergyStorage = 100;
	int employess = 0;
	int maxEmployess = 20;

	bool canShareEnergy = false;

public:
	PowerHouse() = default;
	PowerHouse(const unsigned int height, const sf::Texture & texture,
		const std::vector<Frames> & frames);
	virtual ~PowerHouse();

	PowerHouse& operator++ ();
	PowerHouse operator++ (int);
	PowerHouse& operator--();
	PowerHouse operator--(int);

	virtual std::unique_ptr<SmallTile> clone() const override;

	int UpdateWorkersPopulation(int workers);

	virtual void Update(float elapsedTime) override;
	virtual void Destroy() override;

	void SetCanShareEnergy(bool canShareEnergy);

	int GetEnergyAmount() const;
	bool GetCanShareEnergy() const;
	int GetEmployessAmount() const;
	int GetProducedEnergy() const;
};

#endif // !PowerHouse_hpp
