#ifndef MovableDisaster_hpp
#define MovableDisaster_hpp

#include "Disaster.h"

class MovableDisaster : public Disaster
{
protected:
	int disasterSpeed = 100;
	int disasterDirection = 1;

	bool moveUp = true;
	bool moveDown = true;
	bool moveLeft = true;
	bool moveRight = true;

	sf::Vector2f actualPositionDisaster = sf::Vector2f(0.0f, 0.0f);
	
	void ReverseDisaster(int direction);
	void UpdateActualCoordinates();
	void ResetMovement();

public:
	MovableDisaster() = default;
	MovableDisaster(const sf::Texture & texture, const std::vector<Frames> & frames, DisasterType disasterType);
	virtual ~MovableDisaster() = default;

	void SetDisasterMovableSpeed(int speed);
	void SetDisasterMovableLifeTime(int lifeTime);

	int GetDisasterMovableDirection() const;
	sf::FloatRect GetDisasterMovableGlobalBounds() const;
	sf::Vector2i GetDisasterMovableCoordinates() const;
	sf::Vector2f GetDisasterMovablePosition() const;
};

#endif