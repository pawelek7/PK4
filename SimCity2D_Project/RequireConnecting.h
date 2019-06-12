#ifndef RequireConnecting_hpp
#define RequireConnecting_hpp

#include "SmallTile.h"

class RequireConnecting : public SmallTile
{
protected:
	int height = 0;

public:
	RequireConnecting() = default;
	RequireConnecting(const sf::Texture & texture, TileSpecialise tileSpecialise, const std::vector<Frames> & frames, int height);
	virtual ~RequireConnecting() = default;

	virtual std::unique_ptr<SmallTile> clone() const override;

	void InitializeRequireConnectingParameters(int height);

	//setters
	virtual void SetNewTileVariant(const SmallTile* neighbourhood[NEIGHBORING][NEIGHBORING]) override;

	//getters
	int GetHeight() const;
};

#endif