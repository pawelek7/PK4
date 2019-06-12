#include "LoadGame.h"

#pragma region Constructors

LoadGame::LoadGame(std::shared_ptr<AssetsOfGame> ptrGame)
	:ptrGame(ptrGame)
{
	this->font.loadFromFile("Resources/Fonts/Delimax.ttf");

	this->tableInfSystem.emplace("InformationBuilding", TableInformation(
		{
		std::make_pair("<Empty>", "1"),
		std::make_pair("<Empty>", "2"),
		std::make_pair("<Empty>", "3"),
		std::make_pair("<Empty>", "4"),
		std::make_pair("<Empty>", "5"),
		std::make_pair("<Empty>", "6"),
		std::make_pair("<Empty>", "7"),
		std::make_pair("<Empty>", "8"),
		std::make_pair("<Empty>", "9"),
		std::make_pair("<Empty>", "10")
		},
		TableLook(&font, p2pX(25.0f, this->ptrGame->videoMode), calcCharSize(this->ptrGame->videoMode), calcCharSize(this->ptrGame->videoMode), sf::Color(102, 153, 153), sf::Color::White, sf::Color::Black, sf::Color(61, 92, 92))
	));

	this->tableInfSystem.at("InformationBuilding").setPosition(sf::Vector2f(p2pX(10.0f, this->ptrGame->videoMode), p2pY(37.5f, this->ptrGame->videoMode)));

	this->tableInfSystem.at("InformationBuilding").ShowTable();
}

LoadGame::~LoadGame()
{
	auto i = mapButtons.begin();
	for (i = mapButtons.begin(); i != mapButtons.end(); i++)
	{
		if (i->second != nullptr)
		{
			delete i->second;
			i->second = nullptr;
		}
	}
}

#pragma endregion

#pragma region Class_Methods

void LoadGame::UpdateObject(float elapsedTime)
{
	this->ptrGame->window->setView(this->ptrGame->window->getDefaultView());

	for (auto & i : this->mapButtons)
	{
		i.second->UpdateButton(this->ptrGame->mousePositionWindow, elapsedTime);
	}
}

void LoadGame::DrawObject(float elapsedTime)
{
	this->ptrGame->window->draw(background);
	this->ptrGame->window->draw(this->displayingText);

	for (auto & i : this->mapButtons)
	{
		i.second->DrawButton(this->ptrGame->window);
	}

	for (auto & it : this->tableInfSystem)
	{
		this->ptrGame->window->draw(it.second);
	}
}

void LoadGame::InitializeObject()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->ptrGame->window->getSize().x),
		static_cast<float>(this->ptrGame->window->getSize().y)));

	this->background.setTexture(&this->ptrGame->textureManager.GetAsset("background"));


	sf::VideoMode vm = this->ptrGame->videoMode;

	this->displayingText.setFont(font);
	this->displayingText.setCharacterSize(calcCharSize(vm));
	this->displayingText.setFillColor(sf::Color::Blue);
	this->displayingText.setPosition(p2pX(67.0f, vm), p2pY(60.0f, vm));

	this->mapButtons["RETURN"] = new TextButton(p2pX(60.0f, vm), p2pY(50.0f, vm),
		p2pX(15.0f, vm), calcCharSize(vm),
		"RETURN", calcCharSize(vm, 50), sf::Color::Magenta, sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), this->ptrGame);

	this->mapButtons["DELETE"] = new TextButton(p2pX(75.0f, vm), p2pY(60.0f, vm),
		p2pX(15.0f, vm), calcCharSize(vm),
		"X", calcCharSize(vm), sf::Color::Red, sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), this->ptrGame);

	this->mapButtons["LOAD"] = new TextButton(p2pX(45.0f, vm), p2pY(60.0f, vm),
		p2pX(15.0f, vm), calcCharSize(vm),
		"V", calcCharSize(vm), sf::Color::Green, sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), this->ptrGame);

	std::string tmp_name = "";
	int iterator = 0;

	std::ifstream readSaves("Resources/Maps/Saves.bin", std::ios::in | std::ios::binary);

	if (readSaves.good())
	{
		while (!readSaves.eof())
		{
			size_t nameLength = 0;
			readSaves.read((char*)&nameLength, sizeof(size_t));
			char* temp = new char[nameLength + 1];
			readSaves.read(temp, nameLength);
			temp[nameLength] = '\0';
			tmp_name = temp;
			delete[]temp;

			this->mapNamesVector.push_back(tmp_name);
			this->tableInfSystem.at("InformationBuilding").SetTableText(iterator, tmp_name);
			iterator++;
		}
		this->tableInfSystem.at("InformationBuilding").SetTableText(--iterator, "<Empty>");
	}
}

void LoadGame::HoldInput()
{
	sf::VideoMode vm = this->ptrGame->videoMode;
	sf::Vector2f guiPos = this->ptrGame->window->mapPixelToCoords(sf::Mouse::getPosition(*this->ptrGame->window));
	this->tableInfSystem.at("InformationBuilding").GlowElement(this->tableInfSystem.at("InformationBuilding").GetOption(guiPos));

	while (this->ptrGame->window->pollEvent(events))
	{
		switch (events.type)
		{
		case sf::Event::MouseButtonPressed:
			if (events.mouseButton.button == sf::Mouse::Left)
			{
				mapName = this->tableInfSystem.at("InformationBuilding").ActivatedElement(guiPos);

				if (mapName == "unknown")
					break;

				this->displayingText.setString(mapName);
				this->displayingText.setPosition(p2pX(67.0f, vm) - (this->displayingText.getGlobalBounds().width / 2.f), p2pY(60.0f, vm));
			}
			break;
		case sf::Event::Closed:
			this->ptrGame->window->close();
			break;
		}

		if (this->mapButtons["RETURN"]->GetPressed())
		{
			ptrGame->stateMachine.PopState();
			return;
		}

		if (this->mapButtons["LOAD"]->GetPressed())
		{
			if (displayingText.getString() != "unknown" && displayingText.getString() != "<Empty>" && displayingText.getString() != "")
			{
				ptrGame->stateMachine.NewState(std::unique_ptr<IStateOfProgram>(new GameLoop(ptrGame,
					displayingText.getString(), 0, 32, true)), "GameLoop", true);
				ptrGame->stateMachine.PopState();
				return;
			}
		}

		if (this->mapButtons["DELETE"]->GetPressed())
		{
			std::vector<std::string>::iterator itr = std::find(mapNamesVector.begin(), mapNamesVector.end(), displayingText.getString());
			if (itr != mapNamesVector.end())
			{
				std::string removeCity = "Resources/Maps/" + *itr + ".bin";
				std::string removeCity_info = "Resources/Maps/" + *itr + "_info.bin";

				this->mapNamesVector.erase(itr);

				int i = 0;

				for (i = 0; i < this->mapNamesVector.size(); i++)
				{
					this->tableInfSystem.at("InformationBuilding").SetTableText(i, mapNamesVector[i]);
				}

				for (i; i < 10; i++)
				{
					this->tableInfSystem.at("InformationBuilding").SetTableText(i, "<Empty>");
				}

				std::remove(removeCity.c_str());
				std::remove(removeCity_info.c_str());
				std::remove("Resources/Maps/Saves.bin");

				std::ofstream multipleSaves("Resources/Maps/Saves.bin", std::ios::out | std::ios::binary);

				if (multipleSaves.good())
				{
					std::vector<std::string>::iterator itr2 = mapNamesVector.begin();
					int i2 = 0;
					while (itr2 != mapNamesVector.end())
					{
						size_t lengthName = mapNamesVector[i2].size();

						multipleSaves.write((char*)&lengthName, sizeof(size_t));
						multipleSaves.write(mapNamesVector[i2].c_str(), mapNamesVector[i2].length());
						itr2++;
						i2++;
					}
					multipleSaves.close();

					this->displayingText.setString("<Empty>");
					this->displayingText.setPosition(p2pX(67.0f, vm) - (this->displayingText.getGlobalBounds().width / 2.f), p2pY(60.0f, vm));
				}
			}
		}
	}
}

#pragma endregion