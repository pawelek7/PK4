#ifndef Factory_hpp
#define Factory_hpp

#include "Structure.h"

class Factory : public Structure
{
	int workers = 0;
	int maxWorkersPerLvl = 10;
	float production = 0.0f;

	int storedGoods = 10000;
	int vehicleCargo = 10;


public:
	Factory() = default;
	Factory(const unsigned int height, const
		sf::Texture & texture, const TileSpecialise tileSpecialise, const std::vector<Frames> & frames);

	virtual std::unique_ptr<SmallTile> clone() const override;

	virtual void Update(float elapsedTime) override;
	virtual void Destroy() override;

	virtual void UpdateInformation() override;

	bool CanDeliverGoods();
	int UpdateWorkersPopulation(int newEmployees);

	int GetGoodsAmounst() const;
	int GetWorkersAmount() const;
	int GetDeliveryAmount();
	std::string GetInformationAboutVehicle();
};

#endif // !Factory_hpp
