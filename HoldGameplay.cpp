#include "HoldGameplay.h"

#pragma region Constructors

HoldGameplay::HoldGameplay(std::shared_ptr<AssetsOfGame> ptrGame, const std::string & CityName, uint64_t seedMap,
	unsigned int sizeOfMap, bool loadGame)
{
	this->ptrGame = ptrGame;

	this->mapSize = sizeOfMap;
	this->cityName = CityName;

	this->gameSeed = seedMap;

	this->newspaper = new Newspaper(this->ptrGame, this, this->mapSize);

	if (loadGame == false)
	{
		this->mapTile = new MapTile(CityName, ptrGame, sizeOfMap, seedMap);
		this->gameEvent = GameEvent::NEW_CITY;
		this->newspaper->SetIsTableOpen(true);
		this->newspaper->NewspaperEvent(TypeOfNewspaper::NEW_GAME);

	}
	else
	{
		this->mapTile = new MapTile(CityName, ptrGame);
		this->LoadCityInformation();

		for (int i = 0; i < this->mapTile->GetSizeOfMap(); i++)
		{
			for (int j = 0; j < this->mapTile->GetSizeOfMap(); j++)
			{

				Structure *structure = dynamic_cast<Structure*>(this->mapTile->GetSmallTile().GetElements(i, j).get());

				if (structure != nullptr)
				{
					ID _id = IDstructures.push(structure);
					structure->SetID(_id);
				}
			}
		}
	}

	this->taxesInformation = new TaxesInformation(this->ptrGame, this->mapSize);
	this->statistics = new Statistics(this->ptrGame, this->mapSize);

	this->ptrGame->textureManager.LoadAsset("tornado", "Resources/Textures/tornado.png");
	this->ptrGame->textureManager.LoadAsset("fire", "Resources/Textures/fire.png");

	this->RandomiseBuildings();
}

HoldGameplay::~HoldGameplay()
{
	delete this->taxesInformation;
}

#pragma endregion

#pragma region Class_Methods

void HoldGameplay::ForceEpidemicEvent()
{
	for (auto & it : IDstructures.getObjects())
	{
		House *house = dynamic_cast<House*>(it);

		if (house != nullptr)
		{
			house->ForceEpidemic();
		}
	}
}

void HoldGameplay::ForceCycloneEvent()
{
	Frames tornadoAnim1(0, 7, 0.2f);

	std::vector<Frames> tornadoAnimation;
	tornadoAnimation.push_back({ tornadoAnim1 });

	this->tornado = new Tornado(this->ptrGame->textureManager.GetAsset("tornado"),
		tornadoAnimation);
	this->tornado->SetSizeMapInformation(this->mapSize);
	this->tornado->InitializeTornado();

	this->tornadoVector.push_back(tornado);
}

void HoldGameplay::ForceFireEvent()
{
	for (auto & structures : this->IDstructures.getObjects())
	{
		Frames fireAnimation(0, 2, 0.5f);
		std::vector<Frames> fireAnimationVec;
		fireAnimationVec.push_back(fireAnimation);

		this->fire = new Fire(this->ptrGame->textureManager.GetAsset("fire"),
			fireAnimationVec);
		this->fire->SetSizeMapInformation(this->mapSize);

		this->fire->InitializeFire(structures->GetPosition().x, structures->GetPosition().y);

		this->fireVector.push_back(fire);
		break;
	}
}

void HoldGameplay::DestroyStructureID(std::vector<ID> & structuresToDestroy)
{
	for (auto & it : structuresToDestroy)
	{
		for (auto & it2 : this->pictureInformationVector)
		{
			if (it2->GetPictureID() == it)
			{
				it2->ForceDelete();
			}
		}

		this->IDstructures.PopID(it);
	}
}

void HoldGameplay::DestroyConnectionID(std::vector<ID> & connectionsToDestroy)
{
	for (auto & it : connectionsToDestroy)
	{
		this->IDconnectings.PopID(it);
	}
}

void HoldGameplay::ChangeTileG(TileSpecialise tileSpecialise, bool specialBuilding)
{
	std::vector<ID> structuresToDestroy;
	std::vector<ID> connectionsToDestroy;

	if (specialBuilding == true)
	{
		this->mapTile->ChangeSpecialTile(tileSpecialise, this->IDstructures, structuresToDestroy,
			this->highVoltageLinesVector, this->powerhousesVector, IDconnectings);
	}
	else
	{
		this->mapTile->ChangeTile(tileSpecialise, this->IDstructures, structuresToDestroy,
			housesVector, shopVector, factoryVector,
			hospitalsVector, powerhousesVector, policeStationVector, fireBrigadeVector, highVoltageLinesVector,
			IDconnectings, connectionsToDestroy);
	}

	this->DestroyStructureID(structuresToDestroy);
	this->DestroyConnectionID(connectionsToDestroy);
}

HoldGameplay::InteractBuilding::InteractBuilding()
	:interOption(HoldGameplay::InteractBuilding::InterOption::VOID), structure(nullptr)
{ }

HoldGameplay::InteractBuilding::InteractBuilding(Structure *structure)
	: interOption(HoldGameplay::InteractBuilding::InterOption::STRUCTURE), structure(structure)
{ }

HoldGameplay::InteractBuilding HoldGameplay::Interaction(const sf::Vector2f& position)
{
	InteractBuilding interactBuilding;

	VectorManager<std::unique_ptr<SmallTile>>& smallTilesVector = this->mapTile->GetSmallTile();

	for (auto & it : IDstructures.getObjects())
	{
		Structure *structureInteracion = dynamic_cast<Structure*>(it);

		if (structureInteracion != nullptr)
		{
			if (structureInteracion->Interaction(position))
			{
				interactBuilding = InteractBuilding(it);
				return interactBuilding;
			}
			else
			{
				interactBuilding = InteractBuilding();
			}
		}
	}
	return interactBuilding;
}

void HoldGameplay::SaveCityInformation()
{
	std::ofstream saveCityInfo("Resources/Maps/" + this->cityName + "_info.bin", std::ios::out | std::ios::binary);
	//	std::ofstream saveCityInfo("Resources/Maps/" + this->cityName + "_info.bin", std::ios::out | std::ios::binary);

	if (saveCityInfo.good())
	{
		saveCityInfo.write((char*)&day, sizeof(unsigned int)); //day
		saveCityInfo.write((char*)&month, sizeof(unsigned int)); //month
		saveCityInfo.write((char*)&year, sizeof(unsigned int)); //year
		saveCityInfo.write((char*)&money, sizeof(unsigned int)); //money
		saveCityInfo.write((char*)&homeless, sizeof(int)); //homeless
		saveCityInfo.write((char*)&cityPopulation, sizeof(unsigned int)); //population

		size_t len = this->cityName.size();
		saveCityInfo.write((char*)&len, sizeof(size_t));
		saveCityInfo.write(cityName.c_str(), cityName.length());

		saveCityInfo.close();
	}
}

void HoldGameplay::LoadCityInformation()
{
	std::ifstream loadCityInfo("Resources/Maps/" + this->cityName + "_info.bin", std::ios::in | std::ios::binary);

	if (loadCityInfo.good())
	{
		loadCityInfo.read((char*)&day, sizeof(unsigned int)); //day
		loadCityInfo.read((char*)&month, sizeof(unsigned int)); //month
		loadCityInfo.read((char*)&year, sizeof(unsigned int)); //year
		loadCityInfo.read((char*)&money, sizeof(unsigned int)); //money
		loadCityInfo.read((char*)&homeless, sizeof(int)); //homeless
		loadCityInfo.read((char*)&cityPopulation, sizeof(unsigned int)); //population

		size_t len = 0;

		loadCityInfo.read((char*)&len, sizeof(size_t));
		char* temp = new char[len + 1];
		loadCityInfo.read(temp, len);
		temp[len] = '\0';
		this->cityName = temp;
		delete[]temp;

		loadCityInfo.close();
	}
}

void HoldGameplay::UpdateStatistics()
{
	this->ComputeHappiness();
	this->ComputeAttractivess();
}

void HoldGameplay::ComputeHappiness()
{
	int n = 0;
	float happinessAverage = 0.0f;

	for (auto & house : this->housesVector)
	{
		happinessAverage += house->GetHappiness();
		n = n + 1;
	}

	for (auto & structure : this->IDstructures.getObjects())
	{
		if (structure->GetIsRuins())
		{
			if (happinessAverage > 100)
			{
				happinessAverage -= 20;
			}	
		}
	}

	this->happiness = happinessAverage / n;
}

void HoldGameplay::ComputeAttractivess()
{
	this->attractivness = 50.0f;

	for (auto & tiles : this->mapTile->tilesVector.GetVector())
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
	}

	if (attractivness > 100)
	{
		this->attractivness = 100;
	}
	else if (attractivness < 0)
	{
		this->attractivness = 0;
	}
}

void HoldGameplay::NewHomelessManaging()
{
	this->homeless += 10 * attractivness;
}

void HoldGameplay::EventNewDay()
{
	if (this->month == 1)
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

	this->NewHomelessManaging();

	this->unemployedPopulation = this->cityPopulation;
	this->unemployedPopulation -= this->workingPopulation;
	this->wantShoppingPopulation = this->unemployedPopulation;

	int homePopulation = 0;
	int energySteal = 0;
	//bool energyCanBeSupplied = false;

	for (auto & voltagePylon : this->highVoltageLinesVector)
	{
		voltagePylon->CheckConnectionToPowerStation();
	}

	if (this->powerhousesVector.empty())
	{
		for (auto & building : this->IDstructures.getObjects())
		{
			building->SetHasEnergy(false);
			//energyCanBeSupplied = false;
		}
	}
	else
	{
		for (auto & power : this->powerhousesVector)
		{
			if (!power->GetCanShareEnergy())
			{
				for (auto & building : this->IDstructures.getObjects())
				{
					building->SetHasEnergy(false);
					//energyCanBeSupplied = false;
				}
				break;
			}
		}
	}


	for (auto & building : this->IDstructures.getObjects())
	{
			bool foundEnergySource = false;
			for (auto & structures : this->IDstructures.getObjects())
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
					this->PushPictureInformationToVector(building, PictureType::ENERGY_OUT);
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
		

		House *house = dynamic_cast<House*>(building);
		if (house != nullptr)
		{
			if (!house->GetBuildStatus())
			{
				house->BuildStructure();
			}
			else if (this->homeless > 0)
			{
				int moveRate = 5;
				if (this->homeless < moveRate)
				{
					moveRate = this->homeless;
				}
				this->homeless = this->homeless - (moveRate - house->UpdatePopulationHouse(moveRate));

				//picture info
				if (house->GetIsAddedNewDomators())
				{
					this->PushPictureInformationToVector(house, PictureType::PEOPLE_UP);
				}

			}
			homePopulation += house->GetHousehold();

			//check energy


		}

		//Shop Operations
		Shop *shop = dynamic_cast<Shop*>(building);
		if (shop != nullptr)
		{
			if (!shop->GetBuildStatus())
			{
				shop->BuildStructure();
			}

			//Workers and upgrade
			else if (this->cityPopulation > 0 && (this->cityPopulation - this->workingPopulation) > 0)
			{
				int hiringRate = 5;
				if (this->cityPopulation - this->workingPopulation < hiringRate)
				{
					hiringRate = this->cityPopulation - this->workingPopulation;
				}
				this->workingPopulation = this->workingPopulation += (hiringRate - shop->UpdateWorkersPopulation(hiringRate));
			}

			/*
			//Selling goods
			if (this->wantShoppingPopulation > 0)
			{
				this->wantShoppingPopulation = shop->ShoppingTime(this->wantShoppingPopulation);
			}
			*/

		}

		//Update Factory
		Factory *factory = dynamic_cast<Factory*>(building);
		if (factory != nullptr)
		{
			if (!factory->GetBuildStatus())
			{
				factory->BuildStructure();
			}

			else if (this->cityPopulation > 0 && (this->cityPopulation - this->workingPopulation) > 0)
			{
				int hiringRate = 5;

				if (this->cityPopulation - this->workingPopulation < hiringRate)
				{
					hiringRate = this->cityPopulation - this->workingPopulation;
				}
				this->workingPopulation = this->workingPopulation += (hiringRate - factory->UpdateWorkersPopulation(hiringRate));
			}
		}

		Hospital *hospital = dynamic_cast<Hospital*>(building);
		if (hospital != nullptr)
		{
			hospital->BuildHospital();
		}

		FireBrigade *fireBrigade = dynamic_cast<FireBrigade*>(building);
		if (fireBrigade != nullptr)
		{
			fireBrigade->BuildFireBrigade();
		}

		PowerHouse *powerHouse = dynamic_cast<PowerHouse*>(building);
		if (powerHouse != nullptr)
		{
			if (this->cityPopulation > 0 && (this->cityPopulation - this->workingPopulation) > 0)
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

	this->cityPopulation = homePopulation;
}

void HoldGameplay::EventNewMonth()
{
	if (this->month >= 12)
	{
		this->month = 0;
		++this->year;
	}

	this->UpdateStatistics();

	this->gameEvent = GameEvent::NEW_MONTH;
	this->newspaper->SetIsTableOpen(true);
	this->newspaper->NewspaperEvent(TypeOfNewspaper::REGULAR);

	this->TornadoRandomEvent();

	//...SOON
}

void HoldGameplay::TornadoRandomEvent()
{
	if (randomEngine.RandomiseEvent(0, 3) <= 1)
	{
		this->ForceCycloneEvent();
	}
}

void HoldGameplay::EventNewYear()
{
	//... SOON
}

void HoldGameplay::Draw(sf::RenderWindow* renderTarget, float elapsedTime)
{
	std::vector<ID> structuresToDestroy;

	this->mapTile->DrawMap(renderTarget, elapsedTime,
		this->IDstructures.getObjects(), this->tornadoVector, this->fireVector);

	int iterator = 0;
	for (const auto & iterPictureInformation : pictureInformationVector)
	{
		this->pictureInformationVector[iterator]->DrawPictureInformation(renderTarget);
		iterator++;
	}


	iterator = 0;
	for (const auto & iterFireTmp : this->fireVector)
	{
		this->fireVector[iterator]->Draw(*this->ptrGame->window, elapsedTime);
		iterator++;
	}


	this->DestroyStructureID(structuresToDestroy);
}

void HoldGameplay::ForceRemovePictureIndormation(ID buildingID)
{
	int iterator = 0;
	for (iterPictureInformation = pictureInformationVector.begin(), iterator = 0;
		iterPictureInformation != pictureInformationVector.end(); iterPictureInformation++, iterator++)
	{
		if (pictureInformationVector[iterator]->GetPictureID() == buildingID)
		{
			delete pictureInformationVector[iterator];
			pictureInformationVector.erase(iterPictureInformation);
			return;
		}
	}
}

void HoldGameplay::RandomiseBuildings()
{
	std::random_device random;
	std::mt19937 g(random());

	//std::shuffle(this->IDstructures.getObjects().begin(), this->IDstructures.getObjects().end(), g);
}

void HoldGameplay::PushPictureInformationToVector(Structure* structure, PictureType pictureType, bool animationType)
{
	this->pictureInformation = new PictureInformation(structure->GetID());
	this->pictureInformation->InitializePictureInformation(pictureType);
	this->pictureInformation->SetPictureInformationPosition(structure->GetFixedPosition());
	this->pictureInformation->SetHoldInformation(animationType);
	this->pictureInformationVector.push_back(pictureInformation);
}

void HoldGameplay::Update(float elapsedTime)
{
	this->timeInGame += elapsedTime;
	this->actualTime += elapsedTime;

	if (this->actualTime >= (float)this->timeSpeed)
	{
		this->actualTime = 0;
		++this->day;
		this->EventNewDay();
	}

	for (auto & house : this->housesVector)
	{
		if (house != nullptr)
		{
			house->Update(elapsedTime);

			if (house->GetBuildStatus())
			{
				if (house->GetIsEpidemic())
				{
					if (!house->GetInformationAboutEpidemic())
					{
						this->PushPictureInformationToVector(house, PictureType::SICK, true);

						house->SetInformationAboutEpidemic(true);
					}

					for (auto & hospital : this->hospitalsVector)
					{
						if (hospital != nullptr)
						{
							if (hospital->GetBuildStatus())
							{
								hospital->DriveToBuildingStart(house);

								if (hospital->GetTravelDestinationSuccess())
								{
									hospital->AddPatients(house->SickPeopleToHospitalProcess());
									this->ForceRemovePictureIndormation(house->GetID());

									break;
								}
							}
						}
					}
				}
			}

			//for (auto & shopping : this->IDstructures.getObjects())
			for (auto & shopping : this->shopVector)
			{
				if (shopping != nullptr)
				{
					if (shopping->GetBuildStatus())
					{
						house->DriveToBuildingStart(shopping);
						break;
					}

				}
			}
		}
	}
	//update goods from factory to shop
		//Calling for more goods

	//Shop *shop = dynamic_cast<Shop*>(structure);
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
						this->PushPictureInformationToVector(shop, PictureType::GOODS_OUT, true);

						shop->SetAddedInformation(true);

					}

					for (auto &factory_delivery : factoryVector)
					{
						if (factory_delivery != nullptr)
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

										this->PushPictureInformationToVector(shop, PictureType::GOODS_IN);

										this->ForceRemovePictureIndormation(shop->GetID());

										break;
									}
								}
							}
						}
					}
				}
			}
		}

	for (auto & factory : this->factoryVector)
	{
		if (factory != nullptr)
		{
			factory->Update(elapsedTime);
		}
	}

	for (auto & powerHouse : this->powerhousesVector)
	{
		powerHouse->Update(elapsedTime);
	}

	for (auto & fireStation : this->fireBrigadeVector)
	{
		fireStation->Update(elapsedTime);
	}

	for (auto & structure : this->IDstructures.getObjects())
	{
		if (structure != nullptr)
		{
			for (auto & it : this->tornadoVector)
			{
				if (structure->GetSprite().getGlobalBounds().contains(it->GetTornadoSpritePosition()))
				{
					std::vector<ID> structuresToDestroy;
					std::vector<ID> connectionsToDestroy;

					structure->SetSelectionProcess(SelectionProcess::SELECTED);
					this->mapTile->ChangeTile(TileSpecialise::RUINS, this->IDstructures, structuresToDestroy,
						this->housesVector, this->shopVector, this->factoryVector, this->hospitalsVector,
						powerhousesVector, policeStationVector, fireBrigadeVector, highVoltageLinesVector,
						IDconnectings, connectionsToDestroy);

					this->DestroyStructureID(structuresToDestroy);
				}
			}

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

					structure->SetSelectionProcess(SelectionProcess::SELECTED);
					this->mapTile->ChangeTile(TileSpecialise::RUINS, this->IDstructures, structuresToDestroy,
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
					
			
					fireBrigade->DriveToBuildingStart(structure);

					if (fireBrigade->GetTravelDestinationSuccess())
					{
						for (auto & fireIt : this->fireVector)
						{
							fireIt->FireBrigadeEvent(structure->GetPosition());
						}
						structure->SetStructureOnFire(false);
					}
				
					//....



					
				}
			}
		}

		

	}


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

	this->TaxesManaging();
	this->UpdateStatisticsTable();
	this->UpdateDisasters(elapsedTime);
}

void HoldGameplay::DestroyedByDisaster(ID buildingID)
{
	int iterator = 0;

	for (auto houseIterator = this->housesVector.begin(); houseIterator != this->housesVector.end();
		iterator++, houseIterator++)
	{
		if (housesVector[iterator]->GetID() == buildingID)
		{
			housesVector.erase(houseIterator);
			break;
		}
	}

}

void HoldGameplay::UpdateDisasters(float elapsedTime)
{
	int iterator = 0;
	for (const auto & iterTornado : tornadoVector)
	{
		switch (this->timeSpeed)
		{
		case TimeSpeed::SLOW:
			this->tornadoVector[iterator]->SetTornadoLifeTime(1000);
			this->tornadoVector[iterator]->SetTornadoSpeed(10);
			break;
		case TimeSpeed::NORMAL:
			this->tornadoVector[iterator]->SetTornadoLifeTime(500);
			this->tornadoVector[iterator]->SetTornadoSpeed(20);
			break;
		case TimeSpeed::FAST:
			this->tornadoVector[iterator]->SetTornadoLifeTime(300);
			this->tornadoVector[iterator]->SetTornadoSpeed(40);
			break;
		case TimeSpeed::UBER:
			this->tornadoVector[iterator]->SetTornadoLifeTime(200);
			this->tornadoVector[iterator]->SetTornadoSpeed(50);
			break;
		}

		this->tornadoVector[iterator]->UpdateDisaster(elapsedTime);
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
	}
}

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

void HoldGameplay::DecreaseCityFunds(int totalCost)
{
	this->money -= totalCost;
}

#pragma endregion

#pragma region Setters

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

int HoldGameplay::GetPopulation() const
{
	return this->cityPopulation;
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

GameEvent HoldGameplay::GetEventName() const
{
	return this->gameEvent;
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

int HoldGameplay::GetUnemployed() const
{
	return this->unemployedPopulation;
}

#pragma endregion