#ifndef Shop_hpp
#define Shop_hpp

#include "Structure.h"

class Shop : public Structure
{
	int employees = 0;
	int MaxEmployeesPerLvl = 10;
	int customers = 0;
	int maxCustomersPerLvl = 4;

	int goods = 10;
	int generatedMoney = 0;

	bool emptyWarehouse = false;
	bool addedInformation = false;

public:
	Shop() = default;
	Shop(const unsigned int height, const sf::Texture & texture, const TileSpecialise, const std::vector<Frames> & frames);

	virtual void Update(float elapsedTime) override;
	virtual void Destroy() override;

	virtual void UpdateInformation() override;
	virtual std::unique_ptr<SmallTile> clone() const override;

	int UpdateWorkersPopulation(int newEmployees);
	void DeliveredGoods(int goodsAmount);

	void SetAddedInformation(bool addedInformation);

	int GetEmployessNr() const;
	int GetActualAmountOfCustomets() const;
	int GetGoodsAmount() const;
	bool GetEmptyWarehouse() const;
	bool GetAddedInformation() const;
};

#endif // !Shop_hpp
