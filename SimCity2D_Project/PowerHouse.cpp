#include "PowerHouse.h"

#pragma region Constructors

PowerHouse::PowerHouse(const unsigned int height, const sf::Texture & texture,
	const std::vector<Frames> & frames) : Structure(height, TileSpecialise::POWER_HOUSE, texture, frames)
{
	this->hasEnergy = true;
	this->cityOrdinancesStructure = 1000;

	this->texture = texture;
	this->heightBuilding = height;
	this->tileSpecialise = tileSpecialise;
	this->typeOfTile = typeOfTile;
	this->sprite.setTexture(texture);
	this->sprite.setOrigin(sf::Vector2f(0.0f, TILE_SIZE*(height-1.5f)));
	this->frameSize = sf::IntRect(0, 0, 2*TILE_SIZE * 2, TILE_SIZE*height);
	this->UpdateAnimation(0.0f);

	this->vehicle1 = new Vehicle(Vehicle::VehicleType::AMBULANCE);
	this->hasVehicle = false;
	vehicle1->SetBuildingOwner(this);
}

PowerHouse::~PowerHouse()
{
}

std::unique_ptr<SmallTile> PowerHouse::clone() const
{
	return std::make_unique<PowerHouse>(heightBuilding, texture, frames);
}

#pragma endregion

#pragma region Operators

PowerHouse & PowerHouse::operator++()
{
	if (this->producedEnergy < this->maxEnergyStorage)
	{
		if (this->canShareEnergy == false)
		{
			this->canShareEnergy = true;
		}
		this->producedEnergy += this->employess * 10;
	}

	return *this;
}

PowerHouse PowerHouse::operator++(int)
{
	PowerHouse moreEnergy(*this);
	++(*this);
	return moreEnergy;
}

PowerHouse & PowerHouse::operator--()
{
	if (this->producedEnergy > 0)
	{
		this->producedEnergy--;
	}

	if (producedEnergy <= 0)
	{
		this->canShareEnergy = false;
	}

	return *this;
}

PowerHouse PowerHouse::operator--(int)
{
	PowerHouse lessEnergy(*this);
	--(*this);
	return lessEnergy;
}

#pragma endregion

#pragma region Class_Methods

void PowerHouse::Update(float elapsedTime)
{
	if (this->hasVehicle)
	{
		this->vehicle1->UpdateVehicle(elapsedTime);
	}

	if (this->producedEnergy > 0)
	{
		this->canShareEnergy = true;
	}
}

void PowerHouse::NewPowerHouseDay()
{
	if (this->cityOrdinancesPercentage < this->employess + (this->maxEnergyStorage - this->producedEnergy) / 100.0f)
	{
		this->strike = true;
	}
	else
	{
		this->strike = false;
	}
}

void PowerHouse::InitializePowerHouseParameters(int producedEnergy, int maxEnergyStorage, int employess, int maxEmployess, bool canShareEnergy)
{
	this->producedEnergy = producedEnergy;
	this->maxEnergyStorage = maxEnergyStorage;
	this->employess = employess;
	this->maxEmployess = maxEmployess;
	this->canShareEnergy = canShareEnergy;
}

int PowerHouse::UpdateWorkersPopulation(int newEmployess)
{
	int overPeople = 0;

	if (this->employess < this->maxEmployess)
	{
		this->employess += newEmployess;

		if (this->employess > this->maxEmployess)
		{
			overPeople = this->employess - this->maxEmployess;
			this->employess -= overPeople;
		}
		return overPeople;
	}
	return newEmployess;
}

#pragma endregion

#pragma region Setters

void PowerHouse::SetCanShareEnergy(bool canShareEnergy)
{
	this->canShareEnergy = canShareEnergy;
}

#pragma endregion

#pragma region Getters

std::string PowerHouse::GetProductionSharing() const
{
	if (this->canShareEnergy == true)
	{
		return "Transmission";
	}

	return "Overload";
}

std::string PowerHouse::GetEnergyProductionStatus() const
{
	if (this->producedEnergy > this->maxEnergyStorage)
	{
		return "Above normal";
	}
	else if (this->producedEnergy > 200)
	{
		return "Normal";
	}

	return "Bad";
}

bool PowerHouse::GetCanShareEnergy() const
{
	return this->canShareEnergy;
}

int PowerHouse::GetEmployessAmount() const
{
	return this->employess;
}

int PowerHouse::GetMaxEmployess() const
{
	return this->maxEmployess;
}

int PowerHouse::GetMaxEnergyStorage() const
{
	return this->maxEnergyStorage;
}

int PowerHouse::GetProducedEnergy() const
{
	float percentage = (float)producedEnergy / (float)maxEnergyStorage;
	return percentage * 100;
}

int PowerHouse::GetEnergyAmount() const
{
	return this->producedEnergy;
}
#pragma endregion