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
	this->LoadMap(filename);
}

#pragma endregion

#pragma region Class_Methods

void MapTile::InitialiseMapEnvironment()
{
	this->InitializeShaders();

	this->ptrGame->textureManager.LoadAsset("selection", "Resources/Textures/selection.png");
	this->ptrGame->textureManager.LoadAsset("selection2", "Resources/Textures/selection2.png");
	this->cursorSmall.setTexture(this->ptrGame->textureManager.GetAsset("selection"));
	this->cursorBig.setTexture(this->ptrGame->textureManager.GetAsset("selection2"));
	this->cursorSmall.setOrigin(0, TILE_SIZE*(2));
	this->cursorBig.setOrigin(0, TILE_SIZE*(2));
}

void MapTile::CreateNewMap(const std::string & filename, unsigned int sizeOfMap, uint64_t seedMap)
{
	std::cout << "Create new map" << std::endl;

	this->sizeOfMap = sizeOfMap;

	this->pathRoad = new PathFinding(this->sizeOfMap);
	this->pathVoltagePylons = new PathFinding(this->sizeOfMap);

	tilesVector.ReshapeVector(sizeOfMap, sizeOfMap);

	SeedGenerator seed = SeedGenerator(seedMap);
	mapGenerator = new MapGenerator(seed);
	mapGenerator->GenerateMapBaseOnSeed(sizeOfMap);

	for (int i = 0; i < this->sizeOfMap; i++)
	{
		for (int j = 0; j < this->sizeOfMap; j++)
		{
			if (mapGenerator->GetBasicTileMap()[i*this->sizeOfMap + j] == TileSpecialise::FLOOR)
			{
				this->tilesVector.AddElements(i, j, CreateTile(TileSpecialise::FLOOR));
			}
			else if (mapGenerator->GetBasicTileMap()[i*this->sizeOfMap + j] == TileSpecialise::WATER)
			{
				this->tilesVector.AddElements(i, j, CreateTile(TileSpecialise::WATER));
			}
			else if (mapGenerator->GetBasicTileMap()[i*this->sizeOfMap + j] == TileSpecialise::TREE)
			{
				this->tilesVector.AddElements(i, j, CreateTile(TileSpecialise::TREE));
			}
			else if (mapGenerator->GetBasicTileMap()[i*this->sizeOfMap + j] == TileSpecialise::ROCK)
			{
				this->tilesVector.AddElements(i, j, CreateTile(TileSpecialise::ROCK));
			}
			else
			{
				this->tilesVector.AddElements(i, j, CreateTile(TileSpecialise::VOID));
			}
			this->tilesVector.GetElements(i, j)->SetPosition(i, j);
		}
	}

	this->InitialiseMapEnvironment();
}

void MapTile::LoadMap(const std::string & fileName)
{
	std::cout << "Load Map " << std::endl;

	std::ifstream readFile("Resources/Maps/" + this->cityName + ".bin", std::ios::in | std::ios::binary);

	if (readFile.good())
	{
		readFile.read((char*)&this->sizeOfMap, sizeof(unsigned int));

		this->pathRoad = new PathFinding(this->sizeOfMap);
		this->pathVoltagePylons = new PathFinding(this->sizeOfMap);

		tilesVector.ReshapeVector(this->sizeOfMap, this->sizeOfMap);

		for (int i = 0; i < this->sizeOfMap; i++)
		{
			for (int j = 0; j < this->sizeOfMap; j++)
			{
				TileData tileData_tmp;

				readFile.read((char*)&tileData_tmp.tileSpecialise, sizeof(TileData::tileSpecialise));
				this->tilesVector.AddElements(i, j, CreateTile(tileData_tmp.tileSpecialise));

				this->tilesVector.GetElements(i, j)->SetPosition(i, j);

				readFile.read((char*)&tileData_tmp.population, sizeof(TileData::population));
				readFile.read((char*)&tileData_tmp.level, sizeof(TileData::level));
				readFile.read((char*)&tileData_tmp.height, sizeof(TileData::height));

				size_t len = 0;

				readFile.read((char*)&len, sizeof(size_t));
				char* temp = new char[len + 1];
				readFile.read(temp, len);
				temp[len] = '\0';
				tileData_tmp.texture_name = temp;
				delete[]temp;

				readFile.read((char*)&tileData_tmp.buildingID, sizeof(TileData::buildingID));

				this->tilesVector.GetElements(i, j).get()->SetTileData(tileData_tmp);
				this->tilesVector.GetElements(i, j).get()->UpdateInformation();

			}
		}
		readFile.close();
	}

	this->InitialiseMapEnvironment();
}

void MapTile::SaveMap()
{
	std::ofstream saveFile("Resources/Maps/" + this->cityName + ".bin", std::ios::out | std::ios::binary);

	if (saveFile.good())
	{
		saveFile.write((char*)&this->sizeOfMap, sizeof(unsigned int));

		for (auto & it : tilesVector.GetVector())
		{
			TileSpecialise tmpTileSpecialise = it.get()->GetTileData().tileSpecialise;
			int tmpPopulation = it.get()->GetTileData().population;
			int tmpLevel = it.get()->GetTileData().level;
			std::string tmpTexture_name = it.get()->GetTileData().texture_name;
			ID tmpBuildingID = it.get()->GetTileData().buildingID;
			int tmpHeight = it.get()->GetTileData().height;

			size_t len = tmpTexture_name.size();

			saveFile.write((char*)&tmpTileSpecialise, sizeof(TileData::tileSpecialise));
			saveFile.write((char*)&tmpPopulation, sizeof(TileData::population));
			saveFile.write((char*)&tmpLevel, sizeof(TileData::level));
			saveFile.write((char*)&tmpHeight, sizeof(TileData::height));

			saveFile.write((char*)&len, sizeof(size_t));
			saveFile.write(tmpTexture_name.c_str(), tmpTexture_name.length());

			saveFile.write((char*)&tmpBuildingID, sizeof(ID));
		}
		saveFile.close();

		this->RememberAnotherFile();
	}
}

void MapTile::RememberAnotherFile()
{
	bool alreadyExisting = false;

	const char* search_term = this->cityName.c_str();
	size_t search_term_size = strlen(search_term);

	std::ifstream searchSave("Resources/Maps/Saves.bin", std::ios::binary);

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
				std::cout << found_at << std::endl;
				alreadyExisting = true;
			}

		}

		searchSave.close();
	}

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
					if (it->hasVehicle == true)
					{
						//if (it->GetVehicleVisible() == VehicleVisible::VISIBLE)
						//{
						if (this->tilesVector.GetElements(i, j).get()->GetSprite().getGlobalBounds().contains(it->GetVehicle()->GetVehicleSprite().getPosition()))
						{
							it->GetVehicle()->DrawVehicle(window);
							it->GetVehicle()->ChangeVehicleSpeed(this->timeSpeed);
						}
						//}
					}
				}
			}

			for (auto & tornado : tornados)
			{
				if (tornado->GetTornadoGlobalBounds().contains(this->tilesVector.GetElements(i, j).get()->GetFixedPosition()))
				{
					tornado->Draw(*window, elapsedTime);
				}
			}

			if (!prevCurFromTwo)
			{
				if (this->tilesVector.GetElements(i, j)->GetSprite().getGlobalBounds().contains(sf::Vector2f(this->ptrGame->window->mapPixelToCoords(sf::Mouse::getPosition(*this->ptrGame->window), this->ptrGame->camera))))
				{
					sf::Vector2f position = this->tilesVector.GetElements(i, j).get()->GetSpritePosition();
					if (this->tilesVector.GetElements(i, j)->GetTileSpecialise() == TileSpecialise::POWER_HOUSE)
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



	//test tornados

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
				neighbourhood[dj + 1][di + 1] = this->tilesMap[static_cast<int>(TypeOfTile::VOID)].get();
			}
		}
	}

	this->tilesVector.GetElements(i, j)->SetNewTileVariant(neighbourhood);
}

void MapTile::SelectTiles(sf::Vector2i from, sf::Vector2i to, TypeOfTile typeOfTile)
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

			if (smallTile->GetTypeOfTile() != TypeOfTile::WATER)
			{
				smallTile->SetSelectionProcess(SelectionProcess::SELECTED);
				this->nrSelected++;
			}
			else
			{
				smallTile->SetSelectionProcess(SelectionProcess::ERROR);
			}
		}
	}
}

void MapTile::DeleteSelection()
{
	for (std::unique_ptr<SmallTile>& tile : this->tilesVector.GetVector())
	{
		tile->SetSelectionProcess(SelectionProcess::VOID);
	}
	this->nrSelected = 0;
}


void MapTile::ChangeSpecialTile(TileSpecialise tileSpecialise, IDvector<Structure*>& structuresWithID, std::vector<std::size_t> & structuresToRemove,
	std::vector<HighVoltageLines*> & highVoltageLinesVector, std::vector<PowerHouse*> & powerHouseVector,
	IDvector<RequireConnecting*> & IDconnectings)
{
	for (int i = 0; i < this->sizeOfMap; i++)
	{
		for (int j = 0; j < this->sizeOfMap; j++)
		{
			if (tileSpecialise == TileSpecialise::POWER_HOUSE)
			{
				if (tilesVector.GetElements(i, j)->GetSelectionProcess() == SelectionProcess::SELECTED &&
					tilesVector.GetElements(i + 1, j)->GetSelectionProcess() == SelectionProcess::SELECTED &&
					tilesVector.GetElements(i, j + 1)->GetSelectionProcess() == SelectionProcess::SELECTED &&
					tilesVector.GetElements(i + 1, j + 1)->GetSelectionProcess() == SelectionProcess::SELECTED)
				{
					if (tilesVector.GetElements(i, j)->GetTypeOfTile() == TypeOfTile::DIRT &&
						tilesVector.GetElements(i + 1, j)->GetTypeOfTile() == TypeOfTile::DIRT &&
						tilesVector.GetElements(i, j + 1)->GetTypeOfTile() == TypeOfTile::DIRT &&
						tilesVector.GetElements(i + 1, j + 1)->GetTypeOfTile() == TypeOfTile::DIRT)
					{
						this->tilesVector.AddElements(i + 1, j, CreateTile(tileSpecialise));
						this->tilesVector.AddElements(i, j, CreateTile(TileSpecialise::SPECTRUM_PLATE));
						this->tilesVector.AddElements(i + 1, j + 1, CreateTile(TileSpecialise::SPECTRUM_PLATE));
						this->tilesVector.AddElements(i, j + 1, CreateTile(TileSpecialise::SPECTRUM_PLATE));


						Structure *structure = static_cast<Structure*>(tilesVector.GetElements(i + 1, j).get());
						ID _id = structuresWithID.push(structure);
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

						//structure->SetHoldGameplay(holdGameplay);

						sf::Vector2f position;

						position.x = (j - i) * TILE_SIZE + this->sizeOfMap * TILE_SIZE;
						position.y = (j + i) * TILE_SIZE * 0.5f;

						this->tilesVector.GetElements(i, j)->SetSpritePosition(position);

						/*
						if (structure->GetIsPowerHouse())
						{
							this->pathVoltagePylons->AddConnection(i+1, j);
						}
						*/
					}

				}

			}
		}
	}
}

void MapTile::ChangeTile(TileSpecialise tileSpecialise, IDvector<Structure*> & structuresWithID, std::vector<ID> & structuresToRemove,
	std::vector<House*> & houseVector, std::vector<Shop*> & shopVector, std::vector<Factory*> & factoryVector,
	std::vector<Hospital*> & hospitalVector, std::vector<PowerHouse*> & powerHouseVector, std::vector<PoliceStation*> & policeStationVector,
	std::vector<FireBrigade*> & fireBrigadeVector, std::vector<HighVoltageLines*> & highVoltageLinesVector,
	IDvector<RequireConnecting*> & IDconnectings, std::vector<ID> & connectionsToRemove)
{
	for (int i = 0; i < this->sizeOfMap; i++)
	{
		for (int j = 0; j < this->sizeOfMap; j++)
		{
			if (tilesVector.GetElements(i, j)->GetSelectionProcess() == SelectionProcess::SELECTED)
			{
				if (tileSpecialise != TileSpecialise::RUINS)
				{
					if ((tileSpecialise != TileSpecialise::FLOOR) && (tilesVector.GetElements(i, j)->GetIsRoad() || tilesVector.GetElements(i, j)->GetIsVoltagePylon()
						|| tilesVector.GetElements(i, j)->GetIsBuilding()) || tilesVector.GetElements(i, j).get()->GetTileSpecialise() == TileSpecialise::SPECTRUM_PLATE)
					{
						continue;
					}
				}

				if (tilesVector.GetElements(i, j)->GetIsRoad())
				{
					this->pathRoad->RemoveConnection(i, j);

					/*
					for (auto & it : structuresWithID.getObjects())
					{
						if (it->hasVehicle == true)
						{
							it->rememberRoute = false;
							it->GetPatchRoad()->ForgetPaths();
							it->returnPath.clear();
							it->drivingPath.clear();
						}
					}
					*/
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

										this->tilesVector.AddElements(i - 1, j, CreateTile(TileSpecialise::FLOOR));
										this->tilesVector.AddElements(i, j + 1, CreateTile(TileSpecialise::FLOOR));
										this->tilesVector.AddElements(i - 1, j + 1, CreateTile(TileSpecialise::FLOOR));

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
					ID _id = structuresWithID.push(structure);
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
					/*
					for (auto & it : structuresWithID.getObjects())
					{
						if (it->hasVehicle == true)
						{
							it->rememberRoute = false;
							it->GetPatchRoad()->ForgetPaths();
							it->returnPath.clear();
							it->drivingPath.clear();
						}

					}
					*/
				}
				else if (tilesVector.GetElements(i, j)->GetIsVoltagePylon())
				{
					this->pathVoltagePylons->AddConnection(i, j);

					HighVoltageLines *highVoltageLine = static_cast<HighVoltageLines*>(tilesVector.GetElements(i, j).get());


					for (auto & powerHouse : powerHouseVector)
					{
						highVoltageLine->AddPowerStationCoordinates(powerHouse->GetPosition());
					}

					ID _id = IDconnectings.push(highVoltageLine);
					highVoltageLine->SetHighVoltageLinesID(_id);
					highVoltageLine->SetPylonCoordinates(sf::Vector2i(i, j));
					highVoltageLine->SetPathPylon(this->pathVoltagePylons);
					highVoltageLinesVector.push_back(highVoltageLine);
				}


				tilesVector.GetElements(i, j)->SetSelectionProcess(SelectionProcess::VOID);

				CorrectTheNeighboringOnes(i, j);
			}
		}
	}
};

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

std::unique_ptr<SmallTile> MapTile::CreateTile(TileSpecialise tileSpecialise)
{
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