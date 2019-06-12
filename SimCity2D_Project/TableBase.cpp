#include "TableBase.h"

#pragma Constructors

TableBase::TableBase(std::shared_ptr<AssetsOfGame> ptrGame, int sizeMap)
{
	this->ptrGame = ptrGame;

	this->centre = sf::Vector2f(sizeMap, sizeMap * 0.5);
	this->centre *= float(TILE_SIZE);
}

#pragma endregion

#pragma region Setters

void TableBase::SetIsTableOpen(bool tableOpen)
{
	this->tableOpen = tableOpen;
}

#pragma endregion

#pragma region Getters

bool TableBase::GetIsTableOpnen() const
{
	return this->tableOpen;
}

#pragma endregion