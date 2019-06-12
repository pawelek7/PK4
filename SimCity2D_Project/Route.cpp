#include "Route.h"

#pragma region Constructors

Route::Route(std::vector<sf::Vector2i> xyVector, bool looped)
{
	this->xyVector = xyVector;
	this->looped = looped;
}

#pragma endregion

#pragma region Class_Methods

void Route::PrepareNextPosition()
{
	this->iterator++;
	if (looped == true && this->iterator >= this->xyVector.size())
	{
		this->iterator = 0;
	}
}

#pragma endregion

#pragma region Getters

sf::Vector2i Route::GetPosition() const
{
	return this->xyVector[iterator];
}

sf::Vector2i Route::GetPreviousPosition() const
{
	if (xyVector.size() == 0)
		return sf::Vector2i();

   	return this->xyVector.back();
}

const std::vector<sf::Vector2i> Route::GetAllPositons() const
{
	return this->xyVector;
}

bool Route::GetIsFinish() const
{
	return !looped && this->iterator == (this->xyVector.size() - 1);
}

bool Route::GetIsEmpty() const
{
	return xyVector.empty();
}

#pragma endregion