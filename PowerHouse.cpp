#include "PowerHouse.h"

#pragma region Constructors

PowerHouse::PowerHouse(const unsigned int height, const sf::Texture & texture,
	const std::vector<Frames> & frames) : Structure(height, TileSpecialise::POWER_HOUSE, texture, frames)
{
	this->hasEnergy = true;

	this->texture = texture;
	this->heightBuilding = height;
	this->tileSpecialise = tileSpecialise;
	this->typeOfTile = typeOfTile;
	this->sprite.setTexture(texture);
	this->sprite.setOrigin(sf::Vector2f(0.0f, TILE_SIZE*(height-1.5f)));

	this->frameSize = sf::IntRect(0, 0, 2*TILE_SIZE * 2, TILE_SIZE*height);
	this->UpdateAnimation(0.0f);

	tileData.level = 0;
	tileData.population = 0;
	tileData.tileSpecialise = TileSpecialise::POWER_HOUSE;
	tileData.texture_name = "unknown";
	tileData.height = 1;

	this->vehicle1 = new Vehicle(VehicleType::AMBULANCE);

	this->hasVehicle = false;

	vehicle1->SetBuildingOwner(this);

	this->key = 5;
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
		this->producedEnergy += this->employess;
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

void PowerHouse::Destroy()
{
	//... SOON
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

bool PowerHouse::GetCanShareEnergy() const
{
	return this->canShareEnergy;
}

int PowerHouse::GetEmployessAmount() const
{
	return this->employess;
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