#include "RequireConnecting.h"

#pragma region Constructors

RequireConnecting::RequireConnecting(const sf::Texture & texture, TileSpecialise tileSpecialise,
	const std::vector<Frames> & frames, int height)
	:SmallTile(height, texture, TypeOfTile::REQUIRES_CONNECTION, tileSpecialise, frames)
{
	this->height = height;
}

std::unique_ptr<SmallTile> RequireConnecting::clone() const
{
	return std::make_unique<RequireConnecting>(texture, tileSpecialise, frames, height);
}

#pragma endregion

#pragma region Class_Methods

void RequireConnecting::SetNewTileVariant(const SmallTile* neighbourhood[NEIGHBORING][NEIGHBORING])
{
	sf::IntRect rect(0, 0, 2 * TILE_SIZE, height * TILE_SIZE);

	if (neighbourhood[0][1]->GetIsRoad() && neighbourhood[1][0]->GetIsRoad() &&
		neighbourhood[2][1]->GetIsRoad() && neighbourhood[1][2]->GetIsRoad())
		rect.top = height * TILE_SIZE;
	else if (neighbourhood[0][1]->GetIsRoad() && neighbourhood[1][0]->GetIsRoad() && neighbourhood[2][1]->GetIsRoad())
		rect.top = height * TILE_SIZE * 2;
	else if (neighbourhood[0][1]->GetIsRoad() && neighbourhood[1][0]->GetIsRoad() && neighbourhood[1][2]->GetIsRoad())
		rect.top = height * TILE_SIZE * 3;
	else if (neighbourhood[0][1]->GetIsRoad() && neighbourhood[2][1]->GetIsRoad() && neighbourhood[1][2]->GetIsRoad())
		rect.top = height * TILE_SIZE * 4;
	else if (neighbourhood[1][0]->GetIsRoad() && neighbourhood[2][1]->GetIsRoad() && neighbourhood[1][2]->GetIsRoad())
		rect.top = height * TILE_SIZE * 5;
	else if (neighbourhood[0][1]->GetIsRoad() && neighbourhood[1][0]->GetIsRoad())
		rect.top = height * TILE_SIZE * 6;
	else if (neighbourhood[1][0]->GetIsRoad() && neighbourhood[2][1]->GetIsRoad())
		rect.top = height * TILE_SIZE * 7;
	else if (neighbourhood[2][1]->GetIsRoad() && neighbourhood[1][2]->GetIsRoad())
		rect.top = height * TILE_SIZE * 8;
	else if (neighbourhood[1][2]->GetIsRoad() && neighbourhood[0][1]->GetIsRoad())
		rect.top = height * TILE_SIZE * 9;
	else if ((neighbourhood[1][0]->GetIsRoad() || neighbourhood[1][2]->GetIsRoad()))
		rect.top = height * TILE_SIZE * 10;
	else if (neighbourhood[0][1]->GetIsVoltagePylon() && neighbourhood[1][0]->GetIsVoltagePylon() &&
		neighbourhood[2][1]->GetIsVoltagePylon() && neighbourhood[1][2]->GetIsVoltagePylon())
		rect.top = height * TILE_SIZE;
	else if (neighbourhood[0][1]->GetIsVoltagePylon() && neighbourhood[1][0]->GetIsVoltagePylon() && neighbourhood[2][1]->GetIsVoltagePylon())
		rect.top = height * TILE_SIZE * 2;
	else if (neighbourhood[0][1]->GetIsVoltagePylon() && neighbourhood[1][0]->GetIsVoltagePylon() && neighbourhood[1][2]->GetIsVoltagePylon())
		rect.top = height * TILE_SIZE * 3;
	else if (neighbourhood[0][1]->GetIsVoltagePylon() && neighbourhood[2][1]->GetIsVoltagePylon() && neighbourhood[1][2]->GetIsVoltagePylon())
		rect.top = height * TILE_SIZE * 4;
	else if (neighbourhood[1][0]->GetIsVoltagePylon() && neighbourhood[2][1]->GetIsVoltagePylon() && neighbourhood[1][2]->GetIsVoltagePylon())
		rect.top = height * TILE_SIZE * 5;
	else if (neighbourhood[0][1]->GetIsVoltagePylon() && neighbourhood[1][0]->GetIsVoltagePylon())
		rect.top = height * TILE_SIZE * 6;
	else if (neighbourhood[1][0]->GetIsVoltagePylon() && neighbourhood[2][1]->GetIsVoltagePylon())
		rect.top = height * TILE_SIZE * 7;
	else if (neighbourhood[2][1]->GetIsVoltagePylon() && neighbourhood[1][2]->GetIsVoltagePylon())
		rect.top = height * TILE_SIZE * 8;
	else if (neighbourhood[1][2]->GetIsVoltagePylon() && neighbourhood[0][1]->GetIsVoltagePylon())
		rect.top = height * TILE_SIZE * 9;
	else if ((neighbourhood[1][0]->GetIsVoltagePylon() || neighbourhood[1][2]->GetIsVoltagePylon()))
		rect.top = height * TILE_SIZE * 10;
	else
		rect.top = 0;


	sprite.setTextureRect(rect);
}

void RequireConnecting::InitializeRequireConnectingParameters(int height)
{
	this->height = height;
}

int RequireConnecting::GetHeight() const
{
	return this->height;
}

#pragma endregion