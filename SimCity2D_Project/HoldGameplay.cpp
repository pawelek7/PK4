#include "HoldGameplay.h"

#pragma region Constructors
//constructors

HoldGameplay::HoldGameplay(std::shared_ptr<AssetsOfGame> ptrGame, const std::string & CityName, uint64_t seedMap,
	unsigned int sizeOfMap, bool loadGame)
{
	this->ptrGame = ptrGame; //set parameters and variables

	this->mapSize = sizeOfMap;
	this->cityName = CityName;
	this->gameSeed = seedMap;

	if (loadGame == false) //new game
	{
		this->mapTile = new MapTile(CityName, ptrGame, sizeOfMap, seedMap);
	}
	else //load game
	{
		this->mapTile = new MapTile(CityName, ptrGame);
		this->mapTile->LoadMap(CityName, this->IDstructures, //set structures
			this->housesVector, this->shopVector, this->factoryVector,
			this->hospitalsVector, this->powerhousesVector, this->policeStationVector,
			this->fireBrigadeVector, this->highVoltageLinesVector, this->IDconnectings);

		this->LoadCityInformation(); //load basic assets
	}

	this->newspaper = new Newspaper(this->ptrGame, this, this->mapSize); //create newspaper
	this->gameEventInfo = new GameEventInfo(this->ptrGame, this->mapSize); //create text information
	this->taxesInformation = new TaxesInformation(this->ptrGame, this->mapSize); //create taxes table
	this->statistics = new Statistics(this->ptrGame, this->mapSize); //create statistics table

	if (loadGame == false)
	{
		this->gameEvent = GameEvent::NEW_CITY;
		this->newspaper->SetIsTableOpen(true); //create newspaper - new game event
		this->newspaper->NewspaperEvent(TypeOfNewspaper::NEW_GAME);
	}
	else
	{
		this->EventNewDay();
		this->newspaper->NewspaperEvent(TypeOfNewspaper::REGULAR);
	}

	this->InitializeBasicAssets(); //initialize assets
}

//destructor
HoldGameplay::~HoldGameplay()
{
	if (this->mapTile != nullptr)
	{
		delete this->mapTile;
		this->mapTile = nullptr;
	}

	if (this->pictureInformation != nullptr)
	{
		delete this->pictureInformation;
		this->pictureInformation = nullptr;
	}

	if (this->tornado != nullptr)
	{
		delete this->tornado;
		this->tornado = nullptr;
	}

	if (this->fire != nullptr)
	{
		delete this->fire;
		this->fire = nullptr;
	}

	if (this->taxesInformation != nullptr)
	{
		delete this->taxesInformation;
		this->taxesInformation = nullptr;
	}

	if (this->newspaper != nullptr)
	{
		delete this->newspaper;
		this->newspaper = nullptr;
	}

	if (this->statistics != nullptr)
	{
		delete this->statistics;
		this->statistics = nullptr;
	}

	if (this->gameEventInfo != nullptr)
	{
		delete this->gameEventInfo;
		this->gameEventInfo = nullptr;
	}

	while (this->IDstructures.GetSize() != 0)
	{
		if (this->IDstructures.GetObjects().back() != nullptr)
		{
			delete this->IDstructures.GetObjects().back();
			this->IDstructures.GetObjects().back() = nullptr;
		}
		this->IDstructures.GetObjects().pop_back();
	}

	while (!this->housesVector.empty())
	{
		if (this->housesVector.back() != nullptr)
		{
			delete this->housesVector.back();
			this->housesVector.back() = nullptr;
		}
		this->housesVector.pop_back();
	}

	while (!this->shopVector.empty())
	{
		if (this->shopVector.back() != nullptr)
		{
			delete this->shopVector.back();
			this->shopVector.back() = nullptr;
		}
		this->shopVector.pop_back();
	}

	while (!this->factoryVector.empty())
	{
		if (this->factoryVector.back() != nullptr)
		{
			delete this->factoryVector.back();
			this->factoryVector.back() = nullptr;
		}
		this->factoryVector.pop_back();
	}

	while (!this->hospitalsVector.empty())
	{
		if (this->hospitalsVector.back() != nullptr)
		{
			delete this->hospitalsVector.back();
			this->hospitalsVector.back() = nullptr;
		}
		this->hospitalsVector.pop_back();
	}

	while (!this->powerhousesVector.empty())
	{
		if (this->powerhousesVector.back() != nullptr)
		{
			delete this->powerhousesVector.back();
			this->powerhousesVector.back() = nullptr;
		}
		this->powerhousesVector.pop_back();
	}

	while (!this->policeStationVector.empty())
	{
		if (this->policeStationVector.back() != nullptr)
		{
			delete this->policeStationVector.back();
			this->policeStationVector.back() = nullptr;
		}
		this->policeStationVector.pop_back();
	}

	while (!this->fireBrigadeVector.empty())
	{
		if (this->fireBrigadeVector.back() != nullptr)
		{
			delete this->fireBrigadeVector.back();
			this->fireBrigadeVector.back() = nullptr;
		}
		this->fireBrigadeVector.pop_back();
	}

	while (!this->highVoltageLinesVector.empty())
	{
		if (this->highVoltageLinesVector.back() != nullptr)
		{
			delete this->highVoltageLinesVector.back();
			this->highVoltageLinesVector.back() = nullptr;
		}
		this->highVoltageLinesVector.pop_back();
	}

	while (!this->pictureInformationVector.empty())
	{
		if (this->pictureInformationVector.back() != nullptr)
		{
			delete this->pictureInformationVector.back();
			this->pictureInformationVector.back() = nullptr;
		}
		this->pictureInformationVector.pop_back();
	}

	while (!this->tornadoVector.empty())
	{
		if (this->tornadoVector.back() != nullptr)
		{
			delete this->tornadoVector.back();
			this->tornadoVector.back() = nullptr;
		}
		this->tornadoVector.pop_back();
	}

	while (!this->fireVector.empty())
	{
		if (this->fireVector.back() != nullptr)
		{
			delete this->fireVector.back();
			this->fireVector.back() = nullptr;
		}
		this->fireVector.pop_back();
	}
}

#pragma endregion

#pragma region Class_Methods


#pragma region Description of the method
/*
A method that load basic assets.

method parameters:
____________________
no parameters

the return value:
____________________
no return value

@author
Pawel Salicki
*/
#pragma endregion

void HoldGameplay::InitializeBasicAssets()
{
	this->ptrGame->textureManager.LoadAsset("tornado", "Resources/Textures/tornado.png"); //load tornado texture
	this->ptrGame->textureManager.LoadAsset("fire", "Resources/Textures/fire.png"); //load fire texture
}


#pragma region Description of the method
/*
A method that forces epidemic event.

method parameters:
____________________
elapsedTime - delta time

the return value:
____________________
no return value

@author
Pawel Salicki
*/
#pragma endregion

void HoldGameplay::ForceEpidemicEvent()
{
	for (auto & epidemicHouse : this->housesVector) //epidemic in most houses
	{
		epidemicHouse->ForceEpidemic(); //force epidemic
	}
}


#pragma region Description of the method
/*
A method that forces tornado event.

method parameters:
____________________
no parameters

the return value:
____________________
no return value

@author
Pawel Salicki
*/
#pragma endregion

void HoldGameplay::ForceCycloneEvent()
{
	Frames tornadoAnim1(0, 7, 0.2f); //tornado animation

	std::vector<Frames> tornadoAnimation;
	tornadoAnimation.push_back({ tornadoAnim1 });

	this->tornado = new Tornado(this->ptrGame->textureManager.GetAsset("tornado"), //create new tornado
		tornadoAnimation);
	this->tornado->SetSizeMapInformation(this->mapSize); //initialize tornado
	this->tornado->InitializeTornado();

	this->tornadoVector.push_back(this->tornado); //push pointer of tornado to vector

	this->gameEventInfo->PushInformationToQueue("Tornado alert!", GameEventInfo::InfoType::BAD_INFO);
}


#pragma region Description of the method
/*
A method that forces fire event.

method parameters:
____________________
no parameters

the return value:
____________________
no return value

@author
Pawel Salicki
*/
#pragma endregion

void HoldGameplay::ForceFireEvent()
{
	if (this->IDstructures.GetSize() != 0) //if there are structures on map
	{
		int nrStructure = this->randomEngine.RandomiseEvent(0, this->IDstructures.GetSize()); //randomise structure

		Frames fireAnimation(0, 2, 0.5f); //set animation of fire
		std::vector<Frames> fireAnimationVec;
		fireAnimationVec.push_back(fireAnimation);

		this->fire = new Fire(this->ptrGame->textureManager.GetAsset("fire"), //create new fire
			fireAnimationVec);
		this->fire->SetSizeMapInformation(this->mapSize); //initialize fire

		this->fire->InitializeFire(this->IDstructures.GetObjects()[nrStructure]->GetPosition().x, this->IDstructures.GetObjects()[nrStructure]->GetPosition().y);
		this->fireVector.push_back(fire); //push fire to vector

		this->gameEventInfo->PushInformationToQueue("Fire alert!", GameEventInfo::InfoType::BAD_INFO);
	}
}

#pragma region Description of the method
/*
A method that destroy structure depending of ID.

method parameters:
____________________
structuresToDrstroy - vector of ID's structures to destroy

the return value:
____________________
no return value

@author
Pawel Salicki
*/
#pragma endregion

void HoldGameplay::DestroyStructureID(std::vector<ID> & structuresToDestroy)
{
	for (auto & it : structuresToDestroy)
	{
		for (auto & it2 : this->pictureInformationVector)
		{
			if (it2->GetPictureID() == it)
			{
				it2->ForceDelete(); //destory picture information on structure
			}
		}

		this->IDstructures.PopID(it); //destory structure
	}
}


#pragma region Description of the method
/*
A method that destroy connection.

method parameters:
____________________
connectionsToDestory - vector of ID's connections to destroy

the return value:
____________________
no return value

@author
Pawel Salicki
*/
#pragma endregion

void HoldGameplay::DestroyConnectionID(std::vector<ID> & connectionsToDestroy)
{
	for (auto & it : connectionsToDestroy)
	{
		this->IDconnectings.PopID(it); //destroy connection
	}
}


#pragma region Description of the method
/*
A method that calls method changing tile.

method parameters:
____________________
tileSpecialise - type of tile to change
specialBuilding - 1x1 or 2x2 structure

the return value:
____________________
no return value

@author
Pawel Salicki
*/
#pragma endregion

void HoldGameplay::ChangeTileG(SmallTile::TileSpecialise tileSpecialise, bool specialBuilding)
{
	std::vector<ID> structuresToDestroy; //structures to destory
	std::vector<ID> connectionsToDestroy; //connections to destory

	if (specialBuilding == true) //if is 2x2 structure
	{
		this->mapTile->ChangeSpecialTile(tileSpecialise, this->IDstructures, structuresToDestroy, //change tie
			this->highVoltageLinesVector, this->powerhousesVector, IDconnectings);
	}
	else //1x1 structure
	{
		this->mapTile->ChangeTile(tileSpecialise, this->IDstructures, structuresToDestroy, //change tile
			housesVector, shopVector, factoryVector,
			hospitalsVector, powerhousesVector, policeStationVector, fireBrigadeVector, highVoltageLinesVector,
			IDconnectings, connectionsToDestroy);
	}

	this->DestroyStructureID(structuresToDestroy); //destory ID
	this->DestroyConnectionID(connectionsToDestroy);
}

//constructors of interaction with objects
HoldGameplay::InteractBuilding::InteractBuilding()
	:interOption(HoldGameplay::InteractBuilding::InterOption::VOID), structure(nullptr)
{ }

HoldGameplay::InteractBuilding::InteractBuilding(Structure *structure)
	: interOption(HoldGameplay::InteractBuilding::InterOption::STRUCTURE), structure(structure)
{ }


#pragma region Description of the method
/*
A method that chcecks interaction with mouse position and structure position.

method parameters:
____________________
position - clicked position

the return value:
____________________
no return value

@author
Pawel Salicki
*/
#pragma endregion

HoldGameplay::InteractBuilding HoldGameplay::Interaction(const sf::Vector2f& position)
{
	InteractBuilding interactBuilding;

	VectorManager<std::unique_ptr<SmallTile>>& smallTilesVector = this->mapTile->GetSmallTile();

	for (auto & it : IDstructures.GetObjects()) //check interaction
	{
		Structure *structureInteracion = dynamic_cast<Structure*>(it);

		if (structureInteracion != nullptr)
		{
			if (structureInteracion->Interaction(position)) //mouse and structure on the same position
			{
				interactBuilding = InteractBuilding(it);
				return interactBuilding;
			}
			else //no interaction
			{
				interactBuilding = InteractBuilding();
			}
		}
	}
	return interactBuilding;
}


#pragma region Description of the method
/*
A method that saves city information.

method parameters:
____________________
no parameters

the return value:
____________________
no return value

@author
Pawel Salicki
*/
#pragma endregion

void HoldGameplay::SaveCityInformation()
{
	std::ofstream saveCityInfo;
	saveCityInfo.exceptions(std::ofstream::failbit | std::ifstream::badbit);

	//open file to save

	try
	{
		saveCityInfo.open("Resources/Maps/" + this->cityName + "_info.bin", std::ios::out | std::ios::binary);

		saveCityInfo.write((char*)&gameEvent, sizeof(GameEvent)); //save actual game event
		saveCityInfo.write((char*)&timeSpeed, sizeof(TimeSpeed)); //save actual time speed

		//save city
		saveCityInfo.write((char*)&mapSize, sizeof(int));
		saveCityInfo.write((char*)&gameSeed, sizeof(uint64_t));
		saveCityInfo.write((char*)&money, sizeof(int));
		saveCityInfo.write((char*)&homeless, sizeof(int));
		saveCityInfo.write((char*)&cityPopulation, sizeof(unsigned int));
		saveCityInfo.write((char*)&workingPopulation, sizeof(unsigned int));
		saveCityInfo.write((char*)&unemployedPopulation, sizeof(unsigned int));
		saveCityInfo.write((char*)&wantShoppingPopulation, sizeof(unsigned int));
		saveCityInfo.write((char*)&incomeThisMonth, sizeof(int));
		saveCityInfo.write((char*)&incomePreviousMonth, sizeof(int));
		saveCityInfo.write((char*)&propertyTaxes, sizeof(int));
		saveCityInfo.write((char*)&cityOrdiances, sizeof(int));
		saveCityInfo.write((char*)&policeDepartment, sizeof(int));
		saveCityInfo.write((char*)&fireDepartment, sizeof(int));
		saveCityInfo.write((char*)&healthWelfare, sizeof(int));
		saveCityInfo.write((char*)&timeInGame, sizeof(float));
		saveCityInfo.write((char*)&actualTime, sizeof(float));
		saveCityInfo.write((char*)&day, sizeof(unsigned int));
		saveCityInfo.write((char*)&month, sizeof(unsigned int));
		saveCityInfo.write((char*)&year, sizeof(unsigned int));
		saveCityInfo.write((char*)&happiness, sizeof(float));
		saveCityInfo.write((char*)&attractivness, sizeof(float));

		//save name city
		size_t len = this->cityName.size();
		saveCityInfo.write((char*)&len, sizeof(size_t));
		saveCityInfo.write(cityName.c_str(), cityName.length());

		saveCityInfo.close();

		this->gameEventInfo->PushInformationToQueue("City informations saved!", GameEventInfo::InfoType::GOOD_INFO);
	}
	catch (std::ofstream::failure & e)
	{
		std::cout << "Saving City error: " << e.what() << std::endl;
		this->gameEventInfo->PushInformationToQueue("Saving Error!", GameEventInfo::InfoType::BAD_INFO);
	}
	catch (...)
	{
		std::cout << "Saving City Error!" << std::endl;
	}
}

#pragma region Description of the method
/*
A method that loads city information.

method parameters:
____________________
no parameters

the return value:
____________________
no return value

@author
Pawel Salicki
*/
#pragma endregion

void HoldGameplay::LoadCityInformation()
{
	std::ifstream loadCityInfo;
	loadCityInfo.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	//open file to load
	try
	{
		loadCityInfo.open("Resources/Maps/" + this->cityName + "_info.bin", std::ios::in | std::ios::binary);

		loadCityInfo.read((char*)&gameEvent, sizeof(GameEvent)); //load actual game event
		loadCityInfo.read((char*)&timeSpeed, sizeof(TimeSpeed)); //load actual time speed
		loadCityInfo.read((char*)&mapSize, sizeof(int));
		loadCityInfo.read((char*)&gameSeed, sizeof(uint64_t));
		loadCityInfo.read((char*)&money, sizeof(int));
		loadCityInfo.read((char*)&homeless, sizeof(int));
		loadCityInfo.read((char*)&cityPopulation, sizeof(unsigned int));
		loadCityInfo.read((char*)&workingPopulation, sizeof(unsigned int));
		loadCityInfo.read((char*)&unemployedPopulation, sizeof(unsigned int));
		loadCityInfo.read((char*)&wantShoppingPopulation, sizeof(unsigned int));
		loadCityInfo.read((char*)&incomeThisMonth, sizeof(int));
		loadCityInfo.read((char*)&incomePreviousMonth, sizeof(int));
		loadCityInfo.read((char*)&propertyTaxes, sizeof(int));
		loadCityInfo.read((char*)&cityOrdiances, sizeof(int));
		loadCityInfo.read((char*)&policeDepartment, sizeof(int));
		loadCityInfo.read((char*)&fireDepartment, sizeof(int));
		loadCityInfo.read((char*)&healthWelfare, sizeof(int));
		loadCityInfo.read((char*)&timeInGame, sizeof(float));
		loadCityInfo.read((char*)&actualTime, sizeof(float));
		loadCityInfo.read((char*)&day, sizeof(unsigned int));
		loadCityInfo.read((char*)&month, sizeof(unsigned int));
		loadCityInfo.read((char*)&year, sizeof(unsigned int));
		loadCityInfo.read((char*)&happiness, sizeof(float));
		loadCityInfo.read((char*)&attractivness, sizeof(float));

		//load city name
		size_t len = 0;
		loadCityInfo.read((char*)&len, sizeof(size_t));
		char* temp = new char[len + 1];
		loadCityInfo.read(temp, len);
		temp[len] = '\0';
		this->cityName = temp;
		delete[]temp;

		loadCityInfo.close();
	}
	catch (std::ifstream::failure & e)
	{
		std::cout << "Reading City error: " << e.what() << std::endl;
	//	this->gameEventInfo->PushInformationToQueue("Reading City File Error!", GameEventInfo::InfoType::BAD_INFO);
	}
	catch (...)
	{
		std::cout << "Reading City File error" << std::endl;
	}
}

//update statistics
void HoldGameplay::UpdateStatistics()
{
	this->ComputeHappiness();
	this->ComputeAttractivess();
}


#pragma region Description of the method
/*
A method that calculate overall happiness.

method parameters:
____________________
no parameters

the return value:
____________________
no return value

@author
Pawel Salicki
*/
#pragma endregion

void HoldGameplay::ComputeHappiness()
{
	int n = 0;
	float happinessAverage = 0.0f;

	for (auto & house : this->housesVector) //get happiness from all houses
	{
		happinessAverage += house->GetHappiness();
		n = n + 1;
	}

	for (auto & structure : this->IDstructures.GetObjects()) //decrease happiness if there are ruins on map
	{
		if (structure->GetIsRuins())
		{
			if (happinessAverage > 50)
			{
				happinessAverage -= 5;
			}
		}
	}

	if (n == 0)
	{
		this->happiness = 0;
	}
	else
	{
		this->happiness = happinessAverage / n; //calculate average of happiness
	}

	if (this->happiness < 0)
	{
		this->happiness = 0;
	}
	else if (this->happiness > 100)
	{
		this->happiness = 100;
	}
}


#pragma region Description of the method
/*
A method that calculates attractivness of city.

method parameters:
____________________
no parameters

the return value:
____________________
no return value

@author
Pawel Salicki
*/
#pragma endregion

void HoldGameplay::ComputeAttractivess()
{
	this->attractivness = 50.0f; //start from

	for (auto & tiles : this->mapTile->tilesVector.GetVector()) //add attractivness or drcrease depending on tiles on map
	{
		if (tiles->GetIsFactory())
		{
			attractivness -= 5;
		}
		else if (tiles->GetIsPowerHouse())
		{
			attractivness -= 20;
		}
		else if (tiles->GetIsRuins())
		{
			attractivness -= 50;
		}
		else if (tiles->GetIsShops())
		{
			attractivness += 2;
		}
		else if (tiles->GetIsTrees())
		{
			attractivness += 1;
		}
		else if (tiles->GetIsWater())
		{
			attractivness += 1;
		}
		else if (tiles->GetIsTressWithGrass())
		{
			attractivness += 3;
		}
		else if (tiles->GetIsStatue())
		{
			attractivness += 50;
		}
	}

	if (attractivness > 100) //set max or min percentage of happiness
	{
		this->attractivness = 100;
	}
	else if (attractivness < 0)
	{
		this->attractivness = 0;
	}
}

//manage homeless income
void HoldGameplay::NewHomelessManaging()
{
	if (attractivness > 50)
	{
		this->homeless += (happiness) * ((int)(this->cityPopulation / 100.0f)) + 5;
	}

	if (this->homeless > (this->cityPopulation+100))
	{
		this->homeless = this->cityPopulation;
	}

	if (attractivness < 30)
	{
		if (homeless > 10)
			homeless -= 10;
	}

}

#pragma region Description of the method
/*
A method that updates structures in new day event.

method parameters:
____________________
no parameters

the return value:
____________________
no return value

@author
Pawel Salicki
*/
#pragma endregion

void HoldGameplay::EventNewDay()
{
	if (this->month == 1) //short year or longer year
	{
		if (this->year % 4 == 0 && this->year % 100 != 0 || this->year % 400 == 0)
		{
			if (this->day > 28)
			{
				this->day = 1;
				++this->month;
				this->EventNewMonth();
			}
		}
		else
		{
			if (this->day > 29)
			{
				this->day = 1;
				++this->month;
				this->EventNewMonth();
			}
		}
	}
	else if (this->month % 2 == 0)
	{
		if (this->day > 31)
		{
			this->day = 1;
			++this->month;
			this->EventNewMonth();
		}
	}
	else
	{
		if (this->day > 30)
		{
			this->day = 1;
			++this->month;
			this->EventNewMonth();
		}
	}

	this->NewHomelessManaging(); //manage homeless income

	this->unemployedPopulation = this->cityPopulation; //set population

	if (this->cityPopulation < this->workingPopulation)
	{
		this->workingPopulation = this->cityPopulation;
	}
	this->unemployedPopulation -= this->workingPopulation;
	this->wantShoppingPopulation = this->unemployedPopulation;

	if (this->unemployedPopulation < 0)
	{
		this->unemployedPopulation = 0;
	}
	
	if (this->wantShoppingPopulation < 0)
	{
		this->wantShoppingPopulation = 0;
	}

	int homePopulation = 0;
	int energySteal = 0;
	int actualWorking = 0;

	/* ENERGY MANAGE*/

	for (auto & voltagePylon : this->highVoltageLinesVector)
	{
		voltagePylon->CheckConnectionToPowerStation();
	}

	if (this->powerhousesVector.empty())
	{
		for (auto & building : this->IDstructures.GetObjects())
		{
			building->SetHasEnergy(false);
		}
	}
	else
	{
		for (auto & power : this->powerhousesVector)
		{
			if (!power->GetCanShareEnergy() && power->GetIsStrike() == false)
			{
				for (auto & building : this->IDstructures.GetObjects())
				{
					building->SetHasEnergy(false);
				}
				break;
			}
		}
	}


	for (auto & building : this->IDstructures.GetObjects())
	{
		bool foundEnergySource = false;
		for (auto & structures : this->IDstructures.GetObjects())
		{

			if ((building->GetPosition() == structures->GetPosition() + sf::Vector2i(1, 0)) ||
				(building->GetPosition() == structures->GetPosition() + sf::Vector2i(-1, 0)) ||
				(building->GetPosition() == structures->GetPosition() + sf::Vector2i(0, 1)) ||
				(building->GetPosition() == structures->GetPosition() + sf::Vector2i(0, -1)))
			{
				if (structures->GetHasEnergy() == true)
				{
					building->SetHasEnergy(true);
					foundEnergySource = true;
					energySteal++;
					break;
				}
			}
		}

		if (foundEnergySource == false)
		{
			for (auto & voltagePylon : this->highVoltageLinesVector)
			{
				if ((building->GetPosition() == voltagePylon->GetPylonCoordinates() + sf::Vector2i(1, 0)) ||
					(building->GetPosition() == voltagePylon->GetPylonCoordinates() + sf::Vector2i(-1, 0)) ||
					(building->GetPosition() == voltagePylon->GetPylonCoordinates() + sf::Vector2i(0, 1)) ||
					(building->GetPosition() == voltagePylon->GetPylonCoordinates() + sf::Vector2i(0, -1)))
				{
					if (voltagePylon->GetConnectedToPowerStation())
					{
						building->SetHasEnergy(true);
						foundEnergySource = true;
						energySteal++;
						break;
					}
				}
			}
		}

		if (foundEnergySource == false)
		{
			building->SetHasEnergy(false);

			if (building->GetInformationNoEnergy() == false)
			{
				this->PushPictureInformationToVector(building, PictureInformation::PictureType::ENERGY_OUT);
				building->SetInformationNoEnergy(true);
			}
		}
		else
		{
			if (building->GetInformationNoEnergy() == true)
			{
				this->ForceRemovePictureIndormation(building->GetID());
				building->SetInformationNoEnergy(false);

				energySteal++;
			}
		}

		/* HOUSE MANAGE NEW DAY */

		House *house = dynamic_cast<House*>(building);
		if (house != nullptr)
		{
			if (!house->GetBuildStatus())
			{
				house->BuildStructure();
			}
			else
			{
				if (this->homeless > 0 && house->GetHappiness() >= 20.0f)
				{
					int moveRate = 5;
					if (this->homeless < moveRate)
					{
						moveRate = this->homeless;
					}
					this->homeless = this->homeless - (moveRate - house->UpdatePopulationHouse(moveRate));

					if (house->GetIsAddedNewDomators())
					{
						this->PushPictureInformationToVector(house, PictureInformation::PictureType::PEOPLE_UP);
					}
				}
			}
			homePopulation += house->GetHousehold();

			house->SetPropertyTaxesPercentage(this->propertyTaxes);
			house->NewDayInHouse();

			if (house->GetAbandonedHouse())
			{
				house->SetSelectionProcess(SmallTile::SelectionProcess::SELECTED);
				this->ChangeTileG(SmallTile::TileSpecialise::RUINS, false);
				continue;
			}
		}

		/* SHOP MANAGE NEW DAY */

		Shop *shop = dynamic_cast<Shop*>(building);
		if (shop != nullptr)
		{
			shop->SetPropertyTaxesPercentage(this->propertyTaxes);
			shop->NewDayInShop();
			actualWorking += shop->GetEmployessNr();

			if (!shop->GetBuildStatus())
			{
				shop->BuildStructure();
			}
			else
			{
				if (this->cityPopulation > 0 && (this->cityPopulation - this->workingPopulation) > 0)
				{
					int hiringRate = 5;
					if (this->cityPopulation - this->workingPopulation < hiringRate)
					{
						hiringRate = this->cityPopulation - this->workingPopulation;
					}
					this->workingPopulation = this->workingPopulation += (hiringRate - shop->UpdateWorkersPopulation(hiringRate));
				}
			}
		}

		/* FACTORE MANAGE NEW DAY */

		Factory *factory = dynamic_cast<Factory*>(building);
		if (factory != nullptr)
		{
			actualWorking += factory->GetWorkersAmount();

			if (!factory->GetBuildStatus() && factory->GetIsStrike() == false)
			{
				factory->BuildStructure();
			}
			else
			{
				factory->ProduceGoods();
				factory->NewFactoryDay();

				if (this->cityPopulation > 0 && (this->cityPopulation - this->workingPopulation) > 0)
				{
					int hiringRate = 5;

					if (this->cityPopulation - this->workingPopulation < hiringRate)
					{
						hiringRate = this->cityPopulation - this->workingPopulation;
					}
					this->workingPopulation = this->workingPopulation += (hiringRate - factory->UpdateWorkersPopulation(hiringRate));
				}
			}

			factory->SetCityOrdinancesPercentage(this->cityOrdiances);

			if (factory->GetIsStrike())
			{
				if (factory->GetInformationStrike() == false)
				{
					this->PushPictureInformationToVector(factory, PictureInformation::PictureType::PROTEST, true);
					factory->SetInformationStrike(true);
				}
			}
			else
			{
				if (factory->GetInformationStrike())
				{
					this->ForceRemovePictureIndormation(factory->GetID(), PictureInformation::PictureType::PROTEST);
					factory->SetInformationStrike(false);
				}
			}
		}

		/* HOSPITAL MANAGE NEW DAY */

		Hospital *hospital = dynamic_cast<Hospital*>(building);
		if (hospital != nullptr)
		{
			actualWorking += hospital->GetHospitalWorkersAmount();
			hospital->SetHealthAndWalfare(this->healthWelfare);
			hospital->NewDayHospital();
			if (hospital->GetIsStrike() == false)
			{
				if (!hospital->GetBuildStatus())
				{
					hospital->BuildHospital();
				}
				else
				{
					if (hospital->GetIsHospitalWorking())
					{
						while (hospital->GetIsPatientReady())
						{
							for (auto & house : this->housesVector)
							{
								if (house->GetReservedSpace() > 0)
								{
									if (hospital->ReturnPatientToHouse(house->GetID()))
									{
										house->AddOldDomatorToHouse();
									}
								}
							}
						}
					}

					if (this->cityPopulation > 0 && (this->cityPopulation - this->workingPopulation) > 0)
					{
						int hiringRate = 5;

						if (this->cityPopulation - this->workingPopulation < hiringRate)
						{
							hiringRate = this->cityPopulation - this->workingPopulation;
						}
						this->workingPopulation = this->workingPopulation += (hiringRate - hospital->UpdateWorkersPopulation(hiringRate));
					}
				}
			}

			if (hospital->GetIsStrike())
			{
				if (hospital->GetInformationStrike() == false)
				{
					this->PushPictureInformationToVector(hospital, PictureInformation::PictureType::PROTEST);
					hospital->SetInformationStrike(true);
				}
			}
			else
			{
				if (hospital->GetInformationStrike())
				{
					this->ForceRemovePictureIndormation(hospital->GetID(), PictureInformation::PictureType::PROTEST);
					hospital->SetInformationStrike(false);
				}
			}

		}

		/* FIRE BRIGADE MANAGE NEW DAY*/

		FireBrigade *fireBrigade = dynamic_cast<FireBrigade*>(building);
		if (fireBrigade != nullptr)
		{
			actualWorking += fireBrigade->GetFirefightersAmount();
			fireBrigade->SetFireDepartmentPercentage(this->fireDepartment);
			fireBrigade->NewDayFireBrigade();

			if (!fireBrigade->GetBuildStatus())
			{
				fireBrigade->BuildFireBrigade();
			}

			if (fireBrigade->GetHasEnergy() && fireBrigade->GetIsStrike() == false)
			{
				if (this->cityPopulation > 0 && (this->cityPopulation - this->workingPopulation) > 0)
				{
					int hiringRate = 5;

					if (this->cityPopulation - this->workingPopulation < hiringRate)
					{
						hiringRate = this->cityPopulation - this->workingPopulation;
					}
					this->workingPopulation = this->workingPopulation += (hiringRate - fireBrigade->UpdateFirefightersPopulation(hiringRate));
				}
			}

			if (fireBrigade->GetIsStrike())
			{
				if (fireBrigade->GetInformationStrike() == false)
				{
					this->PushPictureInformationToVector(fireBrigade, PictureInformation::PictureType::PROTEST);
					fireBrigade->SetInformationStrike(true);
				}
				else
				{
					if (fireBrigade->GetInformationStrike() == true)
					{
						this->ForceRemovePictureIndormation(fireBrigade->GetID(), PictureInformation::PictureType::PROTEST);
						fireBrigade->SetInformationStrike(false);
					}
				}
			}
		}

		/* POLICE MANAGE NEW DAY */

		PoliceStation *policeStation = dynamic_cast<PoliceStation*>(building);
		if (policeStation != nullptr)
		{
			actualWorking += policeStation->GetPolicemen();
			policeStation->SetPoliceDepartmentPercentage(this->policeDepartment);
			policeStation->NewDayInPoliceStation();
			if (!policeStation->GetBuildStatus())
			{
				policeStation->BuildPoliceStation();
			}

			if (policeStation->GetIsStrike())
			{
				if (policeStation->GetInformationStrike() == false)
				{
					this->PushPictureInformationToVector(policeStation, PictureInformation::PictureType::PROTEST);
					policeStation->SetInformationStrike(true);
				}
			}
			else
			{
				if (this->cityPopulation > 0 && (this->cityPopulation - this->workingPopulation) > 0)
				{
					int hiringRate = 5;

					if (this->cityPopulation - this->workingPopulation < hiringRate)
					{
						hiringRate = this->cityPopulation - this->workingPopulation;
					}
					this->workingPopulation = this->workingPopulation += (hiringRate - policeStation->UpdatePolicemenPopulation(hiringRate));
				}

				if (policeStation->GetInformationStrike() == true)
				{
					this->ForceRemovePictureIndormation(policeStation->GetID(), PictureInformation::PictureType::PROTEST);
					policeStation->SetInformationStrike(false);
				}
			}

		}

		/* POWER HOUSE MANAGE NEW DAY */

		PowerHouse *powerHouse = dynamic_cast<PowerHouse*>(building);
		if (powerHouse != nullptr)
		{
			actualWorking += powerHouse->GetEmployessAmount();
			if (this->cityPopulation > 0 && (this->cityPopulation - this->workingPopulation) > 0 && powerHouse->GetIsStrike() == false)
			{
				int hiringRate = 5;
				if (this->cityPopulation - this->workingPopulation < hiringRate)
				{
					hiringRate = this->cityPopulation - this->workingPopulation;
				}
				this->workingPopulation = this->workingPopulation += (hiringRate - powerHouse->UpdateWorkersPopulation(hiringRate));
			}
		}
	}

	for (auto & powerHouse : this->powerhousesVector)
	{
		actualWorking += powerHouse->GetEmployessAmount();
		powerHouse->SetCityOrdinancesPercentage(this->cityOrdiances);
		powerHouse->NewPowerHouseDay();

		if (powerHouse->GetIsStrike() == false)
		{
			powerHouse->SetHasEnergy(true);
			powerHouse->operator++();

			int i = 0;
			for (i; i < energySteal; i++)
			{
				if (!powerHouse->GetCanShareEnergy())
				{
					break;
				}
				powerHouse->operator--();
			}
			energySteal -= i;
		}

		if (powerHouse->GetIsStrike())
		{
			if (powerHouse->GetInformationStrike() == false)
			{
				this->PushPictureInformationToVector(powerHouse, PictureInformation::PictureType::PROTEST);
				powerHouse->SetInformationStrike(true);
			}
		}
		else
		{
			if (powerHouse->GetInformationStrike())
			{
				this->ForceRemovePictureIndormation(powerHouse->GetID(), PictureInformation::PictureType::PROTEST);
				powerHouse->SetInformationStrike(false);
			}
		}
	}

	this->cityPopulation = homePopulation;
	this->workingPopulation = actualWorking;
}


#pragma region Description of the method
/*
A method that updates structures in new month.

method parameters:
____________________
no parameters

the return value:
____________________
no return value

@author
Pawel Salicki
*/
#pragma endregion

void HoldGameplay::EventNewMonth()
{
	if (this->month >= 12) //new year
	{
		this->month = 0;
		++this->year;
	}

	this->UpdateStatistics(); //update statistics

	this->gameEvent = GameEvent::NEW_MONTH;
	this->newspaper->NewspaperEvent(TypeOfNewspaper::REGULAR); //new newspaper
	this->gameEventInfo->PushInformationToQueue("New newspaper!", GameEventInfo::InfoType::GOOD_INFO);

	this->TornadoRandomEvent(); //tornado event
	this->CalculateMoneyIncome(); //calculate money income

	for (auto & it : this->IDstructures.GetObjects())
	{
		if (it->GetHasVehicle())
		{
			it->SetVehicleInUse(false);
		}
	}
}

#pragma region Description of the method
/*
A method that calculate income of money.

method parameters:
____________________
no variables

the return value:
____________________
no return value

@author
Pawel Salicki
*/
#pragma endregion

void HoldGameplay::CalculateMoneyIncome()
{
	this->incomePreviousMonth = this->incomeThisMonth;
	this->incomeThisMonth = 0;

	for (auto & buildings : this->IDstructures.GetObjects()) //income from all structures
	{
		this->money += buildings->GetPropertyTaxesStructure(); //get taxes
		this->incomeThisMonth += buildings->GetPropertyTaxesStructure();

		this->money -= buildings->GetCityOrdinancesStructure(); //city ordinances
		this->incomeThisMonth -= buildings->GetCityOrdinancesStructure();

		Shop *shop = dynamic_cast<Shop*>(buildings); //get money from shops
		if (shop != nullptr)
		{
			shop->EmptyTheMoney();
		}
		else
		{
			Hospital *hospital = dynamic_cast<Hospital*>(buildings); //decrease money hispital
			if (hospital != nullptr)
			{
				this->money -= hospital->GetHealthAndWalfareStructure();
				this->incomeThisMonth -= hospital->GetHealthAndWalfareStructure();
			}
			else
			{
				FireBrigade *fireBrifade = dynamic_cast<FireBrigade*>(buildings);
				if (fireBrifade != nullptr)
				{
					this->money -= fireBrifade->GetFireDepartment();
					this->incomeThisMonth -= fireBrifade->GetFireDepartment();
				}
				else
				{
					PoliceStation *policeStation = dynamic_cast<PoliceStation*>(buildings);
					if (policeStation != nullptr)
					{
						this->money -= policeStation->GetPoliceDepartment();
						this->incomeThisMonth -= policeStation->GetPoliceDepartment();
					}
				}
			}
		}
	}

	//income information
	if (this->incomeThisMonth > 0)
	{
		this->gameEventInfo->PushInformationToQueue("Income: " + std::to_string(this->incomeThisMonth) + "$", GameEventInfo::InfoType::GOOD_INFO);
	}
	else
	{
		this->gameEventInfo->PushInformationToQueue("Income: " + std::to_string(this->incomeThisMonth) + "$", GameEventInfo::InfoType::BAD_INFO);
	}
}

//randomise tornado event
void HoldGameplay::TornadoRandomEvent()
{
	if (randomEngine.RandomiseEvent(0, 10000) <= 1)
	{
		this->ForceCycloneEvent();
	}
}


#pragma region Description of the method
/*
A method that updates objects in new year.

method parameters:
____________________
no parameters

the return value:
____________________
no return value

@author
Pawel Salicki
*/
#pragma endregion

void HoldGameplay::EventNewYear()
{
	//... 
}


#pragma region Description of the method
/*
A method that supports drawing objects.

method parameters:
____________________
renderTarget - target where pictures will be render
elapsedTime - delta time

the return value:
____________________
no return value

@author
Pawel Salicki
*/
#pragma endregion

void HoldGameplay::Draw(sf::RenderWindow* renderTarget, float elapsedTime)
{
	std::vector<ID> structuresToDestroy;

	this->mapTile->DrawMap(renderTarget, elapsedTime, //draw tiles
		this->IDstructures.GetObjects(), this->tornadoVector, this->fireVector);

	int iterator = 0;
	for (const auto & iterPictureInformation : pictureInformationVector) //draw tornado
	{
		this->pictureInformationVector[iterator]->DrawPictureInformation(renderTarget);
		iterator++;
	}

	iterator = 0;
	for (const auto & iterFireTmp : this->fireVector) //draw fire
	{
		this->fireVector[iterator]->Draw(*this->ptrGame->window, elapsedTime);
		iterator++;
	}

	this->DestroyStructureID(structuresToDestroy);
}


#pragma region Description of the method
/*
A method that removes picture information from structures.

method parameters:
____________________
buildingID - ID of building
pictureType - type of picture to destroy

the return value:
____________________
no return value

@author
Pawel Salicki
*/
#pragma endregion

void HoldGameplay::ForceRemovePictureIndormation(ID buildingID, PictureInformation::PictureType pictureType)
{
	int iterator = 0;

	//serach for picture to destroy
	for (iterPictureInformation = pictureInformationVector.begin(), iterator = 0;
		iterPictureInformation != pictureInformationVector.end(); iterPictureInformation++, iterator++)
	{
		if (pictureInformationVector[iterator]->GetPictureID() == buildingID)
		{
			if (pictureType == PictureInformation::PictureType::VOID)
			{
				delete pictureInformationVector[iterator]; //destroy picture
				pictureInformationVector.erase(iterPictureInformation);
				return;
			}
			else
			{
				if (pictureInformationVector[iterator]->GetPictureInformation() == pictureType)
				{
					delete pictureInformationVector[iterator]; //destory picture
					pictureInformationVector.erase(iterPictureInformation);
					return;
				}
			}
		}
	}
}


#pragma region Description of the method
/*
A method that sets picture information.

method parameters:
____________________
structure - structure that will have picture information
pictureType - type of picture
animationType - animation : short/long

the return value:
____________________
no return value

@author
Pawel Salicki
*/
#pragma endregion

void HoldGameplay::PushPictureInformationToVector(Structure* structure, PictureInformation::PictureType pictureType, bool animationType)
{
	//set picture informations
	for (auto & it : this->pictureInformationVector)
	{
		if (it->GetBuildingID() == structure->GetID())
		{
			if (it->GetPictureType() == pictureType)
				return;

			break;
		}
	}

	this->pictureInformation = new PictureInformation(structure->GetID());
	this->pictureInformation->InitializePictureInformation(pictureType);
	this->pictureInformation->SetPictureInformationPosition(structure->GetFixedPosition());
	this->pictureInformation->SetHoldInformation(animationType);
	this->pictureInformationVector.push_back(pictureInformation);
}


#pragma region Description of the method
/*
A method that updates city.

method parameters:
____________________
elapsedTime - delta time

the return value:
____________________
no return value

@author
Pawel Salicki
*/
#pragma endregion

void HoldGameplay::Update(float elapsedTime)
{
	this->timeInGame += elapsedTime; //update time
	this->actualTime += elapsedTime;

	if (this->actualTime >= (float)this->timeSpeed) //new day
	{
		this->actualTime = 0;
		++this->day;
		this->EventNewDay();
	}

	/* HOUSE UPDATE */

	for (auto & house : this->housesVector)
	{
		house->Update(elapsedTime);

		if (house->GetBuildStatus())
		{
			if (house->GetIsEpidemic())
			{
				if (!house->GetInformationAboutEpidemic())
				{
					this->PushPictureInformationToVector(house, PictureInformation::PictureType::SICK, true);

					house->SetInformationAboutEpidemic(true);
				}

				if (!this->hospitalsVector.empty())
				{
					int hospitalNr = randomEngine.RandomiseEvent(0, hospitalsVector.size());
					if (this->hospitalsVector[hospitalNr]->GetBuildStatus() && this->hospitalsVector[hospitalNr]->GetIsStrike() == false)
					{
						if (this->hospitalsVector[hospitalNr]->GetIsHospitalWorking() == true)
						{
							if (this->hospitalsVector[hospitalNr]->GetVehicleInUse() == false)
							{
								if (this->hospitalsVector[hospitalNr]->GetHasEnergy())
								{
									this->hospitalsVector[hospitalNr]->DriveToBuildingStart(house);

									if (this->hospitalsVector[hospitalNr]->GetTravelDestinationSuccess())
									{
										this->hospitalsVector[hospitalNr]->AddPatients(house->GetID());
										house->SickPeopleToHospitalProcess();
										this->ForceRemovePictureIndormation(house->GetID(), PictureInformation::PictureType::SICK);
										this->hospitalsVector[hospitalNr]->SetTravelDestinationSuccess(false);
										house->SetInformationAboutEpidemic(false);
									}
								}
							}
						}
					}
				}
			}
		}

		if (house->GetHasEnergy())
		{
			if (house->GetVehicleInUse() == false)
			{
				if (!shopVector.empty())
				{
					int shopNr = randomEngine.RandomiseEvent(0, shopVector.size());
					if (shopVector[shopNr]->GetBuildStatus() && shopVector[shopNr]->GetIsClosedToday() == false)
					{
						if (!shopVector[shopNr]->GetEmptyWarehouse())
						{
							house->DriveToBuildingStart(shopVector[shopNr]);

							if (house->GetTravelDestinationSuccess())
							{
								shopVector[shopNr]->operator--();
								this->PushPictureInformationToVector(shopVector[shopNr], PictureInformation::PictureType::MONEY, false);
								house->SetTravelDestinationSuccess(false);
							}
						}
					}
				}
			}
		}

		if (house->GetThiefCaught())
		{
			this->ForceRemovePictureIndormation(house->GetID(), PictureInformation::PictureType::THIEF);
			house->SetThiefCaught(false);
			house->SetThiefInBuilding(false);
		}

		if (house->GetHappinessEvent() == House::HappinessEvent::HAPPY)
		{
			this->PushPictureInformationToVector(house, PictureInformation::PictureType::HAPPY);
			house->ResetHappinessEvent();
		}
		else if (house->GetHappinessEvent() == House::HappinessEvent::ANGRY)
		{
			this->PushPictureInformationToVector(house, PictureInformation::PictureType::ANGRY);
			house->ResetHappinessEvent();
		}
	}

	/* SHOP UPDATE */

	for (auto & shop : this->shopVector)
		if (shop != nullptr)
		{
			shop->Update(elapsedTime);
			if (shop->GetBuildStatus())
			{
				if (shop->GetEmptyWarehouse())
				{
					if (shop->GetAddedInformation() == false)
					{
						this->PushPictureInformationToVector(shop, PictureInformation::PictureType::GOODS_OUT, true);

						shop->SetAddedInformation(true);

					}

					for (auto &factory_delivery : factoryVector)
					{
						if (factory_delivery != nullptr && factory_delivery->GetIsStrike() == false)
						{
							if (factory_delivery->GetBuildStatus())
							{
								if (factory_delivery->CanDeliverGoods())
								{
									factory_delivery->DriveToBuildingStart(shop);

									if (factory_delivery->GetTravelDestinationSuccess())
									{
										shop->DeliveredGoods(factory_delivery->GetDeliveryAmount());
										factory_delivery->SetTravelDestinationSuccess(false);
										shop->SetAddedInformation(false);

										this->PushPictureInformationToVector(shop, PictureInformation::PictureType::GOODS_IN);

										this->ForceRemovePictureIndormation(shop->GetID(), PictureInformation::PictureType::GOODS_OUT);

										break;
									}
								}
							}
						}
					}
				}
			}
		}

	/* FACTORY UPDATE */

	for (auto & factory : this->factoryVector)
	{
		if (factory != nullptr)
		{
			factory->Update(elapsedTime);
		}
	}

	/* POWER HOUSE UPDATE */

	for (auto & powerHouse : this->powerhousesVector)
	{
		powerHouse->Update(elapsedTime);
	}

	/* FIRE STATION UPDATE */

	for (auto & fireStation : this->fireBrigadeVector)
	{
		fireStation->Update(elapsedTime);
	}

	/* HOSPITAL UPDATE */

	for (auto & hospital : this->hospitalsVector)
	{
		hospital->Update(elapsedTime);
	}

	/* POLICE UPDATE */

	for (auto & police : this->policeStationVector)
	{
		police->Update(elapsedTime);
	}

	/* ALL STRUCTURES UPDATE */

	for (auto & structure : this->IDstructures.GetObjects())
	{
		if (structure != nullptr)
		{
			/* TORNADO EVENT */

			for (auto & it : this->tornadoVector)
			{
				if (structure->GetSprite().getGlobalBounds().contains(it->GetDisasterMovablePosition()))
				{
					std::vector<ID> structuresToDestroy;
					std::vector<ID> connectionsToDestroy;

					structure->SetSelectionProcess(SmallTile::SelectionProcess::SELECTED);
					this->mapTile->ChangeTile(SmallTile::TileSpecialise::RUINS, this->IDstructures, structuresToDestroy,
						this->housesVector, this->shopVector, this->factoryVector, this->hospitalsVector,
						powerhousesVector, policeStationVector, fireBrigadeVector, highVoltageLinesVector,
						IDconnectings, connectionsToDestroy);

					this->DestroyStructureID(structuresToDestroy);
				}
			}

			/* FIRE EVENT */

			for (auto & fireIt : this->fireVector)
			{
				for (auto & fireIt2 : fireIt->GetFireVectorCoordinates())
				{
					if (structure->GetPosition() == fireIt2)
					{
						structure->SetStructureOnFire(true);
					}
				}

				if (structure->GetPosition() == fireIt->GetReturnedBurnedArea())
				{
					std::vector<ID> structuresToDestroy;
					std::vector<ID> connectionsToDestroy;

					structure->SetSelectionProcess(SmallTile::SelectionProcess::SELECTED);
					this->mapTile->ChangeTile(SmallTile::TileSpecialise::RUINS, this->IDstructures, structuresToDestroy,
						this->housesVector, this->shopVector, this->factoryVector, this->hospitalsVector,
						powerhousesVector, policeStationVector, fireBrigadeVector, highVoltageLinesVector,
						IDconnectings, connectionsToDestroy);

					this->DestroyStructureID(structuresToDestroy);
				}
			}

			if (structure->GetStructureOnFire())
			{
				for (auto & fireBrigade : this->fireBrigadeVector)
				{
					if (fireBrigade->GetHasEnergy() && fireBrigade->GetIsStrike() == false)
					{
						fireBrigade->DriveToBuildingStart(structure);

						if (structure->GetSprite().getGlobalBounds().contains(fireBrigade->GetVehicle()->GetVehicleSprite().getPosition()) && fireBrigade->GetTravelDestinationSuccess())
						{
							for (auto & fireIt : this->fireVector)
							{
								fireIt->FireBrigadeEvent(structure->GetPosition());
							}
							fireBrigade->operator++();
							structure->SetStructureOnFire(false);
						}

					}
				}
			}

			/* THIEF EVENT */

			if (structure->GetThiefInBuilding())
			{
				if (structure->GetInformationThief() == false)
				{
					structure->SetInformationThief(true);
					this->PushPictureInformationToVector(structure, PictureInformation::PictureType::THIEF, true);
				}

				for (auto & police : this->policeStationVector)
				{
					if (police->GetBuildStatus() && police->GetHasEnergy() && police->GetIsStrike() == false)
					{
						if (police->GetVehicleInUse() == false)
						{
							police->DriveToBuildingStart(structure);

							if (police->GetTravelDestinationSuccess())
							{
								structure->SetInformationThief(false);
								structure->SetThiefInBuilding(false);
								police->operator++();
								structure->SetThiefCaught(false);
								this->ForceRemovePictureIndormation(structure->GetID(), PictureInformation::PictureType::THIEF);
								police->SetTravelDestinationSuccess(false);
								break;
							}
						}
					}
				}
			}
		}
	}

	/* UPDATE */

	int iterator = 0;
	for (const auto & iterPictureInformation : pictureInformationVector)
	{
		this->pictureInformationVector[iterator]->UpdatePictureInformation(elapsedTime);
		iterator++;
	}

	for (iterPictureInformation = pictureInformationVector.begin(), iterator = 0;
		iterPictureInformation != pictureInformationVector.end(); iterPictureInformation++, iterator++)
	{
		if (pictureInformationVector[iterator]->GetIsDeleted())
		{
			delete pictureInformationVector[iterator];
			pictureInformationVector.erase(iterPictureInformation);
			break;
		}
	}

	this->gameEventInfo->UpdateInformationText();
	this->TaxesManaging();
	this->UpdateStatisticsTable();
	this->UpdateDisasters(elapsedTime);
}


#pragma region Description of the method
/*
A method that deletes structures that were destroyed by disasters.

method parameters:
____________________
buildingID - id of building

the return value:
____________________
no return value

@author
Pawel Salicki
*/
#pragma endregion

void HoldGameplay::DestroyedByDisaster(ID buildingID)
{
	int iterator = 0;

	//search for destroyed structure
	for (auto houseIterator = this->housesVector.begin(); houseIterator != this->housesVector.end();
		iterator++, houseIterator++)
	{
		if (housesVector[iterator]->GetID() == buildingID)
		{
			housesVector.erase(houseIterator); //delete structure
			break;
		}
	}
}


#pragma region Description of the method
/*
A method that updates disasters.

method parameters:
____________________
elapsedTime - delta time

the return value:
____________________
no return value

@author
Pawel Salicki
*/
#pragma endregion

void HoldGameplay::UpdateDisasters(float elapsedTime)
{
	/* UPDATE TORNADO */
	int iterator = 0;
	for (const auto & iterTornado : tornadoVector)
	{
		switch (this->timeSpeed)
		{
		case TimeSpeed::SLOW:
			this->tornadoVector[iterator]->SetDisasterMovableLifeTime(1000);
			this->tornadoVector[iterator]->SetDisasterMovableSpeed(10);
			break;
		case TimeSpeed::NORMAL:
			this->tornadoVector[iterator]->SetDisasterMovableLifeTime(500);
			this->tornadoVector[iterator]->SetDisasterMovableSpeed(20);
			break;
		case TimeSpeed::FAST:
			this->tornadoVector[iterator]->SetDisasterMovableLifeTime(300);
			this->tornadoVector[iterator]->SetDisasterMovableSpeed(40);
			break;
		case TimeSpeed::UBER:
			this->tornadoVector[iterator]->SetDisasterMovableLifeTime(200);
			this->tornadoVector[iterator]->SetDisasterMovableSpeed(50);
			break;
		}

		this->tornadoVector[iterator]->UpdateTornado(elapsedTime);
		iterator++;
	}


	for (iterTornado = tornadoVector.begin(), iterator = 0;
		iterTornado != tornadoVector.end(); iterTornado++, iterator++)
	{
		if (tornadoVector[iterator]->GetIsDisasterEnd())
		{
			delete tornadoVector[iterator];
			tornadoVector.erase(iterTornado);
			break;
		}
	}

	/* UPDATE FIRE */

	for (iterFire = fireVector.begin(), iterator = 0;
		iterFire != fireVector.end(); iterFire++, iterator++)
	{
		if (this->fireVector[iterator]->GetIsDisasterEnd())
		{
			delete fireVector[iterator];
			fireVector.erase(iterFire);
			break;
		}
	}

	iterator = 0;
	for (const auto & iterFireTmp : fireVector)
	{
		this->fireVector[iterator]->UpdateDisaster(elapsedTime);
		iterator++;
	}

}

//update statistics in table
void HoldGameplay::UpdateStatisticsTable()
{
	if (this->statistics->GetIsTableOpnen() == true)
	{
		this->statistics->SetAttractivnessText(std::to_string(this->attractivness));
		this->statistics->SetDateText(this->GetDate());
		this->statistics->SetHappinessText(std::to_string(this->GetAverageHappiness()));
		this->statistics->SetHomelessText(std::to_string(this->homeless));
		this->statistics->SetMoneyText(std::to_string(this->money));
		this->statistics->SetPopulationText(std::to_string(this->cityPopulation));
		this->statistics->SetWorkingText(std::to_string(this->workingPopulation));
		this->statistics->SetCityNameText(this->cityName);
		this->statistics->SetIncomeThisMonthText(std::to_string(this->incomeThisMonth));
		this->statistics->SetIncomePreviousMonth(std::to_string(this->incomePreviousMonth));
	}
}

//manage taxes
void HoldGameplay::TaxesManaging()
{
	if (this->taxesInformation->GetIsTableOpnen() == true)
	{
		if (this->taxesInformation->GetAlreadyInitializedVariables() == false)
		{
			this->taxesInformation->SetVariables(this->propertyTaxes, this->cityOrdiances, this->policeDepartment,
				this->fireDepartment, this->healthWelfare, this->money);
		}
	}
	else
	{
		this->taxesInformation->SetAlreadyInitializedVariables(false);

		if (this->taxesInformation->GetMakeChanges() == true)
		{
			this->propertyTaxes = this->taxesInformation->GetPropertyTaxesIterator();
			this->cityOrdiances = this->taxesInformation->GetCityOrdiancesIterator();
			this->policeDepartment = this->taxesInformation->GetPoliceDepartmentIterator();
			this->fireDepartment = this->taxesInformation->GetFireDepartmentIterator();
			this->healthWelfare = this->taxesInformation->GetHealthWelfareIterator();

			this->taxesInformation->SetMakeChanges(false);
		}
	}
}

void HoldGameplay::ChangePictureInformationPosition()
{
	for (auto & it : this->pictureInformationVector)
	{
		for (auto & structures : this->IDstructures.GetObjects())
		{
			if (it->GetBuildingID() == structures->GetID())
			{
				it->SetPictureInformationPosition(structures->GetSpritePosition());
			}
		}
	}
}

//decrease money
void HoldGameplay::DecreaseCityFunds(int totalCost)
{
	this->money -= totalCost;
}

#pragma endregion

#pragma region Setters
//setters

void HoldGameplay::SetTimeSpeed(TimeSpeed timeSpeed)
{
	this->timeSpeed = timeSpeed;

	switch (timeSpeed)
	{
	case TimeSpeed::SLOW:
		this->mapTile->SetTimeFromGameplay(10);
		break;
	case TimeSpeed::NORMAL:
		this->mapTile->SetTimeFromGameplay(50);
		break;
	case TimeSpeed::FAST:
		this->mapTile->SetTimeFromGameplay(100);
		break;
	case TimeSpeed::UBER:
		this->mapTile->SetTimeFromGameplay(200);
		break;
	}
}

void HoldGameplay::SetPropertyTaxes(int propertyTaxes)
{
	this->propertyTaxes = propertyTaxes;
}

void HoldGameplay::SetCityOrdiances(int cityOrdiances)
{
	this->cityOrdiances = cityOrdiances;
}

void HoldGameplay::SetPoliceDepartment(int policeDepartment)
{
	this->policeDepartment = policeDepartment;
}

void HoldGameplay::SetFireDepartment(int fireDepartment)
{
	this->fireDepartment = fireDepartment;
}

void HoldGameplay::SetHealthWelfare(int healthWalfare)
{
	this->healthWelfare = healthWalfare;
}

#pragma endregion

#pragma region Getters
//getters

MapTile *HoldGameplay::GetMaptile()
{
	return this->mapTile;
}

Newspaper *HoldGameplay::GetNewspaper()
{
	return this->newspaper;
}

unsigned int HoldGameplay::GetDay() const
{
	return this->day;
}

unsigned int HoldGameplay::GetMonth() const
{
	return this->month;
}

unsigned int HoldGameplay::GetYear() const
{
	return this->year;
}

std::string HoldGameplay::GetFromattedMonth() const
{
	switch (this->month)
	{
	case 0:
		return "January";
	case 1:
		return "February";
	case 2:
		return "March";
	case 3:
		return "April";
	case 4:
		return "May";
	case 5:
		return "June";
	case 6:
		return "July";
	case 7:
		return "August";
	case 8:
		return "September";
	case 9:
		return "October";
	case 10:
		return "November";
	case 11:
		return "December";
	default:
		return "unknown";
	}
}

std::string HoldGameplay::GetDate()
{
	return "Day " + std::to_string(this->day) + ' ' + this->GetFromattedMonth() + ' ' + "Year " + std::to_string(this->year);
}

float HoldGameplay::GetAverageHappiness() const
{
	return this->happiness;
}

float HoldGameplay::GetAttractiveness() const
{
	return this->attractivness;
}

int HoldGameplay::GetCityMoney() const
{
	return this->money;
}

unsigned int HoldGameplay::GetPopulation() const
{
	return this->cityPopulation;
}

GameEventInfo *HoldGameplay::GetGameEventInfo()
{
	return this->gameEventInfo;
}

Structure* HoldGameplay::GetStructure(ID _id)
{
	return this->IDstructures.GetElement(_id);
}

TaxesInformation *HoldGameplay::GetTaxesInformation()
{
	return this->taxesInformation;
}

Statistics *HoldGameplay::GetStatistics()
{
	return this->statistics;
}

int HoldGameplay::GetPropertyTaxes() const
{
	return this->propertyTaxes;
}

int HoldGameplay::GetCityOrdiances() const
{
	return this->cityOrdiances;
}

int HoldGameplay::GetPoliceDepartment() const
{
	return this->policeDepartment;
}

int HoldGameplay::GetFireDepartment() const
{
	return this->fireDepartment;
}

int HoldGameplay::GetHealthWelfare() const
{
	return this->healthWelfare;
}

std::string HoldGameplay::GetCityName() const
{
	return this->cityName;
}

uint64_t HoldGameplay::GetGameSeed() const
{
	return this->gameSeed;
}

int HoldGameplay::GetHomeless() const
{
	return this->homeless;
}

unsigned int HoldGameplay::GetUnemployed() const
{
	if (this->unemployedPopulation < 0)
		return 0;

	return this->unemployedPopulation;
}

#pragma endregion