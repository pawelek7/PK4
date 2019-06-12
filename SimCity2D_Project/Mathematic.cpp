#include "Mathematic.h"

#pragma region Class_Methods

float Mathematic::SquaredDistanceTo(const sf::Vector2f& u, const sf::Vector2f & tmp) const
{
	sf::Vector2f i = tmp - u;

	return this->squaredNorm(i.x, i.y);
}

sf::Vector2f Mathematic::GetTruncatedVector(float maxNorm, sf::Vector2f tmp)
{
	float N = this->GetFloatNormalized(tmp);

	if (N > maxNorm)
	{
		return (maxNorm / N) * tmp;
	}

	return tmp;
}

sf::Vector2f Mathematic::GetTruncatEVector(sf::Vector2f tmp, float maxNorm)
{
	float N = this->GetFloatNormalized(tmp);

	if (N > maxNorm)
	{
		return tmp *= maxNorm / N;
	}

	return tmp;
}

#pragma endregion