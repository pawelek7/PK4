#ifndef Road_hpp
#define Road_hpp

#include "RequireConnecting.h"

class Road : public RequireConnecting
{
	int height = 0;

public:
	Road() = default;
	Road(const sf::Texture & texture, TileSpecialise tileSpecialise, const std::vector<Frames> & frames, int height);

	virtual std::unique_ptr<SmallTile> clone() const  override;
};

#endif // !Road_hpp