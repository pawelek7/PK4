#ifndef Tornado_hpp
#define Tornado_hpp

#include "Disaster.h"

class Tornado : public Disaster
{
	int tornadoDirectionLength = 0;
	int tornadoSpeed = 100;
	int tornadoDirection = 1;

	bool moveUp = true;
	bool moveDown = true;
	bool moveLeft = true;
	bool moveRight = true;

	sf::Vector2f tornadoPosition = sf::Vector2f(0, 0);

	void UpdateActualTornadoXY();
	void ReverseThornado(int e_direction);
	void ResetMovement();

public:
	Tornado() = default;
	Tornado(const sf::Texture & texture, const std::vector<Frames> & frames);
	virtual ~Tornado() = default;

	virtual void UpdateDisaster(float elapsedTime) override;

	void ThornadoIntelligence(float elapsedTime);
	void InitializeTornado();

	void SetTornadoSpeed(int speed);
	void SetTornadoLifeTime(int lifeTime);

	int GetTornadoDirection() const;

	sf::Vector2f GetTornadoSpritePosition() const;
	sf::FloatRect GetTornadoGlobalBounds() const;
	sf::Vector2i GetTornadoCoordinates() const;
	sf::Vector2f GetTornadoPosition() const;
};

#endif // !Tornado_hpp
