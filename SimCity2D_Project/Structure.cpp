#include "Structure.h"

#pragma region Constructors

Structure::Structure(const unsigned int heightBuilding, TileSpecialise tileSpecialise,
	const sf::Texture & texture, const std::vector<Frames> & frames, ID buildingID)
	:SmallTile(heightBuilding, texture, TypeOfTile::STRUCTURE, tileSpecialise, frames),
	buildingID(buildingID)
{
	this->structureType = TextureBuildManager::TextureType::HOUSE;

	if (vehicle1 == nullptr)
	{
		vehicle1 = new Vehicle(Vehicle::VehicleType::VOID);
	}
}

Structure::~Structure()
{
	if (vehicle1 != nullptr)
	{
		delete this->vehicle1;
		this->vehicle1 = nullptr;
	}

	if (this->driveToDestination != nullptr)
	{
		delete this->driveToDestination;
		this->driveToDestination = nullptr;
	}
}

std::unique_ptr<SmallTile> Structure::clone() const
{
	return std::make_unique<Structure>(heightBuilding, tileSpecialise, texture, frames, buildingID);
}

#pragma endregion

#pragma region Class_Methods

void Structure::Draw(sf::RenderWindow& window, float elapsedTime, sf::Shader *shaders, const sf::Vector2f & camera_position)
{

	if (selectionProcess == SelectionProcess::SELECTED)
	{
		sprite.setColor(sf::Color(135, 206, 250));
	}
	else
	{
		sprite.setColor(sf::Color(0xff, 0xff, 0xff));
	}

	this->ChangeFrame(this->versionOfBuilding);
	this->UpdateAnimation(elapsedTime);
	this->sprite.setTextureRect(this->currentSection);
	window.draw(this->sprite);
}

bool Structure::Interaction(const sf::Vector2f& position)
{
	if (SpriteClicked(sprite, position))
	{
		return true;
	}

	return false;
}

float Structure::RandomiseEvent(int from, int to)
{
	RandomEngine randomEngine;
	randomEngine.RandomiseEvent(from, to);

	return randomEngine.GetResult();
}

void Structure::InitializeStructureParameters(ID buildingID, VehicleVisible vehicleVisible, unsigned int actualLevel, unsigned int heightBuilding,
	int buildDays, float happiness, int propertyTaxesStructure, int cityOrdinancesStructure, int robberyCounter, float propertyTaxesPercentage,
	float cityOrdinancesPercentage, bool strike, bool thiefCaught, bool informationNoEnergy, bool informationThief, bool informationStrike,
	bool hasEnergy, bool buildedStructure, bool vehicleInUse, bool callBackVehicle, bool travelDestinationSuccess, bool structureOnFire,
	bool thiefInBuilding, bool hasVehicle)
{
	this->buildingID = buildingID;
	this->vehicleVisible = vehicleVisible;
	this->actualLevel = actualLevel;
	this->heightBuilding = heightBuilding;
	this->buildDays = buildDays;
	this->happiness = happiness;
	this->propertyTaxesStructure = propertyTaxesStructure;
	this->cityOrdinancesStructure = cityOrdinancesStructure;
	this->robberyCounter = robberyCounter;
	this->propertyTaxesPercentage = propertyTaxesPercentage;
	this->cityOrdinancesPercentage = cityOrdinancesPercentage;
	this->strike = strike;
	this->thiefCaught = thiefCaught;
	this->informationNoEnergy = informationNoEnergy;
	this->informationThief = informationThief;
	this->informationStrike = informationStrike;
	this->hasEnergy = hasEnergy;
	this->buildedStructure = buildedStructure;
	this->vehicleInUse = vehicleInUse;
	this->callBackVehicle = callBackVehicle;
	this->travelDestinationSuccess = travelDestinationSuccess;
	this->structureOnFire = structureOnFire;
	this->thiefInBuilding = thiefInBuilding;
	this->hasVehicle = hasVehicle;
}

void Structure::ProcessDriving(float elapsedTime)
{
	if (this->vehicleInUse == true)
	{
		if (this->callBackVehicle == false)
		{
			if (this->driveToDestination->MakeProgress() == DriveToDestination::DRIVING_PROCESS::DRIVING)
			{
				this->vehicle1->UpdateVehicle(elapsedTime);
			}
			else if (this->driveToDestination->MakeProgress() == DriveToDestination::DRIVING_PROCESS::AT_DESTINATION)
			{
				this->travelDestinationSuccess = true;
			//	std::cout << "Dojechalem" << std::endl;

				this->callBackVehicle = true;
				this->driveToDestination->BeginDrivingProcess(true);
			}
		}
		else
		{
			if (this->driveToDestination->MakeProgress() == DriveToDestination::DRIVING_PROCESS::DRIVING)
			{
				this->vehicle1->UpdateVehicle(elapsedTime);
			}
			else if (this->driveToDestination->MakeProgress() == DriveToDestination::DRIVING_PROCESS::AT_DESTINATION)
			{
				this->callBackVehicle = false;
				this->vehicleInUse = false;
			//	std::cout << "Wrocilem" << std::endl;

				this->rememberRoute = true;
			}

		}
	}
}

void Structure::DriveToBuildingStart(Structure *structure)
{
	if (this->vehicleInUse == false)
	{
		this->driveToDestination->ActivateProcedure(this, structure);
		this->driveToDestination->BeginDrivingProcess(false);

		if (this->driveToDestination->GetDrivingProcess() != DriveToDestination::DRIVING_PROCESS::DEFEAT)
		{
			this->vehicleInUse = true;
		}
	}
}

void Structure::ChangeTexture()
{
	if (this->GetTileSpecialise() == SmallTile::TileSpecialise::FIRE_BRIGADE)
	{
		if (this->buildedStructure == false)
		{
			this->textureName = "building";
		}
		else
		{
			this->textureName = "fire_station";
		}
	}
	else if (this->GetTileSpecialise() == SmallTile::TileSpecialise::HOSPITAL)
	{
		if (this->buildedStructure == false)
		{
			this->textureName = "building";
		}
		else
		{
			this->textureName = "hospital";
		}
	}
	else if (this->GetTileSpecialise() == SmallTile::TileSpecialise::POLICE_STATION)
	{
		if (this->buildedStructure == false)
		{
			this->textureName = "building";
		}
		else
		{
			this->textureName = "police_station";
		}
	}

	if (this->textureName != "unknown")
	{
		this->sprite.setTexture(textureBuildManager.GetAppropriateTexture(this->textureName));
	}

	if (this->GetTileSpecialise() != SmallTile::TileSpecialise::POWER_HOUSE)
	{
		if (this->textureName != "building")
		{
			this->frameSize = sf::IntRect(0, 0, TILE_SIZE * 2, TILE_SIZE*heightBuilding);
			this->sprite.setOrigin(sf::Vector2f(0.0f, TILE_SIZE*(heightBuilding - 1)));
		}
		else
		{
			this->frameSize = sf::IntRect(0, 0, TILE_SIZE * 2, TILE_SIZE*2);
			this->sprite.setOrigin(sf::Vector2f(0.0f, TILE_SIZE*(2 - 1)));
		}
	}
	else
	{
		this->sprite.setOrigin(sf::Vector2f(0.0f, TILE_SIZE*(heightBuilding - 1.5f)));
		this->frameSize = sf::IntRect(0, 0, 2 * TILE_SIZE * 2, TILE_SIZE*heightBuilding);
	}

	this->ChangeFrame(0);
	this->UpdateAnimation(0.0f);
}

void Structure::BuildStructure()
{
		if (this->buildDays == 0)
		{
			this->sprite.setTexture(this->textureBuildManager.GetBuildingTexture());
			this->heightBuilding = this->textureBuildManager.GetBuildingProcessHeight();

			this->frameSize = sf::IntRect(0, 0, TILE_SIZE * 2, TILE_SIZE*heightBuilding);
			this->sprite.setOrigin(sf::Vector2f(0.0f, TILE_SIZE*(heightBuilding - 1)));
			this->ChangeFrame(0);
			this->UpdateAnimation(0.0f);
		}

		this->buildDays++;

		if (buildDays > 3)
		{
			this->buildDays = 0;
			this->actualLevel++;

			this->isAnimation = (textureBuildManager.GetTexture(this->structureType, this->actualLevel).first);
			texture = (textureBuildManager.GetTexture(this->structureType, this->actualLevel).second);
			this->textureName = textureBuildManager.GetTextureName();

			this->buildedStructure = true;
			this->heightBuilding = this->textureBuildManager.GetTextureHeight();
			this->sprite.setTexture(this->texture);

			this->frameSize = sf::IntRect(0, 0, TILE_SIZE * 2, TILE_SIZE*heightBuilding);
			this->sprite.setOrigin(sf::Vector2f(0.0f, TILE_SIZE*(heightBuilding - 1)));

			this->ChangeFrame(0);
			this->UpdateAnimation(0.0f);

			if (this->isAnimation == true)
			{
				std::vector<Frames> tmp;
				Frames staticAnim(0, 0, 1.0f);
				tmp.push_back({ staticAnim });

				Frames waterAnim1(0, 2, 1.0f);

				std::vector<Frames> waterAnimation;
				waterAnimation.push_back({ waterAnim1 });

				Frames animation(0, 3, 1.0f);
				this->AddAnimation(animation);
			}
		}
}

#pragma endregion

#pragma region Setters

void Structure::SetID(ID id)
{
	this->buildingID = id;
}

void Structure::SetPathRoad(PathFinding *roadPath)
{
	this->roadPath = roadPath;
}

void Structure::SetCityOrdinancesPercentage(float cityOrdinancesPercentage)
{
	this->cityOrdinancesPercentage = cityOrdinancesPercentage;
}

void Structure::SetHasEnergy(bool hasEnergy)
{
	this->hasEnergy = hasEnergy;
}

void Structure::SetPropertyTaxesPercentage(float propertyTaxesPercentage)
{
	this->propertyTaxesPercentage = propertyTaxesPercentage;
}

void Structure::SetThiefInBuilding(bool thief)
{
	this->thiefInBuilding = thief;

	if (thief == false)
	{
		this->robberyCounter = 0;
	}
}

void Structure::SetInformationNoEnergy(bool informationNoEnergy)
{
	this->informationNoEnergy = informationNoEnergy;
}

void Structure::SetStructureOnFire(bool onFire)
{
	this->structureOnFire = onFire;
}

void Structure::SetInformationThief(bool informationThief)
{
	this->informationThief = informationThief;
}

void Structure::SetThiefCaught(bool thiefCaught)
{
	this->thiefCaught = thiefCaught;
}

void Structure::SetHasVehicle(bool hasVehicle)
{
	this->hasVehicle = hasVehicle;
}

void Structure::SetInformationStrike(bool informationStrike)
{
	this->informationStrike = informationStrike;
}

void Structure::SetVehicleInUse(bool vehicleInUse)
{
	this->vehicleInUse = vehicleInUse;
}

#pragma endregion

#pragma region Getters

std::string Structure::GetInformationAboutVehicle() const
{
	if (this->vehicleInUse == true)
	{
		return "Yes";
	}

	return "No";
}

ID Structure::GetID()
{
	return this->buildingID;
}

Vehicle *Structure::GetVehicle()
{
	return this->vehicle1;
}

bool Structure::GetBuildStatus()
{
	return this->buildedStructure;
}

bool Structure::GetThiefCaught() const
{
	return this->thiefCaught;
}

bool Structure::GetVehicleInUse() const
{
	return this->vehicleInUse;
}

const Vehicle *Structure::GetVehicle() const
{
	return this->vehicle1;
}

PathFinding *Structure::GetPatchRoad()
{
	return this->roadPath;
}

Structure::VehicleVisible Structure::GetVehicleVisible() const
{
	return this->vehicleVisible;
}

void Structure::SetTravelDestinationSuccess(bool travelDestinationSuccess)
{
	this->travelDestinationSuccess = travelDestinationSuccess;
}

bool Structure::GetInformationNoEnergy() const
{
	return this->informationNoEnergy;
}

bool Structure::GetTravelDestinationSuccess()
{
	if (this->travelDestinationSuccess == true)
	{
		travelDestinationSuccess == false;
		return true;
	}
	return false;
}

int Structure::GetStructureHeight() const
{
	return this->heightBuilding;
}

float Structure::GetHappiness() const
{
	return this->happiness;
}

bool Structure::GetHasEnergy() const
{
	return this->hasEnergy;
}

bool Structure::GetStructureOnFire() const
{
	return this->structureOnFire;
}

bool Structure::GetIsStrike() const
{
	return this->strike;
}

bool Structure::GetInformationStrike() const
{
	return this->informationStrike;
}

bool Structure::GetThiefInBuilding() const
{
	return this->thiefInBuilding;
}

int Structure::GetPropertyTaxesStructure() const
{
	return this->propertyTaxesStructure * this->propertyTaxesPercentage / 100.0f;
}

bool Structure::GetHasVehicle() const
{
	return this->hasVehicle;
}

int Structure::GetCityOrdinancesStructure() const
{
	return this->cityOrdinancesStructure * this->cityOrdinancesPercentage / 100.0f;
}

unsigned int Structure::GetActualLevel() const
{
	return this->actualLevel;
}

bool Structure::GetCallBackVehicle() const
{
	return this->callBackVehicle;
}

float Structure::GetPropertyTaxesPercentage() const
{
	return this->propertyTaxesPercentage;
}

float Structure::GetCityOrdinancesPercentage() const
{
	return this->cityOrdinancesPercentage;
}

int Structure::GetBuildDays() const
{
	return this->buildDays;
}

int Structure::GetRobberryCounter() const
{
	return this->robberyCounter;
}

bool Structure::GetInformationThief() const
{
	return this->informationThief;
}

#pragma endregion