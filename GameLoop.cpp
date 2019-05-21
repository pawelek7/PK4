#include "GameLoop.h"

#pragma region Constructors

GameLoop::GameLoop(std::shared_ptr<AssetsOfGame> ptrGame, const std::string & mapName, uint64_t seedMap, int sizeMap, bool loadGame)
	:ptrGame(ptrGame)
{
	this->tileSpecialise = TileSpecialise::FLOOR;

	this->holdGameplay = new HoldGameplay(ptrGame, mapName, seedMap, sizeMap, loadGame);

	this->sizeMap = this->holdGameplay->GetMaptile()->GetSizeOfMap();
	this->SetCameraPosition();
}

#pragma endregion

#pragma region Class_Methods

void GameLoop::SetCameraPosition()
{
	sf::Vector2f pos = sf::Vector2f(this->ptrGame->window->getSize());
	this->ptrGame->camera.setSize(pos);
	this->ptrGame->HUDcamera.setSize(pos);

	pos *= 0.5f;

	this->ptrGame->camera.setCenter(pos);
	this->ptrGame->HUDcamera.setCenter(pos);

	this->centre = sf::Vector2f(sizeMap, sizeMap * 0.5);
	this->centre *= float(TILE_SIZE);
	this->ptrGame->camera.setCenter(centre);
	this->ptrGame->HUDcamera.setCenter(
		centre.x + this->ptrGame->window->getSize().x / 2, centre.y + this->ptrGame->window->getSize().y / 2);
}

void GameLoop::UpdateObject(float elapsedTime)
{
	this->holdGameplay->Update(elapsedTime);

	this->UpdateHud(elapsedTime);
	this->UpdateGameplay(elapsedTime);
}

void GameLoop::UpdateHud(float elapsedTime)
{
	this->hudUp->UpdateHUD((sf::Vector2i)this->ptrGame->mousePositionMap, elapsedTime);

	this->hudUp->UpdateDate(holdGameplay->GetDate());
	this->hudUp->UpdateMoneyAmount(this->holdGameplay->GetCityMoney());
	this->hudUp->SetPopulationText(this->holdGameplay->GetPopulation());

	this->hudLeft->UpdateHUDleft((sf::Vector2i)this->ptrGame->mousePositionMap, elapsedTime);

	this->tableInfSystem.at("ButtonInfo").SetTableText(0, this->hudLeft->GetButtonOption1());
	this->tableInfSystem.at("ButtonInfo").SetTableText(1, this->hudLeft->GetButtonOption2());
}

void GameLoop::UpdateGameplay(float elapsedTime)
{
	this->holdGameplay->GetMaptile()->SetCameraPosition(this->ptrGame->window->mapPixelToCoords(sf::Mouse::getPosition(*this->ptrGame->window), this->ptrGame->HUDcamera));

	if (this->hudUp->GetIsReadySelectedOption())
	{
		this->UpdateHudUpOptions();
	}

	if (this->holdGameplay->GetTaxesInformation()->GetIsTableOpnen() == true)
	{
		this->holdGameplay->GetTaxesInformation()->UpdateTable(elapsedTime);
	}

	if (this->holdGameplay->GetStatistics()->GetIsTableOpnen() == true)
	{
		this->holdGameplay->GetStatistics()->UpdateTable(elapsedTime);
	}

	if (this->holdGameplay->GetNewspaper()->GetIsTableOpnen() == true)
	{
		this->holdGameplay->GetNewspaper()->UpdateTable(elapsedTime);
	}
}

void GameLoop::UpdateHudUpOptions()
{
	std::string option = this->hudUp->GetClickedOption();

	if (option == "Slow")
	{
		this->holdGameplay->SetTimeSpeed(TimeSpeed::SLOW);
		std::cout << "Slow" << std::endl;
	}
	else if (option == "Normal")
	{
		this->holdGameplay->SetTimeSpeed(TimeSpeed::NORMAL);
		std::cout << "Normal" << std::endl;
	}
	else if (option == "Fast")
	{
		this->holdGameplay->SetTimeSpeed(TimeSpeed::FAST);
		std::cout << "Fast" << std::endl;
	}
	else if (option == "Uber")
	{
		this->holdGameplay->SetTimeSpeed(TimeSpeed::UBER);
		std::cout << "Uber" << std::endl;
	}
	else if (option == "Save")
	{
		this->holdGameplay->GetMaptile()->SaveMap();
		std::cout << "Saved" << std::endl;
	}
	else if (option == "Load")
	{
		this->ptrGame->stateMachine.NewState(std::unique_ptr<StateOfProgram>(new LoadGame(this->ptrGame)), "LoadGame");
	}
	else if (option == "Menu")
	{
		this->ptrGame->stateMachine.PopState();
		return;
	}
	else if (option == "Exit")
	{
		this->ptrGame->window->close();
		this->ptrGame->stateMachine.PopState();
	}
	else if (option == "Short")
	{
		this->holdGameplay->GetMaptile()->SetDravingDistance(10);
	}
	else if (option == "Medium")
	{
		this->holdGameplay->GetMaptile()->SetDravingDistance(20);
	}
	else if (option == "Long")
	{
		this->holdGameplay->GetMaptile()->SetDravingDistance(30);
	}
	else if (option == "Pause")
	{
		this->ptrGame->stateMachine.NewState(std::unique_ptr<StateOfProgram>(new Options(this->ptrGame)), "Options", true);
	}
	else if (option == "Cyclone")
	{
		this->holdGameplay->ForceCycloneEvent();
	}
	else if (option == "Epidemic")
	{
		this->holdGameplay->ForceEpidemicEvent();
	}
	else if (option == "Fire")
	{
		this->holdGameplay->ForceFireEvent();
	}
	else if (option == "Newest")
	{
		this->holdGameplay->GetNewspaper()->SetIsTableOpen(true);
	}
	else if (option == "Info")
	{
		this->holdGameplay->GetStatistics()->SetIsTableOpen(true);
	}
}

void GameLoop::DrawObject(float elapsedTime)
{
	this->DrawBackground();
	this->DrawMap(elapsedTime);
	this->DrawHud(elapsedTime);
}

void GameLoop::DrawBackground()
{
	this->ptrGame->window->setView(this->ptrGame->HUDcamera);
	this->ptrGame->window->draw(background);
}

void GameLoop::DrawHud(float elapsedTime)
{
	this->ptrGame->window->setView(this->ptrGame->HUDcamera);

	if (this->holdGameplay->GetTaxesInformation()->GetIsTableOpnen() == true)
	{
		this->holdGameplay->GetTaxesInformation()->DrawTable();
	}

	if (this->holdGameplay->GetStatistics()->GetIsTableOpnen() == true)
	{
		this->holdGameplay->GetStatistics()->DrawTable();
	}

	if (this->holdGameplay->GetNewspaper()->GetIsTableOpnen() == true)
	{
		this->holdGameplay->GetNewspaper()->DrawTable();
	}

	this->hudLeft->DrawHUDleft(this->ptrGame->window);
	this->hudUp->DrawHUD(this->ptrGame->window);

	for (auto & it : this->tableInfSystem)
	{
		this->ptrGame->window->draw(it.second);
	}
}

void GameLoop::DrawMap(float elapsedTime)
{
	this->ptrGame->window->setView(this->ptrGame->camera);

	this->holdGameplay->Draw(this->ptrGame->window, elapsedTime);
}

void GameLoop::InitializeObject()
{
	this->loadData = new LoadData(ptrGame);

	this->ptrGame->textureManager.LoadAsset("HUD", "Resources/Textures/HUD.png");
	this->ptrGame->textureManager.LoadAsset("HUD_2", "Resources/Textures/HUD_2.png");
	this->ptrGame->textureManager.LoadAsset("gs_background", "Resources/Textures/gs_background.png");

	this->background.setSize(sf::Vector2f(static_cast<float>(this->ptrGame->window->getSize().x),
		static_cast<float>(this->ptrGame->window->getSize().y)));
	this->background.setTexture(&this->ptrGame->textureManager.GetAsset("gs_background"));
	this->background.setPosition(centre.x, centre.y);

	this->font.loadFromFile("Resources/Fonts/Kids Zone.ttf"); //temporary solution!!!

	this->hudUp = new HudUp(this->ptrGame->textureManager.GetAsset("HUD"),
		this->ptrGame->textureManager.GetAsset("HUD_2"),
		this->ptrGame->window->getSize().x, this->ptrGame->window->getSize().y,
		centre.x, centre.y,
		150.0f, 50.0f, this->font, this->ptrGame, this->ptrGame->videoMode);

	this->hudLeft = new HudLeft(centre.x, centre.y,
		64, 64, this->ptrGame->window->getSize().x, this->ptrGame->window->getSize().y, this->ptrGame);

	this->tableInfSystem.emplace("InformationBuilding", TableInformation(
		{
			std::make_pair("Unknown: ", "Unknown"),
			std::make_pair("Unknown: ", "Unknown"),
			std::make_pair("Unknown: ", "Unknown"),
			std::make_pair("Unknown: ", "Unknown"),
			std::make_pair("Unknown: ", "Unknown")
		},
		TableLook(&font, p2pX(25.0f, this->ptrGame->videoMode), calcCharSize(this->ptrGame->videoMode), calcCharSize(this->ptrGame->videoMode), sf::Color(204, 204, 179), sf::Color::Black, sf::Color::Black, sf::Color::Yellow)
	));

	this->tableInfSystem.emplace("ButtonInfo", TableInformation(
		{
			std::make_pair("Unknown: ", "Unknown"),
			std::make_pair("Unknown: ", "Unknown")
		},
		TableLook(&font, p2pX(25.0f, this->ptrGame->videoMode), calcCharSize(this->ptrGame->videoMode), calcCharSize(this->ptrGame->videoMode), sf::Color(204, 204, 179), sf::Color::Black, sf::Color::Black, sf::Color::Yellow)
	));
}

void GameLoop::HoldInput()
{
	sf::Event sfmlEvent;

	while (this->ptrGame->window->pollEvent(sfmlEvent))
	{
		sf::Vector2f guiPos = this->ptrGame->window->mapPixelToCoords(sf::Mouse::getPosition(*this->ptrGame->window), this->ptrGame->HUDcamera);
		int totalCost = this->CalculateCostOfAllTiles();
		this->hudUp->SetDecreaseMoneyText(totalCost);

		switch (sfmlEvent.type)
		{
		case(sf::Event::MouseMoved):
			this->tableInfSystem.at("ButtonInfo").GlowElement(this->tableInfSystem.at("ButtonInfo").GetOption(guiPos));

			if (this->mouseAction == MouseAction::MOVEVIEW)
			{
				sf::Vector2f position = sf::Vector2f(this->ptrGame->mousePositionWindow - this->movingDistance);
				this->ptrGame->camera.move(-1.0f * position * this->zoomAmount);

				movingDistance = this->ptrGame->mousePositionWindow;

			}
			else if (this->mouseAction == MouseAction::SELECTMAP)
			{
				sf::Vector2f pos = this->ptrGame->window->mapPixelToCoords(sf::Mouse::getPosition(*this->ptrGame->window), this->ptrGame->camera); //??

				this->hudUp->isDrawDecreaseMoney(true);

				selectTO.x = pos.y / (TILE_SIZE)+pos.x / (2 * TILE_SIZE) - this->holdGameplay->GetMaptile()->GetSizeOfMap() * 0.5 - 0.5;
				selectTO.y = pos.y / (TILE_SIZE)-pos.x / (2 * TILE_SIZE) + this->holdGameplay->GetMaptile()->GetSizeOfMap()  * 0.5 + 0.5;

				this->holdGameplay->GetMaptile()->DeleteSelection();
				this->holdGameplay->GetMaptile()->SelectTiles(selectFROM, selectTO, TypeOfTile::DIRT);

			}
			break;
		case(sf::Event::MouseButtonPressed):
			if (sfmlEvent.mouseButton.button == sf::Mouse::Middle)
			{
				if (this->mouseAction != MouseAction::MOVEVIEW)
				{
					this->mouseAction = MouseAction::MOVEVIEW;
					this->movingDistance = this->ptrGame->mousePositionWindow;
				}

				this->tableInfSystem.at("InformationBuilding").Hidetable();
			}
			else if (sfmlEvent.mouseButton.button == sf::Mouse::Left)
			{
				if (this->tableInfSystem.at("ButtonInfo").GetIsActivated())
				{
					std::string buildingOption = this->tableInfSystem.at("ButtonInfo").ActivatedElement(guiPos);
					this->GetBuildingOption(buildingOption);

					this->tableInfSystem.at("ButtonInfo").Hidetable();
					std::cout << buildingOption << std::endl;
				}

				if (this->tableInfSystem.at("ButtonInfo").GetIsActivated())
				{
					this->mouseAction = MouseAction::TABLE_ACTIVATED;
				}
				else
				{
					if (this->hudLeft->GetMouseOnHud())
					{
						this->mouseAction = MouseAction::GUI_SELECTING;
					}
					else if (this->hudUp->GetCursorOnHudUp())
					{
						//this->mouseAction = MouseAction::GUI_SELECTING;
					}
					else
					{
						this->mouseAction = MouseAction::VOID;
					}
				}

				if (this->mouseAction == MouseAction::GUI_SELECTING)
				{
					this->tableInfSystem.at("ButtonInfo").setPosition(guiPos);
					this->tableInfSystem.at("ButtonInfo").ShowTable();
				}
				else
				{
					if (this->mouseAction != MouseAction::SELECTMAP)
					{
						this->mouseAction = MouseAction::SELECTMAP;
						sf::Vector2f pos = this->ptrGame->window->mapPixelToCoords(sf::Mouse::getPosition(*this->ptrGame->window), this->ptrGame->camera);
						this->hudUp->isDrawDecreaseMoney(true);

						selectFROM.x = pos.y / (TILE_SIZE)+pos.x / (2 * TILE_SIZE) - this->holdGameplay->GetMaptile()->GetSizeOfMap() * 0.5 - 0.5;
						selectFROM.y = pos.y / (TILE_SIZE)-pos.x / (2 * TILE_SIZE) + this->holdGameplay->GetMaptile()->GetSizeOfMap() * 0.5 + 0.5;
					}
				}

				this->tableInfSystem.at("InformationBuilding").Hidetable();
			}
			else if (sfmlEvent.mouseButton.button == sf::Mouse::Right)
			{
				HoldGameplay::InteractBuilding interaction = holdGameplay->Interaction(this->ptrGame->window->mapPixelToCoords(sf::Mouse::getPosition(*this->ptrGame->window), this->ptrGame->camera));
				if (interaction.interOption == HoldGameplay::InteractBuilding::InterOption::STRUCTURE)
				{
					if (interaction.structure->GetIsBuilding())
					{
						sf::Vector2f pos = guiPos;

						House *house = dynamic_cast<House*>(interaction.structure);

						if (house != nullptr)
						{
							this->tableInfSystem.at("InformationBuilding").setPosition(pos);
							this->tableInfSystem.at("InformationBuilding").ShowTable();
							this->tableInfSystem.at("InformationBuilding").SetTableText(0, "Population:" + std::to_string(house->GetHousehold()));
							this->tableInfSystem.at("InformationBuilding").SetTableText(1, "ID:" + std::to_string(house->GetID()));
							this->tableInfSystem.at("InformationBuilding").SetTableText(2, "Sick: " + std::to_string(house->GetSickPeopleNr()));
							if (house->GetHasEnergy())
							{
								this->tableInfSystem.at("InformationBuilding").SetTableText(3, "Energy: Yes");
							}
							else
							{
								this->tableInfSystem.at("InformationBuilding").SetTableText(3, "Energy: No");
							}
							this->tableInfSystem.at("InformationBuilding").SetTableText(4, "Happiness: " + std::to_string(house->GetHappiness()) + "%");
						}
						else
						{
							Shop *shop = dynamic_cast<Shop*>(interaction.structure);

							if (shop != nullptr)
							{
								this->tableInfSystem.at("InformationBuilding").setPosition(pos);
								this->tableInfSystem.at("InformationBuilding").ShowTable();
								this->tableInfSystem.at("InformationBuilding").SetTableText(0, "Employees: " + std::to_string(shop->GetEmployessNr()));
								this->tableInfSystem.at("InformationBuilding").SetTableText(1, "ID: " + std::to_string(shop->GetID()));
								this->tableInfSystem.at("InformationBuilding").SetTableText(2, "Today customers: " + std::to_string(shop->GetActualAmountOfCustomets()));
								this->tableInfSystem.at("InformationBuilding").SetTableText(3, "Goods amount: " + std::to_string(shop->GetGoodsAmount()));
								if (shop->GetHasEnergy())
								{
									this->tableInfSystem.at("InformationBuilding").SetTableText(4, "Energy: Yes");
								}
								else
								{
									this->tableInfSystem.at("InformationBuilding").SetTableText(4, "Energy: No");
								}
							}
							else
							{
								Factory *factory = dynamic_cast<Factory*>(interaction.structure);

								if (factory != nullptr)
								{
									this->tableInfSystem.at("InformationBuilding").setPosition(pos);
									this->tableInfSystem.at("InformationBuilding").ShowTable();
									this->tableInfSystem.at("InformationBuilding").SetTableText(0, "Employees: " + std::to_string(factory->GetWorkersAmount()));
									this->tableInfSystem.at("InformationBuilding").SetTableText(1, "ID: " + std::to_string(factory->GetID()));
									this->tableInfSystem.at("InformationBuilding").SetTableText(2, "Delivery car: " + factory->GetInformationAboutVehicle());
									this->tableInfSystem.at("InformationBuilding").SetTableText(3, "Goods:" + std::to_string(factory->GetGoodsAmounst()));
									if (factory->GetHasEnergy())
									{
										this->tableInfSystem.at("InformationBuilding").SetTableText(4, "Energy: Yes");
									}
									else
									{
										this->tableInfSystem.at("InformationBuilding").SetTableText(4, "Energy: No");
									}
								}
								else
								{
									PowerHouse *powerHouse = dynamic_cast<PowerHouse*>(interaction.structure);

									if (powerHouse != nullptr)
									{
										this->tableInfSystem.at("InformationBuilding").setPosition(pos);
										this->tableInfSystem.at("InformationBuilding").ShowTable();
										this->tableInfSystem.at("InformationBuilding").SetTableText(0, "Employees: " + std::to_string(powerHouse->GetEmployessAmount()));
										this->tableInfSystem.at("InformationBuilding").SetTableText(1, "ID: " + std::to_string(powerHouse->GetID()));
										this->tableInfSystem.at("InformationBuilding").SetTableText(2, "Power: " + std::to_string(powerHouse->GetProducedEnergy()) + "%");
										this->tableInfSystem.at("InformationBuilding").SetTableText(3, "Unknown");
									}
								}
							}

						}
					}
				}

				this->tableInfSystem.at("ButtonInfo").Hidetable();

				if (this->mouseAction == MouseAction::SELECTMAP)
				{
					this->mouseAction = MouseAction::VOID;

					this->holdGameplay->GetMaptile()->DeleteSelection();
					this->hudUp->isDrawDecreaseMoney(false);
				}
			}
			break;
		case (sf::Event::MouseButtonReleased):
			if (sfmlEvent.mouseButton.button == sf::Mouse::Middle)
			{
				this->mouseAction = MouseAction::VOID;
			}
			else if (sfmlEvent.mouseButton.button == sf::Mouse::Left)
			{
				if (this->mouseAction != MouseAction::GUI_SELECTING)
				{
					if (this->mouseAction == MouseAction::SELECTMAP)
					{
						this->hudUp->isDrawDecreaseMoney(false);

						if (this->holdGameplay->GetCityMoney() >= totalCost)
						{
							this->holdGameplay->DecreaseCityFunds(totalCost);
							this->holdGameplay->ChangeTileG(tileSpecialise, special_building);
						}

						this->holdGameplay->GetMaptile()->DeleteSelection();
						this->mouseAction = MouseAction::VOID;
					}
				}
			}
			break;
		case(sf::Event::MouseWheelScrolled):
			this->ptrGame->window->setView(this->ptrGame->camera);
			if (sfmlEvent.mouseWheelScroll.delta > 0)
				zoomViewAt({ sfmlEvent.mouseWheelScroll.x,  sfmlEvent.mouseWheelScroll.y }, (*this->ptrGame->window), (1.f / zoomAmount));
			else if (sfmlEvent.mouseWheelScroll.delta < 0)
				zoomViewAt({ sfmlEvent.mouseWheelScroll.x,  sfmlEvent.mouseWheelScroll.y }, (*this->ptrGame->window), zoomAmount);
			break;
		case (sf::Event::Closed):
			this->ptrGame->window->close();
			break;
		}
	}
}

void GameLoop::zoomViewAt(sf::Vector2i pixel, sf::RenderWindow& window, float zoom)
{
	if (zoom > 1)
	{
		if (zoomSize > 3)
		{
			return;
		}
		zoomSize++;
	}
	else
	{
		if (zoomSize < -3)
		{
			return;
		}
		zoomSize--;
	}

	const sf::Vector2f beforeCoord{ window.mapPixelToCoords(pixel) };
	this->ptrGame->camera.zoom(zoom);
	window.setView(this->ptrGame->camera);
	const sf::Vector2f afterCoord{ window.mapPixelToCoords(pixel) };
	const sf::Vector2f offsetCoords{ beforeCoord - afterCoord };
	this->ptrGame->camera.move(offsetCoords);
	window.setView(this->ptrGame->camera);
}

void GameLoop::GetBuildingOption(const std::string & buildingOption)
{
	if (buildingOption == "Build Houses")
	{
		this->IsTileUpdate("HOUSE");
		this->special_building = false;
	}
	else if (buildingOption == "Destroy terrain")
	{
		this->IsTileUpdate("FLOOR");
		this->special_building = false;
	}
	else if (buildingOption == "Build Shops")
	{
		this->IsTileUpdate("SHOP");
		this->special_building = false;
	}
	else if (buildingOption == "Build Factory")
	{
		this->IsTileUpdate("FACTORY");
		this->special_building = false;
	}
	else if (buildingOption == "Build roads")
	{
		this->IsTileUpdate("ROAD");
		this->special_building = false;
	}
	else if (buildingOption == "Build Power Lines")
	{
		this->IsTileUpdate("HIGH_VOLTAGE_LINES");
		this->special_building = false;
	}
	else if (buildingOption == "Build PowerStation")
	{
		this->IsTileUpdate("POWER_HOUSE");
		this->special_building = true;
	}
	else if (buildingOption == "Build Hospital")
	{
		this->IsTileUpdate("HOSPITAL");
		this->special_building = false;
	}
	else if (buildingOption == "Change Taxes")
	{
		this->holdGameplay->GetTaxesInformation()->SetIsTableOpen(true);
	}
	else if (buildingOption == "Build FireStation")
	{
		this->IsTileUpdate("FIRE_STATION");
		this->special_building = false;
	}
}

bool GameLoop::IsTileUpdate(const std::string & tileName)
{
	tileSpecialise = SmallTile::SetStringToTileSpecialise(
		tileName.substr(0, tileName.size()));

	return true;
}

unsigned long int GameLoop::GetTileCost(TileSpecialise tileSpecialise) const
{
	switch (tileSpecialise)
	{
	case TileSpecialise::FACTORY:
		return 1000;
	case TileSpecialise::FLOOR:
		return 50;
	case TileSpecialise::HOUSE:
		return 500;
	case TileSpecialise::ROAD:
		return 150;
	case TileSpecialise::SHOP:
		return 1000;
	default:
		return 0;
	}
}

unsigned long int GameLoop::CalculateCostOfAllTiles()
{
	return GetTileCost(this->tileSpecialise) * this->holdGameplay->GetMaptile()->GetNrSelectedTiles();
}

#pragma endregion