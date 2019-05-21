#include "Structure.h"

#pragma region Constructors

Structure::Structure(const unsigned int heightBuilding, TileSpecialise tileSpecialise,
	const sf::Texture & texture, const std::vector<Frames> & frames, ID buildingID)
	:SmallTile(heightBuilding, texture, TypeOfTile::STRUCTURE, tileSpecialise, frames),
	buildingID(buildingID)
{
	this->structureType = StructureType::HOUSE;


	tileData.tileSpecialise = tileSpecialise;
	tileData.population = 0;
	tileData.level = 0;
	tileData.texture_name = "unknown";
	tileData.buildingID = UNDEFINED;
	tileData.height = 1;
}

Structure::~Structure()
{

}

#pragma endregion

#pragma region Class_Methods

std::unique_ptr<SmallTile> Structure::clone() const
{
	return std::make_unique<Structure>(heightBuilding, tileSpecialise, texture, frames, buildingID);
}


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
	if (SpriteClicked(sprite, *image, position))
	{
		return true;
	}

	return false;
}

float Structure::RandomiseEvent(int from, int to)
{
	std::default_random_engine engine;
	std::uniform_real_distribution<float> distribution(from, to);

	auto time = std::chrono::system_clock::now();
	auto interwal = time.time_since_epoch();
	engine.seed(interwal.count());

	return distribution(engine);
}

void Structure::ProcessDriving(float elapsedTime)
{
	if (this->vehicleInUse == true)
	{
		if (this->callBackVehicle == false)
		{
			if (this->driveToDestination->MakeProgress() == DRIVING_PROCESS::DRIVING)
			{
				this->vehicle1->UpdateVehicle(elapsedTime);
			}
			else if (this->driveToDestination->MakeProgress() == DRIVING_PROCESS::AT_DESTINATION)
			{
				this->travelDestinationSuccess = true;
				std::cout << "Dojechalem" << std::endl;

				this->callBackVehicle = true;
				this->driveToDestination->BeginDrivingProcess(true);
			}
		}
		else
		{
			if (this->driveToDestination->MakeProgress() == DRIVING_PROCESS::DRIVING)
			{
				this->vehicle1->UpdateVehicle(elapsedTime);
			}
			else if (this->driveToDestination->MakeProgress() == DRIVING_PROCESS::AT_DESTINATION)
			{
				this->callBackVehicle = false;
				this->vehicleInUse = false;
				std::cout << "Wrocilem" << std::endl;

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

		if (this->driveToDestination->GetDrivingProcess() != DRIVING_PROCESS::DEFEAT)
		{
			this->vehicleInUse = true;
		}
	}
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
			tileData.texture_name = textureBuildManager.GetTextureName();

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

bool Structure::GetBuildStatus()
{
	return this->buildedStructure;
}

void Structure::UpdateInformation()
{
	//... SOON
}

void Structure::SetNewTileVariant(const SmallTile * neighbourghood[NEIGHBORING][NEIGHBORING])
{
	//.. SOON
}

void Structure::Update(float elapsedTime)
{
	//... SOON
}

void Structure::Destroy()
{
	//..SOON
}

#pragma endregion

#pragma region Setters

void Structure::SetID(ID id)
{
	this->tileData.buildingID = id;
	this->buildingID = id;
}

void Structure::SetPathRoad(PathFinding *roadPath)
{
	this->roadPath = roadPath;
}

void Structure::SetHasEnergy(bool hasEnergy)
{
	this->hasEnergy = hasEnergy;
}

void Structure::SetInformationNoEnergy(bool informationNoEnergy)
{
	this->informationNoEnergy = informationNoEnergy;
}

void Structure::SetStructureOnFire(bool onFire)
{
	this->structureOnFire = onFire;
}

#pragma endregion

#pragma region Getters

ID Structure::GetID()
{
	return this->buildingID;
}

Vehicle *Structure::GetVehicle()
{
	return this->vehicle1;
}

const Vehicle *Structure::GetVehicle() const
{
	return this->vehicle1;
}

PathFinding *Structure::GetPatchRoad()
{
	return this->roadPath;
}

VehicleVisible Structure::GetVehicleVisible() const
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

#pragma endregion