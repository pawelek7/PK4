#include "Vehicle.h"

#pragma region Constructors

Vehicle::Vehicle(VehicleType vehicleType, int vehicleSpeed)
	:vehiclePhysics(2.0f, vehicleSpeed), vehicleProcedure(&this->vehiclePhysics)
{
	this->vehicleType = vehicleType;
	vehicleProcedure.SetSearchDistance(4.0f);
	vehicleProcedure.SetTaegetDistance(4.0f);

	if (vehicleType == VehicleType::AMBULANCE)
	{
		this->textureVehicleManager.LoadAsset("ambulance", "Resources/Textures/ambulance.png");
		this->texture = this->textureVehicleManager.GetAsset("ambulance");
	}
	else if (vehicleType == VehicleType::FIRE_TRUCK)
	{
		this->textureVehicleManager.LoadAsset("fire_truck", "Resources/Textures/fire_truck.png");
		this->texture = this->textureVehicleManager.GetAsset("fire_truck");
	}
	else if (vehicleType == VehicleType::POLICE)
	{
		this->textureVehicleManager.LoadAsset("police", "Resources/Textures/police.png");
		this->texture = this->textureVehicleManager.GetAsset("police");
	}
	else if (vehicleType == VehicleType::CYVILIAN)
	{
		this->textureVehicleManager.LoadAsset("cyvil", "Resources/Textures/cyvil.png");
		this->texture = this->textureVehicleManager.GetAsset("cyvil");
	}
	else if (vehicleType == VehicleType::DELIVERY_VAN)
	{
		this->textureVehicleManager.LoadAsset("van", "Resources/Textures/van.png");
		this->texture = this->textureVehicleManager.GetAsset("van");
	}
	
	this->widthVehicle = texture.getSize().x / 8;
	this->heightVehicle = texture.getSize().y;

	this->vehicleLook.setTexture(texture);
	this->vehicleLook.setTextureRect(sf::IntRect(0, 0, this->widthVehicle, this->heightVehicle));


	this->vehicleLook.setOrigin(this->widthVehicle * 0.5f , this->heightVehicle * 0.5f);
}

Vehicle::~Vehicle()
{

}

#pragma endregion

#pragma region Class_Methods

float Vehicle::CalculateRotation(float date)
{
	return 180.0f * date * M_1_PI;
}

void Vehicle::DrawVehicle(sf::RenderTarget * target)
{
	target->draw(vehicleLook);
}

void Vehicle::UpdateVehicle(float elapsedTime)
{
	sf::Vector2f force = this->vehicleProcedure.Calculate(elapsedTime);
	this->vehiclePhysics.SetForce(force);
	this->vehiclePhysics.UpdateVehiclePhysics(elapsedTime);

	this->vehicleLook.setPosition(this->vehiclePhysics.GetPosition());

	float angle = this->CalculateRotation(std::atan2(this->vehiclePhysics.GetDirection().y, this->vehiclePhysics.GetDirection().x));

	if (angle >= 0.0f)
	{
		angle = 360.0f - angle;
	}
	else
	{
		angle -= angle;
	}

	int i = static_cast<int>((angle + 22.5f) / 45.0f) % 8;
	this->vehicleLook.setTextureRect(sf::IntRect(i*widthVehicle, 0, this->widthVehicle, this->heightVehicle));
}

#pragma endregion

#pragma region Setters

void Vehicle::SetBuildingOwner(Structure *buildingOwner)
{
	this->buildingOwner = buildingOwner;
}

#pragma endregion

#pragma region Getters

VehiclePhysics & Vehicle::GetVehiclePhysics()
{
	return this->vehiclePhysics;
}

const VehiclePhysics & Vehicle::GetVehiclePhysics() const
{
	return this->vehiclePhysics;
}

void Vehicle::ChangeVehicleSpeed(int speed)
{
	this->vehiclePhysics.SetSpeed(speed);
}

VehicleProcedure & Vehicle::GetVehicleProcedure()
{
	return this->vehicleProcedure;
}

sf::FloatRect Vehicle::GetGlobalboundsOfVehicle() const
{
	return this->vehicleLook.getGlobalBounds();
}

Structure * Vehicle::GetBuildingOwner()
{
	return this->buildingOwner;
}

const Structure * Vehicle::GetBuildingOwner() const
{
	return this->buildingOwner;
}

sf::Sprite Vehicle::GetVehicleSprite()
{
	return this->vehicleLook;
}

#pragma endregion