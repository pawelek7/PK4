#include "VehiclePhysics.h"

#pragma region Constructors

VehiclePhysics::VehiclePhysics(float weight, float speed, float force, float rotation)
{
	this->weight = weight;
	this->speed = speed;
	this->force = force;
	this->rotation = rotation;
}

#pragma endregion

#pragma region Class_Merhods

void VehiclePhysics::UpdateVehiclePhysics(float elapsedTime)
{
	sf::Vector2f acceleration = this->GetTruncatedVector(force, this->accForce) / this->weight;

	velocity += acceleration * elapsedTime;
	velocity = this->GetTruncatEVector(velocity, speed);

	position += velocity * elapsedTime;

	if (!this->NearZero(velocity))
	{
		direction = this->GetVectorNormalized(velocity);
		side = this->GetOrthogonalVector(direction);
	}

	if (!this->NearZero(velocity))
	{
		this->direction = this->GetVectorNormalized(velocity);
		this->side = this->GetOrthogonalVector(this->direction);
	}
	
	this->Reset();
}

void VehiclePhysics::Reset()
{
	this->accForce = sf::Vector2f(0, 0);
}

#pragma endregion

#pragma region Setters

void VehiclePhysics::SetForce(const sf::Vector2f & force)
{
	this->accForce += force;
}

void VehiclePhysics::SetPosition(const sf::Vector2f & position)
{
	this->position = position;
}

void VehiclePhysics::SetDirection(const sf::Vector2f & direction)
{
	this->direction = direction;
}

void VehiclePhysics::SetSpeed(float speed)
{
	this->speed = speed;
}

#pragma endregion

#pragma region Getters

const sf::Vector2f & VehiclePhysics::GetPosition() const
{
	return this->position;
}

const sf::Vector2f VehiclePhysics::GetDirection() const
{
	return this->direction;
}

const sf::Vector2f & VehiclePhysics::GetVelocity() const
{
	return this->velocity;
}

float VehiclePhysics::GetWeight() const
{
	return this->weight;
}

float VehiclePhysics::GetSpeed() const
{
	return this->speed;
}

float VehiclePhysics::GetForce() const
{
	return this->force;
}

#pragma endregion