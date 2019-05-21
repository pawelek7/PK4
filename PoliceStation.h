#ifndef PoliceStation_hpp
#define PoliceStation_hpp

#include "Structure.h"

class PoliceStation : public Structure
{

public:
	PoliceStation() = default;
	PoliceStation(const unsigned int height, const sf::Texture & texture, const TileSpecialise, const std::vector<Frames> & frames);

	virtual std::unique_ptr<SmallTile> clone() const override;

	virtual void Update(float elapsedTime) override;
	virtual void Destroy() override;
	virtual void UpdateInformation() override;
};

#endif // !PoliceStation_hpp
