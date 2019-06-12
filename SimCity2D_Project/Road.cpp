#include "Road.h"

#pragma region Constructors

Road::Road(const sf::Texture & texture, TileSpecialise tileSpecialise, const std::vector<Frames> & frames, int height)
	:RequireConnecting(texture, tileSpecialise, frames, height)
{
	this->height = height;
}

std::unique_ptr<SmallTile> Road::clone() const
{
	return std::make_unique<Road>(texture, tileSpecialise, frames, height);
}

#pragma endregion