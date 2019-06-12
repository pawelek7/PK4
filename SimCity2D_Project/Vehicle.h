#ifndef Vehicle_hpp
#define Vehicle_hpp

#include <SFML/Graphics.hpp>

#include <stack>
#include <cmath>
#include <map>

#include "Structure.h"
#include "VehiclePhysics.h"
#include "VehicleProcedure.h"
#include "AssetManager.h"
#include "NoCopyNoMove.h"

#define M_1_PI 0.318309886183790671538

class Structure;

class Vehicle 
{
public:
	enum class VehicleType
	{
		VOID = 0, AMBULANCE = 1, DELIVERY_VAN = 2, FIRE_TRUCK = 3, CYVILIAN = 4, POLICE = 5
	};

private:
	AssetManager<sf::Texture> textureVehicleManager;

	VehicleType vehicleType = VehicleType::VOID;

	int widthVehicle = 0, heightVehicle = 0;

	Structure *buildingOwner = nullptr;
	VehiclePhysics vehiclePhysics;
	VehicleProcedure vehicleProcedure;

	std::map<int, sf::Texture> vehiclePositions;

	sf::Texture texture;
	sf::Sprite vehicleLook;

	float CalculateRotation(float date);

public:
	Vehicle() = default;
	Vehicle(VehicleType vehicleType,int vehicleSpeed = 50);
	virtual ~Vehicle();
	
	void DrawVehicle(sf::RenderTarget * target);
	void UpdateVehicle(float elapsedTime);

	void SetBuildingOwner(Structure *buildingOwner);
	void ChangeVehicleSpeed(int speed);

	//getters
	VehiclePhysics & GetVehiclePhysics();
	const VehiclePhysics & GetVehiclePhysics() const;
	VehicleProcedure & GetVehicleProcedure();

	sf::FloatRect GetGlobalboundsOfVehicle() const;
	sf::Sprite GetVehicleSprite();

	Structure *GetBuildingOwner();
	const Structure *GetBuildingOwner() const;
};

#endif // !Vehicle_hpp