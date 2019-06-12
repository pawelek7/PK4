#include "VehicleProcedure.h"

#pragma region Constructors

VehicleProcedure::VehicleProcedure(VehiclePhysics* vehiclePhysics)
{
	this->vehiclePhysics = vehiclePhysics;
}

VehicleProcedure::~VehicleProcedure()
{

}

#pragma endregion

#pragma region Class_Methods

sf::Vector2f VehicleProcedure::Calculate(float elapsedTime)
{
	return this->VehicleSpeedToForce(this->FollowCreatedRoute(), elapsedTime);
}

sf::Vector2f VehicleProcedure::FollowCreatedRoute()
{
	if (this->route.GetIsEmpty())
	{
		return sf::Vector2f(0, 0);
	}

	if (!this->route.GetIsFinish())
	{
		if (this->SquaredDistanceTo((sf::Vector2f)route.GetPosition(), this->vehiclePhysics->GetPosition()) < this->searchDist * this->searchDist)
		{
			this->route.PrepareNextPosition();
		}
		return this->Search((sf::Vector2f)this->route.GetPosition());
	}
	else
	{
		return this->NearDestinationTarget((sf::Vector2f)this->route.GetPosition());
	}
}

sf::Vector2f VehicleProcedure::VehicleSpeedToForce(const sf::Vector2f & velocity, float elapsedTime)
{
	return (velocity - this->vehiclePhysics->GetVelocity()) * this->vehiclePhysics->GetWeight() / elapsedTime;
}

sf::Vector2f VehicleProcedure::Search(sf::Vector2f destinationTarget)
{
	sf::Vector2f targetPosition = destinationTarget - vehiclePhysics->GetPosition();

	float distance = norm(targetPosition);

	if (!this->IsAlmostZero(distance))
	{
		return (vehiclePhysics->GetSpeed() / distance) * targetPosition;
	}

	return sf::Vector2f(0, 0);
}

sf::Vector2f VehicleProcedure::Drive(sf::Vector2f destinationTarget)
{
	sf::Vector2f targetPosition = this->vehiclePhysics->GetPosition() - this->destinationTarget;
	float distance = norm(targetPosition);

	if (distance < this->targetDist)
	{
		if (this->IsAlmostZero(distance))
		{
			return sf::Vector2f(1.0f, 0.0f) * this->vehiclePhysics->GetSpeed();
		}
		else
		{
			return (this->vehiclePhysics->GetSpeed() / distance) * targetPosition;
		}
	}

	return sf::Vector2f(0, 0);
}

sf::Vector2f VehicleProcedure::NearDestinationTarget(sf::Vector2f  destinationTarget)
{
	sf::Vector2f targetPosition = destinationTarget - this->vehiclePhysics->GetPosition();

	float distance = norm(targetPosition);

	if (!this->IsAlmostZero(distance))
	{
		float speed = std::min(1.0f, distance / this->targetDist) * this->vehiclePhysics->GetSpeed();
		return (speed / distance) * targetPosition;
	}
	return sf::Vector2f(0, 0);
}

#pragma endregion

#pragma region Setters

void VehicleProcedure::SetDestinationTarget(const sf::Vector2f & destinationTarget)
{
	this->destinationTarget = destinationTarget;
}

void VehicleProcedure::SetRoute(Route route)
{
	this->route = std::move(route);
}

void VehicleProcedure::SetSearchDistance(float distance)
{
	this->searchDist = distance;
}

void VehicleProcedure::SetDriveDistance(float distance)
{
	this->driveDist = distance;
}

void VehicleProcedure::SetTaegetDistance(float distance)
{
	this->targetDist = distance;
}

#pragma endregion

#pragma region Getters

const Route & VehicleProcedure::GetRoute() const
{
	return this->route;
}

#pragma endregion