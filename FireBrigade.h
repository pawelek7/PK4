#ifndef FireBrigade_hpp
#define FireBrigade_hpp

#include "Structure.h"

class FireBrigade : public Structure
{


public:
	FireBrigade() = default;
	FireBrigade(const unsigned int height, const sf::Texture & texture, const TileSpecialise, const std::vector<Frames> & frames);

	virtual std::unique_ptr<SmallTile> clone() const override;
	void BuildFireBrigade();
	virtual void Update(float elapsedTime) override;
	virtual void Destroy() override;
	virtual void UpdateInformation() override;
};

#endif // !FireBrigade_hpp
