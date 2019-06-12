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
	int maxGoodsInShop = 100;

	bool emptyWarehouse = false;
	bool addedInformation = false;

public:
	Shop() = default;
	Shop(const unsigned int height, const sf::Texture & texture, const TileSpecialise, const std::vector<Frames> & frames);
	virtual ~Shop() = default;

	virtual std::unique_ptr<SmallTile> clone() const override;

	Shop & operator+(int);
	Shop & operator++();
	Shop operator++(int);
	Shop & operator--();
	Shop  operator--(int);

	virtual void Update(float elapsedTime) override;
	int UpdateWorkersPopulation(int newEmployees);
	void DeliveredGoods(int goodsAmount);
	void EmptyTheMoney();
	void NewDayInShop();
	void InitializeShopParameters(int employess, int maxEmployeesOnLvl, int customers, int maxCustomersPerLvl,
		int goods, int maxGoodsInShop, bool emptyWarehouse, bool addedInformation);

	//setters
	void SetAddedInformation(bool addedInformation);

	//getters
	int GetEmployessNr() const;
	int GetMaxEmployessOnLvl() const;
	int GetMaxGoodsInShop() const;
	int GetActualAmountOfCustomets() const;
	int GetGoodsAmount() const;
	int GetMaxCustomersOnLvl() const;
	int GetCustomers() const;
	bool GetEmptyWarehouse() const;
	bool GetAddedInformation() const;
	bool GetIsClosedToday() const;
};

#endif // !Shop_hpp