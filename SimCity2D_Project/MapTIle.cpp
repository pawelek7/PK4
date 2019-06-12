#include "MapTile.h"

#pragma region Constructors

MapTile::MapTile(const std::string & filename, std::shared_ptr<AssetsOfGame> ptrGame, unsigned int sizeOfMap, uint64_t seedMap)
	:LoadData(ptrGame)
{
	this->cityName = filename;
	this->CreateNewMap(filename, sizeOfMap, seedMap);
}

MapTile::MapTile(const std::string & filename, std::shared_ptr<AssetsOfGame> ptrGame)
	:LoadData(ptrGame)
{
	this->cityName = filename;
}

MapTile::~MapTile()
{
	if (this->pathRoad != nullptr)
	{
		delete this->pathRoad;
		this->pathRoad = nullptr;
	}

	if (this->pathVoltagePylons != nullptr)
	{
		delete this->pathVoltagePylons;
		this->pathVoltagePylons = nullptr;
	}

	if (this->mapGenerator != nullptr)
	{
		delete this->mapGenerator;
		this->mapGenerator = nullptr;
	}
}

#pragma endregion

#pragma region Class_Methods

void MapTile::InitialiseMapEnvironment()
{
	this->InitializeShaders(); //initialize shaders

	this->ptrGame->textureManager.LoadAsset("selection", "Resources/Textures/selection.png"); //load cursor from folder of resources
	this->ptrGame->textureManager.LoadAsset("selection2", "Resources/Textures/selection2.png");
	this->cursorSmall.setTexture(this->ptrGame->textureManager.GetAsset("selection")); //set texture cursor
	this->cursorBig.setTexture(this->ptrGame->textureManager.GetAsset("selection2"));
	this->cursorSmall.setOrigin(0, TILE_SIZE*(2)); //sec cursor origin
	this->cursorBig.setOrigin(0, TILE_SIZE*(2));
}

void MapTile::CreateNewMap(const std::string & filename, unsigned int sizeOfMap, uint64_t seedMap)
{
	this->sizeOfMap = sizeOfMap; //size of map

	this->pathRoad = new PathFinding(this->sizeOfMap); //create path road
	this->pathVoltagePylons = new PathFinding(this->sizeOfMap); //create path voltage pylons

	tilesVector.ReshapeVector(sizeOfMap, sizeOfMap);

	SeedGenerator seed = SeedGenerator(seedMap); //seed of map
	mapGenerator = new MapGenerator(seed); //generate map depending on seed
	mapGenerator->GenerateMapBaseOnSeed(sizeOfMap);

	for (int i = 0; i < this->sizeOfMap; i++) //put tiles on map
	{
		for (int j = 0; j < this->sizeOfMap; j++)
		{
			if (mapGenerator->GetBasicTileMap()[i*this->sizeOfMap + j] == SmallTile::TileSpecialise::FLOOR)
			{
				this->tilesVector.AddElements(i, j, CreateTile(SmallTile::TileSpecialise::FLOOR));
			}
			else if (mapGenerator->GetBasicTileMap()[i*this->sizeOfMap + j] == SmallTile::TileSpecialise::WATER)
			{
				this->tilesVector.AddElements(i, j, CreateTile(SmallTile::TileSpecialise::WATER));
			}
			else if (mapGenerator->GetBasicTileMap()[i*this->sizeOfMap + j] == SmallTile::TileSpecialise::TREE)
			{
				this->tilesVector.AddElements(i, j, CreateTile(SmallTile::TileSpecialise::TREE));
			}
			else if (mapGenerator->GetBasicTileMap()[i*this->sizeOfMap + j] == SmallTile::TileSpecialise::ROCK)
			{
				this->tilesVector.AddElements(i, j, CreateTile(SmallTile::TileSpecialise::ROCK));
			}
			else
			{
				this->tilesVector.AddElements(i, j, CreateTile(SmallTile::TileSpecialise::VOID));
			}
			this->tilesVector.GetElements(i, j)->SetPosition(i, j);
		}
	}

	this->InitialiseMapEnvironment();
}

void MapTile::LoadMap(const std::string & fileName, IDvector<Structure*> & structuresWithID,
	std::vector<House*> & houseVector, std::vector<Shop*> & shopVector, std::vector<Factory*> & factoryVector,
	std::vector<Hospital*> & hospitalVector, std::vector<PowerHouse*> & powerHouseVector, std::vector<PoliceStation*> & policeStationVector,
	std::vector<FireBrigade*> & fireBrigadeVector, std::vector<HighVoltageLines*> & highVoltageLinesVector,
	IDvector<RequireConnecting*> & IDconnectings)
{
	std::ifstream readFile;
	readFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);

	try {

		//open file to load map
		try {
			readFile.open("Resources/Maps/" + this->cityName + ".bin", std::ios::in | std::ios::binary);
			if (!readFile)
			{
				throw std::runtime_error("Could not open the save file!");
			}
			//read size of map
			readFile.read((char*)&this->sizeOfMap, sizeof(unsigned int));

			this->sizeOfMap = sizeOfMap;

			this->pathRoad = new PathFinding(this->sizeOfMap);
			this->pathVoltagePylons = new PathFinding(this->sizeOfMap);

			tilesVector.ReshapeVector(this->sizeOfMap, this->sizeOfMap);

			std::vector<bool> drivingPathVector;

			//read path road
			int drivingPathSize;
			readFile.read((char*)&drivingPathSize, sizeof(int));

			for (int i = 0; i < drivingPathSize; i++)
			{
				bool drivingPathTmp;
				readFile.read((char*)&drivingPathTmp, sizeof(bool));
				drivingPathVector.push_back(drivingPathTmp);
			}

			this->pathRoad->SetConnection(drivingPathVector);

			//read voltage path
			std::vector<bool> voltagePathVector;
			int voltagePathSize;
			readFile.read((char*)&voltagePathSize, sizeof(int));

			for (int i = 0; i < voltagePathSize; i++)
			{
				bool voltafePathTmp;
				readFile.read((char*)&voltafePathTmp, sizeof(bool));
				voltagePathVector.push_back(voltafePathTmp);
			}
			this->pathVoltagePylons->SetConnection(voltagePathVector);

			//read tiles
			for (int i = 0; i < this->sizeOfMap; i++)
			{
				for (int j = 0; j < this->sizeOfMap; j++)
				{
					//read tile informations
					SmallTile::TypeOfTile typeOfTile;
					readFile.read((char*)&typeOfTile, sizeof(SmallTile::TypeOfTile));

					SmallTile::TileSpecialise tileSpecialise;
					readFile.read((char*)&tileSpecialise, sizeof(SmallTile::TileSpecialise));

					int height;
					readFile.read((char*)&height, sizeof(int));

					int tileVariant;
					readFile.read((char*)&tileVariant, sizeof(int));

					bool isAnimation;
					readFile.read((char*)&isAnimation, sizeof(bool));

					std::string textureName;
					size_t len = 0;
					readFile.read((char*)&len, sizeof(size_t));
					char* temp = new char[len + 1];
					readFile.read(temp, len);
					temp[len] = '\0';
					textureName = temp;
					delete[]temp;

					this->tilesVector.AddElements(i, j, CreateTile(tileSpecialise));
					this->tilesVector.GetElements(i, j)->InitializeSmallTileParameters(height, tileVariant, typeOfTile, tileSpecialise, isAnimation, textureName);
					this->tilesVector.GetElements(i, j)->SetPosition(i, j);

					sf::Vector2f position;
					position.x = (j - i) * TILE_SIZE + this->sizeOfMap * TILE_SIZE;
					position.y = (j + i) * TILE_SIZE * 0.5f;
					this->tilesVector.GetElements(i, j)->SetSpritePosition(position);

					//--------------------

					//read structure information
					if (this->tilesVector.GetElements(i, j).get()->GetIsBuilding())
					{
						Structure *structure = static_cast<Structure*>(tilesVector.GetElements(i, j).get());

						ID buildingID;
						readFile.read((char*)&buildingID, sizeof(ID));

						Structure::VehicleVisible vehicleVisible;
						readFile.read((char*)&vehicleVisible, sizeof(Structure::VehicleVisible));

						unsigned int actualLevel;
						readFile.read((char*)&actualLevel, sizeof(unsigned int));

						unsigned int heightBuilding;//??
						readFile.read((char*)&heightBuilding, sizeof(int));

						int buildDays;
						readFile.read((char*)&buildDays, sizeof(int));

						float happiness;
						readFile.read((char*)&happiness, sizeof(float));

						int propertyTaxesStructure;
						readFile.read((char*)&propertyTaxesStructure, sizeof(int));

						int cityOrdinancesStructure;
						readFile.read((char*)&cityOrdinancesStructure, sizeof(int));

						int robberyCounter;
						readFile.read((char*)&robberyCounter, sizeof(int));

						float propertyTaxesPercentage;
						readFile.read((char*)&propertyTaxesPercentage, sizeof(float));

						float cityOrdinancesPercentage;
						readFile.read((char*)&cityOrdinancesPercentage, sizeof(float));

						bool strike;
						readFile.read((char*)&strike, sizeof(bool));

						bool thiefCaught;
						readFile.read((char*)&thiefCaught, sizeof(bool));

						bool informationNoEnergy;
						readFile.read((char*)&informationNoEnergy, sizeof(bool));

						bool informationThief;
						readFile.read((char*)&informationThief, sizeof(bool));

						bool informationStrike;
						readFile.read((char*)&informationStrike, sizeof(bool));

						bool hasEnergy;
						readFile.read((char*)&hasEnergy, sizeof(bool));

						bool buildedStructure;
						readFile.read((char*)&buildedStructure, sizeof(bool));

						bool vehicleInUse;
						readFile.read((char*)&vehicleInUse, sizeof(bool));

						bool callBackVehicle;
						readFile.read((char*)&callBackVehicle, sizeof(bool));

						bool travelDestinationSuccess;
						readFile.read((char*)&travelDestinationSuccess, sizeof(bool));

						bool structureOnFire;
						readFile.read((char*)&structureOnFire, sizeof(bool));

						bool thiefInBuilding;
						readFile.read((char*)&thiefInBuilding, sizeof(bool));

						bool hasVehicle;
						readFile.read((char*)&hasVehicle, sizeof(bool));

						structure->InitializeStructureParameters(buildingID, vehicleVisible, actualLevel,
							heightBuilding, buildDays, happiness, propertyTaxesStructure, cityOrdinancesStructure,
							robberyCounter, propertyTaxesPercentage, cityOrdinancesPercentage, strike, thiefCaught,
							false, false, false, hasEnergy, buildedStructure,
							false, callBackVehicle, travelDestinationSuccess, structureOnFire, thiefInBuilding,
							hasVehicle);

						structure->SetPathRoad(this->pathRoad);
						structure->SetPosition(i, j);

						//	structuresWithID.Push(structure);

						if (this->tilesVector.GetElements(i, j).get()->GetIsHouse())
						{
							//read house
							House *house = dynamic_cast<House*>(structure);

							int household;
							readFile.read((char*)&household, sizeof(int));

							int maxPopOnLvl;
							readFile.read((char*)&maxPopOnLvl, sizeof(int));

							int buildingDays; //??
							readFile.read((char*)&buildingDays, sizeof(int));

							int sickDomators;
							readFile.read((char*)&sickDomators, sizeof(int));

							int reservedSpace;
							readFile.read((char*)&reservedSpace, sizeof(int));

							bool abandonedHouse;
							readFile.read((char*)&abandonedHouse, sizeof(bool));

							bool connectedToPower; //??
							readFile.read((char*)&connectedToPower, sizeof(bool));

							bool addedNewDomatros;
							readFile.read((char*)&addedNewDomatros, sizeof(bool));

							bool epidemic;
							readFile.read((char*)&epidemic, sizeof(bool));

							bool informationAboutEpidemic;
							readFile.read((char*)&informationAboutEpidemic, sizeof(bool));

							House::HappinessEvent happinessEvent;
							readFile.read((char*)&happinessEvent, sizeof(House::HappinessEvent));

							house->InitializeHouseParameters(household, maxPopOnLvl, buildingDays, sickDomators, reservedSpace,
								abandonedHouse, connectedToPower, addedNewDomatros, epidemic, informationAboutEpidemic,
								happinessEvent);

							structure = dynamic_cast<Structure*>(house);

							houseVector.push_back(house);
							house->ChangeTexture();
							ID newID = structuresWithID.Push(structure);
							structure->SetID(newID);

						}
						else if (this->tilesVector.GetElements(i, j).get()->GetIsShops())
						{
							//read shop
							Shop *shop = dynamic_cast<Shop*>(structure);

							int employees;
							readFile.read((char*)&employees, sizeof(int));

							int maxEmployeesOnLvl;
							readFile.read((char*)&maxEmployeesOnLvl, sizeof(int));

							int customers;
							readFile.read((char*)&customers, sizeof(int));

							int maxCustomersPerLvl;
							readFile.read((char*)&maxCustomersPerLvl, sizeof(int));

							int goods;
							readFile.read((char*)&goods, sizeof(int));

							int maxGoodsInShop;
							readFile.read((char*)&maxGoodsInShop, sizeof(int));

							bool emptyWarehouse;
							readFile.read((char*)&emptyWarehouse, sizeof(bool));

							bool addedInformation;
							readFile.read((char*)&addedInformation, sizeof(bool));

							shop->InitializeShopParameters(employees, maxEmployeesOnLvl, customers, maxCustomersPerLvl,
								goods, maxGoodsInShop, emptyWarehouse, addedInformation);

							shop->ChangeTexture();
							shopVector.push_back(shop);
							structure = dynamic_cast<Structure*>(shop);
							ID newID = structuresWithID.Push(structure);
							structure->SetID(newID);

						}
						else if (this->tilesVector.GetElements(i, j).get()->GetIsFactory())
						{
							//read factory
							Factory *factory = dynamic_cast<Factory*>(structure);

							int workers;
							readFile.read((char*)&workers, sizeof(int));

							int maxWorkersPerLvl;
							readFile.read((char*)&maxWorkersPerLvl, sizeof(int));

							int storedGoods;
							readFile.read((char*)&storedGoods, sizeof(int));

							int vehicleCargo;
							readFile.read((char*)&vehicleCargo, sizeof(int));

							int maxGoodsStorage;
							readFile.read((char*)&maxGoodsStorage, sizeof(int));

							factory->InitializeFactoryParameters(workers, maxWorkersPerLvl, storedGoods, vehicleCargo, maxGoodsStorage);

							factory->ChangeTexture();
							factoryVector.push_back(factory);
							structure = dynamic_cast<Structure*>(factory);
							ID newID = structuresWithID.Push(structure);
							structure->SetID(newID);
						}
						else if (this->tilesVector.GetElements(i, j).get()->GetIsHospital())
						{
							//read hospital
							Hospital *hospital = dynamic_cast<Hospital*>(structure);

							IDvector<Hospital::Patient*> patients;
							Hospital::Patient* patient = nullptr;
							patient = new Hospital::Patient();

							int patientAmount;
							readFile.read((char*)&patientAmount, sizeof(int));

							for (int i = 0; i < patientAmount; i++)
							{
								readFile.read((char*)&patient->daysToHeal, sizeof(Hospital::Patient::daysToHeal));
								readFile.read((char*)&patient->homeID, sizeof(Hospital::Patient::homeID));
								readFile.read((char*)&patient->patientID, sizeof(Hospital::Patient::patientID));
								readFile.read((char*)&patient->returnToHome, sizeof(Hospital::Patient::returnToHome));

								ID patientID = patients.Push(patient);
								patient->patientID = patientID;
							}

							int hospitalWorkers;
							readFile.read((char*)&hospitalWorkers, sizeof(int));

							int maxHospitalWorkets;
							readFile.read((char*)&maxHospitalWorkets, sizeof(int));

							int maxPatients;
							readFile.read((char*)&maxPatients, sizeof(int));

							int healedPatients;
							readFile.read((char*)&healedPatients, sizeof(int));

							int healthAndWalfareStructure;//fix later this for all 
							readFile.read((char*)&healthAndWalfareStructure, sizeof(int));

							float healthAndWalfarePercentage;
							readFile.read((char*)&healthAndWalfarePercentage, sizeof(float));

							hospital->InitializeHospitalParameters(patients, hospitalWorkers, maxHospitalWorkets,
								maxPatients, healedPatients, healthAndWalfareStructure, healthAndWalfarePercentage);

							hospital->ChangeTexture();
							hospitalVector.push_back(hospital);
							structure = dynamic_cast<Structure*>(hospital);
							ID newID = structuresWithID.Push(structure);
							structure->SetID(newID);
						}
						else if (this->tilesVector.GetElements(i, j).get()->GetIsFireBrigade())
						{
							//read fireBrigade
							FireBrigade *fireBrigade = dynamic_cast<FireBrigade*>(structure);

							int extinguishedFires;
							readFile.read((char*)&extinguishedFires, sizeof(int));

							int fireFighters;
							readFile.read((char*)&fireFighters, sizeof(int));

							int maxFireFighters;
							readFile.read((char*)&maxFireFighters, sizeof(int));

							int fireDepartamentStructure;//fix this later
							readFile.read((char*)&fireDepartamentStructure, sizeof(int));

							float fireDepartamentPercentage;
							readFile.read((char*)&fireDepartamentPercentage, sizeof(float));

							fireBrigade->InitializeFireBrigadeParameters(fireFighters, maxFireFighters, fireDepartamentStructure,
								fireDepartamentPercentage, extinguishedFires);

							fireBrigade->ChangeTexture();
							fireBrigadeVector.push_back(fireBrigade);
							structure = dynamic_cast<Structure*>(fireBrigade);
							ID newID = structuresWithID.Push(structure);
							structure->SetID(newID);
						}
						else if (this->tilesVector.GetElements(i, j).get()->GetIsPoliceStation())
						{
							//read policeStation
							PoliceStation *policeStation = dynamic_cast<PoliceStation*>(structure);

							IDvector<PoliceStation::Prisoner*> prisonersVector;
							PoliceStation::Prisoner* prisoner = nullptr;
							prisoner = new PoliceStation::Prisoner();

							int prisonersNoumber;

							readFile.read((char*)&prisonersNoumber, sizeof(int));

							for (int i = 0; i < prisonersNoumber; i++)
							{
								readFile.read((char*)&prisoner->daysOfDetention, sizeof(PoliceStation::Prisoner::daysOfDetention));
								readFile.read((char*)&prisoner->idPrisoner, sizeof(PoliceStation::Prisoner::idPrisoner));
								readFile.read((char*)&prisoner->isFree, sizeof(PoliceStation::Prisoner::isFree));
								ID prisonerID = prisonersVector.Push(prisoner);
								prisoner->idPrisoner = prisonerID;
							}

							int policemen;
							readFile.read((char*)&policemen, sizeof(int));

							int maxPolicemen;
							readFile.read((char*)&maxPolicemen, sizeof(int));

							int policeDepartmentStructure;//fix this later
							readFile.read((char*)&policeDepartmentStructure, sizeof(int));

							float policeDepartmentPercenage;
							readFile.read((char*)&policeDepartmentPercenage, sizeof(float));

							int prisoners;
							readFile.read((char*)&prisoners, sizeof(int));

							int maxPrisoners;
							readFile.read((char*)&maxPrisoners, sizeof(int));

							policeStation->InitializePoliceStationParameters(prisonersVector, policemen, maxPolicemen,
								policeDepartmentStructure, policeDepartmentPercenage, prisoners, maxPrisoners);

							policeStation->ChangeTexture();
							policeStationVector.push_back(policeStation);
							structure = dynamic_cast<Structure*>(policeStation);
							ID newID = structuresWithID.Push(structure);
							structure->SetID(newID);
						}
						else if (this->tilesVector.GetElements(i, j).get()->GetIsPowerHouse())
						{
							//read Power House
							PowerHouse *powerHouse = dynamic_cast<PowerHouse*>(structure);

							int producedEnergy;
							readFile.read((char*)&producedEnergy, sizeof(int));

							int maxEnergyStorage;
							readFile.read((char*)&maxEnergyStorage, sizeof(int));

							int employess;
							readFile.read((char*)&employess, sizeof(int));

							int maxEmployess;
							readFile.read((char*)&maxEmployess, sizeof(int));

							bool canShareEnergy;
							readFile.read((char*)&canShareEnergy, sizeof(bool));

							powerHouse->InitializePowerHouseParameters(producedEnergy, maxEnergyStorage, employess, maxEmployess, canShareEnergy);

							powerHouse->ChangeTexture();
							powerHouseVector.push_back(powerHouse);
							structure = dynamic_cast<Structure*>(powerHouse);
							ID newID = structuresWithID.Push(structure);
							structure->SetID(newID);
						}
					}

					if (this->tilesVector.GetElements(i, j).get()->GetIsVoltagePylon())
					{
						//read Require Connecting
						RequireConnecting *requireConnecting = static_cast<RequireConnecting*>(tilesVector.GetElements(i, j).get());

						int height;
						readFile.read((char*)&height, sizeof(int));

						requireConnecting->InitializeRequireConnectingParameters(height);
						//	IDconnectings.Push(requireConnecting);

							//read Voltage Pylons
						HighVoltageLines *highVoltageLines = dynamic_cast<HighVoltageLines*>(requireConnecting);
						if (highVoltageLines != nullptr)
						{
							bool connectedToPowerStation;
							readFile.read((char*)&connectedToPowerStation, sizeof(bool));

							ID voltageLineID;
							readFile.read((char*)&voltageLineID, sizeof(ID));

							int pylonCoordinatesX;
							readFile.read((char*)&pylonCoordinatesX, sizeof(int));

							int pylonCoordinatesY;
							readFile.read((char*)&pylonCoordinatesY, sizeof(int));

							std::vector<sf::Vector2i> powerStationCoordinates;
							int size;

							readFile.read((char*)&size, sizeof(int));

							int x;
							int y;

							for (int i = 0; i < size; i++)
							{
								readFile.read((char*)&x, sizeof(int));
								readFile.read((char*)&y, sizeof(int));

								powerStationCoordinates.push_back(sf::Vector2i(x, y));
							}

							sf::Vector2i pylco = sf::Vector2i(pylonCoordinatesX, pylonCoordinatesY);

							highVoltageLines->InitializeHighVoltageLinesParameters(connectedToPowerStation, voltageLineID,
								pylco, powerStationCoordinates);

							highVoltageLines->SetPylonCoordinates(sf::Vector2i(i, j));
							highVoltageLines->SetPathPylon(this->pathVoltagePylons);
							highVoltageLinesVector.push_back(highVoltageLines);

							requireConnecting = dynamic_cast<RequireConnecting*>(highVoltageLines);

							//voltage lines
							ID _id = IDconnectings.Push(highVoltageLines);
							highVoltageLines->SetHighVoltageLinesID(_id);
						}
					}
				}
			}
			readFile.close();
		}
		catch (std::runtime_error & e)
		{
			std::cout << e.what() << std::endl;
			this->CreateNewMap(fileName, 32, 1);
		}

	}
	catch (const std::ifstream::failure & e)
	{
		std::cout << "Reading map error: " << e.what() << std::endl;
		this->CreateNewMap(fileName, 32, 1);
	}
	catch (...)
	{
		std::cout << "File error" << std::endl;
		this->CreateNewMap(fileName, 32, 1);
	}

	this->InitialiseMapEnvironment();
}

void MapTile::SaveMap()
{
	//open file to save map

	std::ofstream saveFile;
	saveFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);

	try
	{
		try {
			saveFile.open("Resources/Maps/" + this->cityName + ".bin", std::ios::out | std::ios::binary);

			if (!saveFile)
			{
				throw std::runtime_error("Could not save map!");
			}
			saveFile.write((char*)&this->sizeOfMap, sizeof(unsigned int));

			//save driving path
			std::vector<bool> drivingPathVector = this->pathRoad->GetConnection();

			int drivingPathSize = drivingPathVector.size();
			saveFile.write((char*)&drivingPathSize, sizeof(int));

			for (int i = 0; i < drivingPathSize; i++)
			{
				bool isPath = drivingPathVector[i];
				saveFile.write((char*)&isPath, sizeof(bool));
			}

			//save pylons path
			std::vector<bool> voltagePathVector = this->pathVoltagePylons->GetConnection();

			int voltagePathSize = voltagePathVector.size();
			saveFile.write((char*)&voltagePathSize, sizeof(int));

			for (int i = 0; i < voltagePathSize; i++)
			{
				bool isPath = voltagePathVector[i];
				saveFile.write((char*)&isPath, sizeof(bool));
			}

			for (auto & it : tilesVector.GetVector())
			{
				//save tile informations
				SmallTile::TypeOfTile typeOfTile = it.get()->GetTypeOfTile();
				saveFile.write((char*)&typeOfTile, sizeof(SmallTile::TypeOfTile));

				SmallTile::TileSpecialise tileSpecialise = it.get()->GetTileSpecialise();
				saveFile.write((char*)&tileSpecialise, sizeof(SmallTile::TileSpecialise));

				int height = it.get()->GetHeight();
				saveFile.write((char*)&height, sizeof(int));

				int tileVariant = it.get()->GetTileVariant();
				saveFile.write((char*)&tileVariant, sizeof(int));

				bool isAnimation = it.get()->GetIsAnimation();
				saveFile.write((char*)&isAnimation, sizeof(bool));

				std::string tmpTextureName = it.get()->GetTextureName();
				size_t len = tmpTextureName.size();
				saveFile.write((char*)&len, sizeof(size_t));
				saveFile.write(tmpTextureName.c_str(), tmpTextureName.length());

				//-----------------------------------------------

				//save structure informations
				Structure *structure = dynamic_cast<Structure*>(it.get());
				if (structure != nullptr)
				{
					ID buildingID = structure->GetID();
					saveFile.write((char*)&buildingID, sizeof(ID));

					Structure::VehicleVisible vehicleVisible = structure->GetVehicleVisible();
					saveFile.write((char*)&vehicleVisible, sizeof(Structure::VehicleVisible));

					unsigned int actualLevel = structure->GetActualLevel();
					saveFile.write((char*)&actualLevel, sizeof(unsigned int));

					unsigned int heightBuilding = structure->GetStructureHeight(); //??
					saveFile.write((char*)&heightBuilding, sizeof(int));

					int buildDays = structure->GetBuildDays();
					saveFile.write((char*)&buildDays, sizeof(int));

					float happiness = structure->GetHappiness();
					saveFile.write((char*)&happiness, sizeof(float));

					int propertyTaxesStructure = structure->GetPropertyTaxesStructure();
					saveFile.write((char*)&propertyTaxesStructure, sizeof(int));

					int cityOrdinancesStructure = structure->GetCityOrdinancesStructure();
					saveFile.write((char*)&cityOrdinancesStructure, sizeof(int));

					int robberyCounter = structure->GetRobberryCounter();
					saveFile.write((char*)&robberyCounter, sizeof(int));

					float propertyTaxesPercentage = structure->GetPropertyTaxesPercentage();
					saveFile.write((char*)&propertyTaxesPercentage, sizeof(float));

					float cityOrdinancesPercentage = structure->GetCityOrdinancesPercentage();
					saveFile.write((char*)&cityOrdinancesPercentage, sizeof(float));

					bool strike = structure->GetIsStrike();
					saveFile.write((char*)&strike, sizeof(bool));

					bool thiefCaught = structure->GetThiefCaught();
					saveFile.write((char*)&thiefCaught, sizeof(bool));

					bool informationNoEnergy = structure->GetInformationNoEnergy();
					saveFile.write((char*)&informationNoEnergy, sizeof(bool));

					bool informationThief = structure->GetInformationThief();
					saveFile.write((char*)&informationThief, sizeof(bool));

					bool informationStrike = structure->GetInformationStrike();
					saveFile.write((char*)&informationStrike, sizeof(bool));

					bool hasEnergy = structure->GetHasEnergy();
					saveFile.write((char*)&hasEnergy, sizeof(bool));

					bool buildedStructure = structure->GetBuildStatus();
					saveFile.write((char*)&buildedStructure, sizeof(bool));

					bool vehicleInUse = structure->GetVehicleInUse();
					saveFile.write((char*)&vehicleInUse, sizeof(bool));

					bool callBackVehicle = structure->GetCallBackVehicle();
					saveFile.write((char*)&callBackVehicle, sizeof(bool));

					bool travelDestinationSuccess = structure->GetTravelDestinationSuccess();
					saveFile.write((char*)&travelDestinationSuccess, sizeof(bool));

					bool structureOnFire = structure->GetStructureOnFire();
					saveFile.write((char*)&structureOnFire, sizeof(bool));

					bool thiefInBuilding = structure->GetThiefInBuilding();
					saveFile.write((char*)&thiefInBuilding, sizeof(bool));

					bool hasVehicle = structure->GetHasVehicle();
					saveFile.write((char*)&hasVehicle, sizeof(bool));

					//bool remember route ??


				}

				//--------------------------

				//save house informations
				House *house = dynamic_cast<House*>(it.get());
				if (house != nullptr)
				{
					int household = house->GetHousehold();
					saveFile.write((char*)&household, sizeof(int));

					int maxPopOnLvl = house->GetMaxPopOnLvl();
					saveFile.write((char*)&maxPopOnLvl, sizeof(int));

					int buildingDays = house->GetBuildDays(); //??
					saveFile.write((char*)&buildingDays, sizeof(int));

					int sickDomators = house->GetSickPeopleNr();
					saveFile.write((char*)&sickDomators, sizeof(int));

					int reservedSpace = house->GetReservedSpace();
					saveFile.write((char*)&reservedSpace, sizeof(int));

					bool abandonedHouse = house->GetAbandonedHouse();
					saveFile.write((char*)&abandonedHouse, sizeof(bool));

					bool connectedToPower = house->GetHasEnergy(); //??
					saveFile.write((char*)&connectedToPower, sizeof(bool));

					bool addedNewDomatros = house->GetIsAddedNewDomators();
					saveFile.write((char*)&addedNewDomatros, sizeof(bool));

					bool epidemic = house->GetIsEpidemic();
					saveFile.write((char*)&epidemic, sizeof(bool));

					bool informationAboutEpidemic = house->GetInformationAboutEpidemic();
					saveFile.write((char*)&informationAboutEpidemic, sizeof(bool));

					House::HappinessEvent happinessEvent = house->GetHappinessEvent();
					saveFile.write((char*)&happinessEvent, sizeof(House::HappinessEvent));
				}

				//--------------------------

				//save shop informations
				Shop *shop = dynamic_cast<Shop*>(it.get());
				if (shop != nullptr)
				{
					int employees = shop->GetEmployessNr();
					saveFile.write((char*)&employees, sizeof(int));

					int maxEmployeesOnLvl = shop->GetMaxEmployessOnLvl();
					saveFile.write((char*)&maxEmployeesOnLvl, sizeof(int));

					int customers = shop->GetCustomers();
					saveFile.write((char*)&customers, sizeof(int));

					int maxCustomersPerLvl = shop->GetMaxCustomersOnLvl();
					saveFile.write((char*)&maxCustomersPerLvl, sizeof(int));

					int goods = shop->GetGoodsAmount();
					saveFile.write((char*)&goods, sizeof(int));

					int maxGoodsInShop = shop->GetMaxGoodsInShop();
					saveFile.write((char*)&maxGoodsInShop, sizeof(int));

					bool emptyWarehouse = shop->GetEmptyWarehouse();
					saveFile.write((char*)&emptyWarehouse, sizeof(bool));

					bool addedInformation = shop->GetAddedInformation();
					saveFile.write((char*)&addedInformation, sizeof(bool));
				}

				//save factory informations
				Factory *factory = dynamic_cast<Factory*>(it.get());
				if (factory != nullptr)
				{
					int workers = factory->GetWorkersAmount();
					saveFile.write((char*)&workers, sizeof(int));

					int maxWorkersPerLvl = factory->GetMaxWorkersPerLvl();
					saveFile.write((char*)&maxWorkersPerLvl, sizeof(int));

					int storedGoods = factory->GetGoodsAmounst();
					saveFile.write((char*)&storedGoods, sizeof(int));

					int vehicleCargo = factory->GetVehicleCargo();
					saveFile.write((char*)&vehicleCargo, sizeof(int));

					int maxGoodsStorage = factory->GetMaxGoodsStorage();
					saveFile.write((char*)&maxGoodsStorage, sizeof(int));
				}

				//save hospital informations
				Hospital *hospital = dynamic_cast<Hospital*>(it.get());
				if (hospital != nullptr)
				{
					Hospital::Patient patient;
					int patientAmount = 0;
					patientAmount = hospital->GetPatients().GetSize();

					saveFile.write((char*)&patient, sizeof(int));

					for (auto & it : hospital->GetPatients().GetObjects())
					{
						patient.daysToHeal = it->daysToHeal;
						patient.homeID = it->homeID;
						patient.patientID = it->patientID;
						patient.returnToHome = it->returnToHome;

						saveFile.write((char*)&patient.daysToHeal, sizeof(Hospital::Patient::daysToHeal));
						saveFile.write((char*)&patient.homeID, sizeof(Hospital::Patient::homeID));
						saveFile.write((char*)&patient.patientID, sizeof(Hospital::Patient::patientID));
						saveFile.write((char*)&patient.returnToHome, sizeof(Hospital::Patient::returnToHome));
					}

					int hospitalWorkers = hospital->GetHospitalWorkersAmount();
					saveFile.write((char*)&hospitalWorkers, sizeof(int));

					int maxHospitalWorkets = hospital->GetMaxHospitalWorkers();
					saveFile.write((char*)&maxHospitalWorkets, sizeof(int));

					int maxPatients = hospital->GetMaxPatients();
					saveFile.write((char*)&maxPatients, sizeof(int));

					int healedPatients = hospital->GetHealedPatients();
					saveFile.write((char*)&healedPatients, sizeof(int));

					int healthAndWalfareStructure = hospital->GetHealthAndWalfareStructure(); //fix later this for all 
					saveFile.write((char*)&healthAndWalfareStructure, sizeof(int));

					float healthAndWalfarePercentage = hospital->GetHealthAndWalfarePercentage();
					saveFile.write((char*)&healthAndWalfarePercentage, sizeof(float));
				}

				//save fire brigade informations
				FireBrigade *fireBrigade = dynamic_cast<FireBrigade*>(it.get());
				if (fireBrigade != nullptr)
				{
					int extinguishedFire = fireBrigade->GetExtinguishedFires();
					saveFile.write((char*)&extinguishedFire, sizeof(int));

					int fireFighters = fireBrigade->GetFirefightersAmount();
					saveFile.write((char*)&fireFighters, sizeof(int));

					int maxFireFighters = fireBrigade->GetMaxFireFighters();
					saveFile.write((char*)&maxFireFighters, sizeof(int));

					int fireDepartamentStructure = fireBrigade->GetFireDepartment(); //fix this later
					saveFile.write((char*)&fireDepartamentStructure, sizeof(int));

					float fireDepartamentPercentage = fireBrigade->GetFireDepartamentPercentage();
					saveFile.write((char*)&fireDepartamentPercentage, sizeof(float));
				}

				//save police station informations
				PoliceStation *policeStation = dynamic_cast<PoliceStation*>(it.get());
				if (policeStation != nullptr)
				{
					PoliceStation::Prisoner prisoner;
					int prisonersNoumber = policeStation->GetPrisonersVector().GetSize();

					saveFile.write((char*)&prisonersNoumber, sizeof(int));

					for (auto & it : policeStation->GetPrisonersVector().GetObjects())
					{
						prisoner.daysOfDetention = it->daysOfDetention;
						prisoner.idPrisoner = it->idPrisoner;
						prisoner.isFree = it->isFree;

						saveFile.write((char*)&prisoner.daysOfDetention, sizeof(PoliceStation::Prisoner::daysOfDetention));
						saveFile.write((char*)&prisoner.idPrisoner, sizeof(PoliceStation::Prisoner::idPrisoner));
						saveFile.write((char*)&prisoner.isFree, sizeof(PoliceStation::Prisoner::isFree));
					}

					int policemen = policeStation->GetPolicemen();
					saveFile.write((char*)&policemen, sizeof(int));

					int maxPolicemen = policeStation->GetMaxPolicemen();
					saveFile.write((char*)&maxPolicemen, sizeof(int));

					int policeDepartmentStructure = policeStation->GetPoliceDepartment(); //fix this later
					saveFile.write((char*)&policeDepartmentStructure, sizeof(int));

					float policeDepartmentPercenage = policeStation->GetPoliceDepartmentPercenatge();
					saveFile.write((char*)&policeDepartmentPercenage, sizeof(float));

					int prisoners = policeStation->GetPrisoners();
					saveFile.write((char*)&prisoners, sizeof(int));

					int maxPrisoners = policeStation->GetMaxPrisoners();
					saveFile.write((char*)&maxPrisoners, sizeof(int));
				}

				//save power house information
				PowerHouse *powerHouse = dynamic_cast<PowerHouse*>(it.get());
				if (powerHouse != nullptr)
				{
					int producedEnergy = powerHouse->GetProducedEnergy();
					saveFile.write((char*)&producedEnergy, sizeof(int));

					int maxEnergyStorage = powerHouse->GetMaxEnergyStorage();
					saveFile.write((char*)&maxEnergyStorage, sizeof(int));

					int employess = powerHouse->GetEmployessAmount();
					saveFile.write((char*)&employess, sizeof(int));

					int maxEmployess = powerHouse->GetMaxEmployess();
					saveFile.write((char*)&maxEmployess, sizeof(int));

					bool canShareEnergy = powerHouse->GetCanShareEnergy();
					saveFile.write((char*)&canShareEnergy, sizeof(bool));
				}

				//---------------------------------

				if (it.get()->GetIsVoltagePylon())
				{
					//save require connecting information
					RequireConnecting *requireConnecting = dynamic_cast<RequireConnecting*>(it.get());
					if (requireConnecting != nullptr)
					{
						int height = requireConnecting->GetHeight();
						saveFile.write((char*)&height, sizeof(int));
					}

					//save high voltage lines information
					HighVoltageLines *highVoltageLines = dynamic_cast<HighVoltageLines*>(it.get());
					if (highVoltageLines != nullptr)
					{
						bool connectedToPowerStation = highVoltageLines->GetConnectedToPowerStation();
						saveFile.write((char*)&connectedToPowerStation, sizeof(bool));

						ID voltageLineID = highVoltageLines->GetHighVoltageLinesID();
						saveFile.write((char*)&voltageLineID, sizeof(ID));

						int pylonCoordinatesX = highVoltageLines->GetPylonCoordinates().x;
						saveFile.write((char*)&pylonCoordinatesX, sizeof(int));

						int pylonCoordinatesY = highVoltageLines->GetPylonCoordinates().y;
						saveFile.write((char*)&pylonCoordinatesY, sizeof(int));

						std::vector<sf::Vector2i> pylonCoordinates = highVoltageLines->GetPowetStationCoordinates();
						int size = pylonCoordinates.size();

						saveFile.write((char*)&size, sizeof(int));

						for (int i = 0; i < size; i++)
						{
							int x = pylonCoordinates[i].x;
							int y = pylonCoordinates[i].y;

							saveFile.write((char*)&x, sizeof(int));
							saveFile.write((char*)&y, sizeof(int));
						}
					}
				}
			}
			saveFile.close();

			this->RememberAnotherFile();
		}
		catch (std::runtime_error & e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	catch (const std::ifstream::failure & e)
	{
		std::cout << "Saving map error: " << e.what() << std::endl;

	}
	catch (...)
	{
		std::cout << "File error" << std::endl;
	}
}



void MapTile::RememberAnotherFile()
{
	bool alreadyExisting = false;

	const char* search_term = this->cityName.c_str();
	size_t search_term_size = strlen(search_term);

	std::ifstream searchSave("Resources/Maps/Saves.bin", std::ios::in | std::ios::binary);

	if (searchSave.good())
	{
		searchSave.seekg(0, std::ios::end);
		size_t file_size = searchSave.tellg();
		searchSave.seekg(0, std::ios::beg);
		std::string file_content;
		file_content.reserve(file_size);
		char buffer[256];
		std::streamsize chars_read;

		while (searchSave.read(buffer, sizeof buffer), chars_read = searchSave.gcount())
		{
			file_content.append(buffer, chars_read);
		}

		if (searchSave.eof())
		{
			for (std::string::size_type offset = 0, found_at;
				file_size > offset &&
				(found_at = file_content.find(search_term, offset)) !=
				std::string::npos;
				offset = found_at + search_term_size)
			{
				//	std::cout << found_at << std::endl;
				alreadyExisting = true;
			}

		}
		searchSave.close();

		if (alreadyExisting == false)
		{
			std::ofstream multipleSaves("Resources/Maps/Saves.bin", std::ios::out | std::ios::binary | std::ios::app);

			if (multipleSaves.good())
			{
				size_t lengthName = cityName.size();

				multipleSaves.write((char*)&lengthName, sizeof(size_t));
				multipleSaves.write(cityName.c_str(), cityName.length());

				multipleSaves.close();
			}
		}
	}
}

void MapTile::DrawMap(sf::RenderWindow *window, float elapsedTime,
	const std::vector<Structure*> & structures, const std::vector<Tornado*> & tornados,
	const std::vector<Fire*> & fires)
{
	sf::Vector2f pos = this->ptrGame->camera.getCenter();

	fromX = pos.y / (TILE_SIZE)+pos.x / (2 * TILE_SIZE) - this->sizeOfMap * 0.5 - 0.5 - this->dravingDistance;
	fromY = pos.y / (TILE_SIZE)-pos.x / (2 * TILE_SIZE) + this->sizeOfMap * 0.5 + 0.5 - this->dravingDistance;
	toX = pos.y / (TILE_SIZE)+pos.x / (2 * TILE_SIZE) - this->sizeOfMap * 0.5 - 0.5 + this->dravingDistance;
	toY = pos.y / (TILE_SIZE)-pos.x / (2 * TILE_SIZE) + this->sizeOfMap  * 0.5 + 0.5 + this->dravingDistance;

	if (fromX < 0)
	{
		fromX = 0;
	}
	else if (fromX >= this->sizeOfMap)
	{
		fromX = this->sizeOfMap - 1;
		this->ptrGame->camera.move(-1000 * elapsedTime, 0);
	}
	if (fromY < 0)
	{
		fromY = 0;
	}
	else if (fromY >= this->sizeOfMap)
	{
		fromY = this->sizeOfMap - 1;
		this->ptrGame->camera.move(0, -1000 * elapsedTime);
	}
	if (toX < 0)
	{
		toX = 0;
		this->ptrGame->camera.move(1000 * elapsedTime, 0);
	}
	else if (toX >= this->sizeOfMap)
	{
		toX = this->sizeOfMap - 1;
	}
	if (toY < 0)
	{
		toY = 0;
		this->ptrGame->camera.move(0, 1000 * elapsedTime);
	}
	else if (toY >= this->sizeOfMap)
	{
		toY = this->sizeOfMap - 1;
	}

	for (int i = fromY; i < toY + 1; i++)
	{
		for (int j = fromX; j < toX + 1; j++)
		{
			sf::Vector2f position;

			position.x = (j - i) * TILE_SIZE + this->sizeOfMap * TILE_SIZE;
			position.y = (j + i) * TILE_SIZE * 0.5f;

			this->tilesVector.GetElements(i, j)->SetSpritePosition(position);

			this->tilesVector.GetElements(i, j)->Draw(*window, elapsedTime);

			if (tilesVector.GetElements(i, j)->GetIsRoad())
			{
				for (auto & it : structures)
				{
					if (it->GetHasVehicle() == true)
					{
						if (this->tilesVector.GetElements(i, j).get()->GetSprite().getGlobalBounds().contains(it->GetVehicle()->GetVehicleSprite().getPosition()))
						{
							it->GetVehicle()->DrawVehicle(window);
							it->GetVehicle()->ChangeVehicleSpeed(this->timeSpeed);
						}
					}
				}
			}

			for (auto & tornado : tornados)
			{
				if (tornado->GetDisasterMovableGlobalBounds().contains(this->tilesVector.GetElements(i, j).get()->GetFixedPosition()))
				{
					tornado->Draw(*window, elapsedTime);
				}
			}

			if (!prevCurFromTwo)
			{
				if (this->tilesVector.GetElements(i, j)->GetSprite().getGlobalBounds().contains(sf::Vector2f(this->ptrGame->window->mapPixelToCoords(sf::Mouse::getPosition(*this->ptrGame->window), this->ptrGame->camera))))
				{
					sf::Vector2f position = this->tilesVector.GetElements(i, j).get()->GetSpritePosition();
					if (this->tilesVector.GetElements(i, j)->GetTileSpecialise() == SmallTile::TileSpecialise::POWER_HOUSE)
					{

						this->cursorBig.setPosition(sf::Vector2f(position));
						this->ptrGame->window->draw(cursorBig);
					}
					else
					{
						this->cursorSmall.setPosition(sf::Vector2f(position));
						this->ptrGame->window->draw(cursorSmall);
					}

					this->prevCurFromTwo = true;
				}

			}

			UpdateTile(i, j);
		}
	}
	this->prevCurFromTwo = false;
}

void MapTile::UpdateTile(int i, int j)
{
	const SmallTile* neighbourhood[NEIGHBORING][NEIGHBORING];

	for (int di = -1; di <= 1; di++)
	{
		for (int dj = -1; dj <= 1; ++dj)
		{
			if (i + di >= 0 && i + di < static_cast<int>(this->sizeOfMap) &&
				j + dj >= 0 && j + dj < static_cast<int>(this->sizeOfMap))
			{
				neighbourhood[dj + 1][di + 1] = tilesVector.GetElements(i + di, j + dj).get();
			}
			else
			{
				neighbourhood[dj + 1][di + 1] = this->tilesMap[static_cast<int>(SmallTile::TypeOfTile::VOID)].get();
			}
		}
	}

	this->tilesVector.GetElements(i, j)->SetNewTileVariant(neighbourhood);
}

void MapTile::SelectTiles(sf::Vector2i from, sf::Vector2i to, SmallTile::TypeOfTile typeOfTile)
{
	if (to.x < from.x)
	{
		std::swap(from.x, to.x);
	}
	if (to.y < from.y)
	{
		std::swap(from.y, to.y);
	}
	if (to.x >= this->sizeOfMap)
	{
		to.x = this->sizeOfMap - 1;
	}
	else if (to.x < 0)
	{
		to.x = 0;
	}
	if (to.y >= this->sizeOfMap)
	{
		to.y = this->sizeOfMap - 1;
	}
	else if (to.y < 0)
	{
		to.y = 0;
	}
	if (from.x >= this->sizeOfMap)
	{
		from.x = this->sizeOfMap - 1;
	}
	else if (from.x < 0)
	{
		from.x = 0;
	}
	if (from.y >= this->sizeOfMap)
	{
		from.y = this->sizeOfMap - 1;
	}
	else if (from.y < 0)
	{
		from.y = 0;
	}

	for (int i = from.y; i <= to.y; i++)
	{
		for (int j = from.x; j <= to.x; j++)
		{
			const std::unique_ptr<SmallTile> & smallTile = tilesVector.GetElements(i, j);

			if (smallTile->GetTypeOfTile() != SmallTile::TypeOfTile::WATER)
			{
				smallTile->SetSelectionProcess(SmallTile::SelectionProcess::SELECTED);
				this->nrSelected++;
			}
			else
			{
				smallTile->SetSelectionProcess(SmallTile::SelectionProcess::ERROR);
			}
		}
	}
}

void MapTile::DeleteSelection()
{
	for (std::unique_ptr<SmallTile>& tile : this->tilesVector.GetVector())
	{
		tile->SetSelectionProcess(SmallTile::SelectionProcess::VOID);
	}
	this->nrSelected = 0;
}


void MapTile::ChangeSpecialTile(SmallTile::TileSpecialise tileSpecialise, IDvector<Structure*>& structuresWithID, std::vector<std::size_t> & structuresToRemove,
	std::vector<HighVoltageLines*> & highVoltageLinesVector, std::vector<PowerHouse*> & powerHouseVector,
	IDvector<RequireConnecting*> & IDconnectings)
{
	for (int i = 0; i < this->sizeOfMap; i++)
	{
		for (int j = 0; j < this->sizeOfMap; j++)
		{
			if (tileSpecialise == SmallTile::TileSpecialise::POWER_HOUSE)
			{
				if (tilesVector.GetElements(i, j)->GetSelectionProcess() == SmallTile::SelectionProcess::SELECTED &&
					tilesVector.GetElements(i + 1, j)->GetSelectionProcess() == SmallTile::SelectionProcess::SELECTED &&
					tilesVector.GetElements(i, j + 1)->GetSelectionProcess() == SmallTile::SelectionProcess::SELECTED &&
					tilesVector.GetElements(i + 1, j + 1)->GetSelectionProcess() == SmallTile::SelectionProcess::SELECTED)
				{
					if (tilesVector.GetElements(i, j)->GetTypeOfTile() == SmallTile::TypeOfTile::DIRT &&
						tilesVector.GetElements(i + 1, j)->GetTypeOfTile() == SmallTile::TypeOfTile::DIRT &&
						tilesVector.GetElements(i, j + 1)->GetTypeOfTile() == SmallTile::TypeOfTile::DIRT &&
						tilesVector.GetElements(i + 1, j + 1)->GetTypeOfTile() == SmallTile::TypeOfTile::DIRT)
					{
						this->tilesVector.AddElements(i + 1, j, CreateTile(tileSpecialise));
						this->tilesVector.AddElements(i, j, CreateTile(SmallTile::TileSpecialise::SPECTRUM_PLATE));
						this->tilesVector.AddElements(i + 1, j + 1, CreateTile(SmallTile::TileSpecialise::SPECTRUM_PLATE));
						this->tilesVector.AddElements(i, j + 1, CreateTile(SmallTile::TileSpecialise::SPECTRUM_PLATE));


						Structure *structure = static_cast<Structure*>(tilesVector.GetElements(i + 1, j).get());
						ID _id = structuresWithID.Push(structure);
						structure->SetID(_id);
						structure->SetPosition(i + 1, j);

						PowerHouse *powerHouse = dynamic_cast<PowerHouse*>(structure);
						if (powerHouse != nullptr)
						{
							powerHouseVector.push_back(powerHouse);
						}

						for (auto & pylons : highVoltageLinesVector)
						{
							pylons->AddPowerStationCoordinates(powerHouse->GetPosition());
						}

						this->pathVoltagePylons->AddConnection(i, j);
						this->pathVoltagePylons->AddConnection(i + 1, j);
						this->pathVoltagePylons->AddConnection(i + 1, j + 1);
						this->pathVoltagePylons->AddConnection(i, j + 1);

						sf::Vector2f position;

						position.x = (j - i) * TILE_SIZE + this->sizeOfMap * TILE_SIZE;
						position.y = (j + i) * TILE_SIZE * 0.5f;

						this->tilesVector.GetElements(i, j)->SetSpritePosition(position);

					}
				}
			}
		}
	}
}

void MapTile::ChangeTile(SmallTile::TileSpecialise tileSpecialise, IDvector<Structure*> & structuresWithID, std::vector<ID> & structuresToRemove,
	std::vector<House*> & houseVector, std::vector<Shop*> & shopVector, std::vector<Factory*> & factoryVector,
	std::vector<Hospital*> & hospitalVector, std::vector<PowerHouse*> & powerHouseVector, std::vector<PoliceStation*> & policeStationVector,
	std::vector<FireBrigade*> & fireBrigadeVector, std::vector<HighVoltageLines*> & highVoltageLinesVector,
	IDvector<RequireConnecting*> & IDconnectings, std::vector<ID> & connectionsToRemove)
{
	for (int i = 0; i < this->sizeOfMap; i++)
	{
		for (int j = 0; j < this->sizeOfMap; j++)
		{
			if (tilesVector.GetElements(i, j)->GetSelectionProcess() == SmallTile::SelectionProcess::SELECTED)
			{
				if (tileSpecialise != SmallTile::TileSpecialise::RUINS)
				{
					if ((tileSpecialise != SmallTile::TileSpecialise::FLOOR) && (tilesVector.GetElements(i, j)->GetIsRoad() || tilesVector.GetElements(i, j)->GetIsVoltagePylon()
						|| tilesVector.GetElements(i, j)->GetIsBuilding()) || tilesVector.GetElements(i, j).get()->GetTileSpecialise() == SmallTile::TileSpecialise::SPECTRUM_PLATE)
					{
						continue;
					}
				}

				if (tilesVector.GetElements(i, j)->GetIsRoad())
				{
					this->pathRoad->RemoveConnection(i, j);
				}
				else if (tilesVector.GetElements(i, j)->GetIsVoltagePylon())
				{
					this->pathVoltagePylons->RemoveConnection(i, j);

					HighVoltageLines* voltageLine = static_cast<HighVoltageLines*>(tilesVector.GetElements(i, j).get());
					connectionsToRemove.push_back(voltageLine->GetHighVoltageLinesID());

					int iterator = 0;
					for (auto pylonIt = highVoltageLinesVector.begin(); pylonIt != highVoltageLinesVector.end(); pylonIt++, iterator++)
					{
						if (highVoltageLinesVector[iterator]->GetHighVoltageLinesID() == voltageLine->GetHighVoltageLinesID())
						{
							highVoltageLinesVector.erase(pylonIt);
							break;
						}
					}
				}
				else if (tilesVector.GetElements(i, j)->GetIsBuilding())
				{
					Structure* structure = static_cast<Structure*>(tilesVector.GetElements(i, j).get());
					structuresToRemove.push_back(structure->GetID());

					//destroy vectors
					House* house = dynamic_cast<House*>(structure);
					if (house != nullptr)
					{
						int iterator = 0;
						for (auto houseIt = houseVector.begin(); houseIt != houseVector.end(); houseIt++, iterator++)
						{
							if (houseVector[iterator]->GetID() == structure->GetID())
							{
								houseVector.erase(houseIt);
								break;
							}
						}
					}
					else
					{
						Shop* shop = dynamic_cast<Shop*>(structure);

						if (shop != nullptr)
						{
							int iterator = 0;
							for (auto shopIt = shopVector.begin(); shopIt != shopVector.end(); shopIt++, iterator++)
							{
								if (shopVector[iterator]->GetID() == structure->GetID())
								{
									shopVector.erase(shopIt);
									break;
								}
							}
						}
						else
						{
							Factory* factory = dynamic_cast<Factory*>(structure);

							if (factory != nullptr)
							{
								int iterator = 0;
								for (auto factoryIt = factoryVector.begin(); factoryIt != factoryVector.end(); factoryIt++, iterator++)
								{
									if (factoryVector[iterator]->GetID() == structure->GetID())
									{
										factoryVector.erase(factoryIt);
										break;
									}
								}
							}
							else
							{
								Hospital* hospital = dynamic_cast<Hospital*>(structure);

								if (hospital != nullptr)
								{
									int iterator = 0;
									for (auto hospitalIt = hospitalVector.begin(); hospitalIt != hospitalVector.end(); hospitalIt++, iterator++)
									{
										if (hospitalVector[iterator]->GetID() == structure->GetID())
										{
											hospitalVector.erase(hospitalIt);
											break;
										}
									}
								}
								else
								{
									PowerHouse *powerHouse = dynamic_cast<PowerHouse*>(structure);

									if (powerHouse != nullptr)
									{
										for (auto & pylons : highVoltageLinesVector)
										{
											pylons->RemovePowerStationMemory(powerHouse->GetPosition());
										}

										int iterator = 0;
										for (auto powerStationIt = powerHouseVector.begin(); powerStationIt != powerHouseVector.end(); powerStationIt++, iterator++)
										{
											if (powerHouseVector[iterator]->GetID() == structure->GetID())
											{
												powerHouseVector.erase(powerStationIt);
												break;
											}
										}
										this->pathVoltagePylons->RemoveConnection(i, j);

										this->tilesVector.AddElements(i - 1, j, CreateTile(SmallTile::TileSpecialise::FLOOR));
										this->tilesVector.AddElements(i, j + 1, CreateTile(SmallTile::TileSpecialise::FLOOR));
										this->tilesVector.AddElements(i - 1, j + 1, CreateTile(SmallTile::TileSpecialise::FLOOR));

									}
									else
									{
										FireBrigade *fireStation = dynamic_cast<FireBrigade*>(structure);

										if (fireStation != nullptr)
										{
											int iterator = 0;
											for (auto fireStationIt = fireBrigadeVector.begin(); fireStationIt != fireBrigadeVector.end(); fireStationIt++, iterator++)
											{
												if (fireBrigadeVector[iterator]->GetID() == structure->GetID())
												{
													fireBrigadeVector.erase(fireStationIt);
													break;
												}
											}
										}
										else
										{
											PoliceStation *policeStation = dynamic_cast<PoliceStation*>(structure);

											if (policeStation != nullptr)
											{
												int iterator = 0;
												for (auto policeStationIt = policeStationVector.begin(); policeStationIt != policeStationVector.end(); policeStationIt++, iterator++)
												{
													if (policeStationVector[iterator]->GetID() == structure->GetID())
													{
														policeStationVector.erase(policeStationIt);
														break;
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}

				this->tilesVector.AddElements(i, j, CreateTile(tileSpecialise));

				if (tilesVector.GetElements(i, j)->GetIsBuilding())
				{
					Structure *structure = static_cast<Structure*>(tilesVector.GetElements(i, j).get());
					ID _id = structuresWithID.Push(structure);
					structure->SetID(_id);
					structure->SetPosition(i, j);
					structure->SetPathRoad(this->pathRoad);

					House* house = dynamic_cast<House*>(structure);
					if (house != nullptr)
					{
						houseVector.push_back(house);
					}
					else
					{
						Shop* shop = dynamic_cast<Shop*>(structure);

						if (shop != nullptr)
						{
							shopVector.push_back(shop);
						}
						else
						{
							Factory* factory = dynamic_cast<Factory*>(structure);

							if (factory != nullptr)
							{
								factoryVector.push_back(factory);
							}
							else
							{
								Hospital *hospital = dynamic_cast<Hospital*>(structure);

								if (hospital != nullptr)
								{
									hospitalVector.push_back(hospital);
								}
								else
								{
									PowerHouse *powerHouse = dynamic_cast<PowerHouse*>(structure);

									if (powerHouse != nullptr)
									{
										powerHouseVector.push_back(powerHouse);
									}
									else
									{

										FireBrigade *fireBrigade = dynamic_cast<FireBrigade*>(structure);

										if (fireBrigade != nullptr)
										{
											fireBrigadeVector.push_back(fireBrigade);
										}
										else
										{
											PoliceStation *policeStation = dynamic_cast<PoliceStation*>(structure);

											if (policeStation != nullptr)
											{
												policeStationVector.push_back(policeStation);
											}
										}
									}
								}
							}
						}
					}

					if (structure->GetIsPowerHouse())
					{
						this->pathVoltagePylons->AddConnection(i, j);
					}

				}
				else if (tilesVector.GetElements(i, j)->GetIsRoad())
				{
					this->pathRoad->AddConnection(i, j);
				}
				else if (tilesVector.GetElements(i, j)->GetIsVoltagePylon())
				{
					this->pathVoltagePylons->AddConnection(i, j);

					HighVoltageLines *highVoltageLine = static_cast<HighVoltageLines*>(tilesVector.GetElements(i, j).get());

					for (auto & powerHouse : powerHouseVector)
					{
						highVoltageLine->AddPowerStationCoordinates(powerHouse->GetPosition());
					}

					ID _id = IDconnectings.Push(highVoltageLine);
					highVoltageLine->SetHighVoltageLinesID(_id);
					highVoltageLine->SetPylonCoordinates(sf::Vector2i(i, j));
					highVoltageLine->SetPathPylon(this->pathVoltagePylons);
					highVoltageLinesVector.push_back(highVoltageLine);
				}


				tilesVector.GetElements(i, j)->SetSelectionProcess(SmallTile::SelectionProcess::VOID);

				CorrectTheNeighboringOnes(i, j);
			}
		}
	}
}

void MapTile::CorrectTheNeighboringOnes(int i, int j)
{
	for (int di = -1; di <= 1; ++di)
	{
		for (int dj = -1; dj <= 1; ++dj)
		{
			if (i + di >= 0 && i + di < static_cast<int>(this->sizeOfMap) &&
				j + dj >= 0 && j + dj < static_cast<int>(this->sizeOfMap))
				UpdateTile(i + di, j + dj);
		}
	}
}

std::unique_ptr<SmallTile> MapTile::CreateTile(SmallTile::TileSpecialise tileSpecialise)
{
	if (tilesMap.size() < (int)tileSpecialise)
	{
		return	tilesMap[static_cast<int>(SmallTile::TileSpecialise::VOID)]->clone();
	}

	return tilesMap[static_cast<int>(tileSpecialise)]->clone();
}

void MapTile::RotateMap()
{
	std::reverse(tilesVector.GetVector().begin(), tilesVector.GetVector().end());
}

void MapTile::MoveUpMap()
{
	std::rotate(tilesVector.GetVector().begin(), tilesVector.GetVector().begin() + 1, tilesVector.GetVector().end());
}

void MapTile::MoveDownMap()
{
	std::rotate(tilesVector.GetVector().rbegin(), tilesVector.GetVector().rbegin() + 1, tilesVector.GetVector().rend());
}

void MapTile::InitializeShaders()
{
	if (!this->core_shader.loadFromFile("vertex_shader.vert", "fragment_shader.frag"))
	{
		std::cout << "ERROR could not load shader" << std::endl;
	}
}

#pragma endregion

#pragma region Setters

void MapTile::SetCameraPosition(sf::Vector2f cameraPosition)
{
	this->camera_position = this->ptrGame->camera.getCenter();
}

void MapTile::SetDravingDistance(int dravingDistance)
{
	this->dravingDistance = dravingDistance;
}

void MapTile::SetTimeFromGameplay(int timeSpeed)
{
	this->timeSpeed = timeSpeed;
}

#pragma endregion

#pragma region Getters

std::vector<char> MapTile::GetSelectedTiles() const
{
	return this->selectedTiles;
}

int MapTile::GetSizeOfMap() const
{
	return this->sizeOfMap;
}

unsigned int MapTile::GetNrSelectedTiles() const
{
	return this->nrSelected;
}

VectorManager<std::unique_ptr<SmallTile>>&  MapTile::GetSmallTile()
{
	return this->tilesVector;
}

PathFinding *MapTile::GetPathVoltagePylons()
{
	return this->pathVoltagePylons;
}

PathFinding *MapTile::GetPathRoads()
{
	return this->pathRoad;
}

#pragma endregion