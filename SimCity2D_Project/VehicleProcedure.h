#ifndef VehicleProcedure_hpp
#define VehicleProcedure_hpp

#include "VehiclePhysics.h"
#include "Route.h"
#include "Mathematic.h"

class VehicleProcedure : public Mathematic
{
	VehiclePhysics *vehiclePhysics = nullptr;
	Route route;

	float searchDist = EPSILON;
	float driveDist = EPSILON;
	float targetDist = MAX_FLOAT;

	sf::Vector2f destinationTarget = sf::Vector2f(0, 0);

	sf::Vector2f FollowCreatedRoute();
	sf::Vector2f Drive(sf::Vector2f destinationTarget);
	sf::Vector2f Search(sf::Vector2f destinationTarget);
	sf::Vector2f NearDestinationTarget(sf::Vector2f  destinationTarget);
	sf::Vector2f VehicleSpeedToForce(const sf::Vector2f & velocity, float elapsedTime);

public:
	VehicleProcedure() = default;
	VehicleProcedure(VehiclePhysics* vehiclePhysics);
	virtual ~VehicleProcedure();

	sf::Vector2f Calculate(float elapsedTime);

	//setters
	void SetDestinationTarget(const sf::Vector2f & destinationTarget);
	void SetRoute(Route route);
	void SetSearchDistance(float distance);
	void SetDriveDistance(float distance);
	void SetTaegetDistance(float distance);

	//getters
	const Route & GetRoute() const;
};

#endif // !VehicleProcedure_hpp