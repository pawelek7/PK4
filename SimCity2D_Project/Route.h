#ifndef Route_hpp
#define Route_hpp

#include <SFML/Graphics.hpp>

#include <vector>

class Route
{
	std::vector<sf::Vector2i> xyVector;

	int iterator = 0;
	bool looped = false;

public:
	Route() = default;
	Route(std::vector<sf::Vector2i> xyVector, bool looped = false);
	virtual ~Route() = default;

	void PrepareNextPosition();
	const std::vector<sf::Vector2i> GetAllPositons() const;

	//getters
	sf::Vector2i GetPosition() const;
	sf::Vector2i GetPreviousPosition() const;
	bool GetIsFinish() const;
	bool GetIsEmpty() const;
};

#endif // !Route_hpp
