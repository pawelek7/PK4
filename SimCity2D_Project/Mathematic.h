#ifndef Mathematic_hpp
#define Mathematic_hpp

#include <SFML/Graphics.hpp>

#include <numeric>

#define EPSILON std::numeric_limits<float>::epsilon();
#define MAX_FLOAT std::numeric_limits<float>::max();

class Mathematic 
{
public:
	Mathematic() = default;
	virtual ~Mathematic() = default;

	inline bool NearZero(sf::Vector2f xy)
	{
		return GetIsABSnearZero(L2norm(xy.x, xy.y));
	}

	inline float L2norm(float x, float y)
	{
		return x * x + y * y;
	}

	inline bool GetIsABSnearZero(float x)
	{
		return std::abs(x) < EPSILON;
	}

	inline sf::Vector2f GetVectorNormalized(sf::Vector2f tmp)
	{
		return sf::Vector2f(tmp.x / GetFloatNormalized(tmp), tmp.y / GetFloatNormalized(tmp));
	}

	inline float GetFloatNormalized(sf::Vector2f tmp)
	{
		return std::sqrt(L2norm(tmp.x, tmp.y));
	}

	inline sf::Vector2f GetOrthogonalVector(sf::Vector2f xy)
	{
		return sf::Vector2f(-xy.y, xy.x);
	}

	inline bool IsAlmostZero(float date)
	{
		return std::abs(date) < EPSILON;
	}

	inline bool AlmostEquals(float date_1, float date_2)
	{
		return this->IsAlmostZero(date_1 - date_2);
	}

	inline float norm(sf::Vector2f tmp)
	{
		return std::sqrt(squaredNorm(tmp.x, tmp.y));
	}

	inline float squaredNorm(float x, float y) const
	{
		return x * x + y * y;
	}

	float SquaredDistanceTo(const sf::Vector2f& u, const sf::Vector2f & tmp) const;

	//getters
	sf::Vector2f GetTruncatedVector(float maxNorm, sf::Vector2f tmp);
	sf::Vector2f GetTruncatEVector(sf::Vector2f tmp, float maxNorm);
};

#endif // !Mathematic_hpp
