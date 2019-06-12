#ifndef Road_hpp
#define Road_hpp

#include "RequireConnecting.h"

class Road : public RequireConnecting
{
public:
	Road() = default;
	Road(const sf::Texture & texture, TileSpecialise tileSpecialise, const std::vector<Frames> & frames, int height);
	virtual ~Road() = default;

	virtual std::unique_ptr<SmallTile> clone() const  override;
};

#endif // !Road_hpp