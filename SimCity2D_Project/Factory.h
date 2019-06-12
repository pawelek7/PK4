#ifndef Factory_hpp
#define Factory_hpp

#include "Structure.h"

class Factory : public Structure
{
	int workers = 0;
	int maxWorkersPerLvl = 10;
	int storedGoods = 100;
	int vehicleCargo = 10;
	int maxGoodsStorage = 1000;

public:
	Factory() = default;
	Factory(const unsigned int height, const
		sf::Texture & texture, const TileSpecialise tileSpecialise, const std::vector<Frames> & frames);
	virtual ~Factory();

	virtual std::unique_ptr<SmallTile> clone() const override;

	virtual void Update(float elapsedTime) override;
	void ProduceGoods();
	void NewFactoryDay();
	bool CanDeliverGoods();
	int UpdateWorkersPopulation(int newEmployees);
	void InitializeFactoryParameters(int workers, int maxWorkersPerLvl, int storedGoods, int vehicleCargo, int maxGoodsStorage);

	//getters
	int GetGoodsAmounst() const;
	int GetWorkersAmount() const;
	int GetMaxWorkersPerLvl() const;
	int GetVehicleCargo() const;
	int GetMaxGoodsStorage() const;
	int GetDeliveryAmount();
};

#endif // !Factory_hpp
