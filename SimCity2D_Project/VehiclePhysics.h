#ifndef VehiclePhysics_hpp
#define VehiclePhysics_hpp

#include <SFML/Graphics.hpp>

#include <cmath>
#include <limits>
#include <algorithm>
#include <numeric>

#include "Mathematic.h"

class VehiclePhysics : public Mathematic
{
	float weight = 0.0f;
	float speed = 0.0f;
	float force = 0.0f;
	float rotation = 0.0f;

	sf::Vector2f position = sf::Vector2f(0, 0);
	sf::Vector2f direction = sf::Vector2f(0, 0);
	sf::Vector2f side = sf::Vector2f(0, 0);
	sf::Vector2f velocity = sf::Vector2f(0, 0);
	sf::Vector2f accForce = sf::Vector2f(0, 0);

public:
	VehiclePhysics() = default;
	VehiclePhysics(float weight, float speed, float force = std::numeric_limits<float>::max(), float rotation = std::numeric_limits<float>::max());
	virtual ~VehiclePhysics() = default;

	void UpdateVehiclePhysics(float elapsedTime);
	void Reset();

	//setters
	void SetForce(const sf::Vector2f & force);
	void SetPosition(const sf::Vector2f & position);
	void SetDirection(const sf::Vector2f & direction);
	void SetSpeed(float speed);

	//getters
	const sf::Vector2f GetDirection() const;
	const sf::Vector2f & GetPosition() const;
	const sf::Vector2f & GetVelocity() const;
	
	float GetWeight() const;
	float GetSpeed() const;
	float GetForce() const;
};

#endif // !VehiclePhysics_hpp
