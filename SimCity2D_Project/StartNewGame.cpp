#include "StartNewGame.h"

#pragma region Constructors

StartNewGame::StartNewGame(std::shared_ptr<AssetsOfGame> ptrGame)
{
	this->ptrGame = ptrGame;

	this->seedActive = false;
	this->nameActife = false;

	this->ptrGame->textureManager.LoadAsset("new_game", "Resources/Textures/new_game.png");
}

StartNewGame::~StartNewGame()
{
	if (this->nameMapInput != nullptr)
	{
		delete this->nameMapInput;
		this->nameMapInput = nullptr;
	}

	if (this->seedMapInput != nullptr)
	{
		delete this->seedMapInput;
		this->seedMapInput = nullptr;
	}

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

void StartNewGame::UpdateObject(float elapsedTime)
{
	for (auto & i : this->mapButtons)
	{
		i.second->UpdateButton(this->ptrGame->mousePositionWindow, elapsedTime);
	}
}

void StartNewGame::DrawObject(float elapsedTime)
{
	this->ptrGame->window->draw(background);

	this->seedMapInput->Draw(this->ptrGame->window);
	this->nameMapInput->Draw(this->ptrGame->window);
	for (auto & i : this->mapButtons)
	{
		i.second->DrawButton(this->ptrGame->window);
	}
	this->ptrGame->window->draw(sizeMapText);
}

void StartNewGame::InitializeObject()
{
	this->mapButtons["APPLY"] = new TextButton(this->ptrGame->window->getSize().x * 0.7, this->ptrGame->window->getSize().y *0.75f,
		this->ptrGame->window->getSize().x * 0.25f, this->ptrGame->window->getSize().y * 0.05f,
		"APPLY", this->ptrGame->window->getSize().y * 0.05f, sf::Color::White, sf::Color(102, 153, 153), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), this->ptrGame);

	this->mapButtons["RETURN"] = new TextButton(this->ptrGame->window->getSize().x * 0.7, this->ptrGame->window->getSize().y *0.85,
		this->ptrGame->window->getSize().x * 0.25f, this->ptrGame->window->getSize().y * 0.05f,
		"RETURN", this->ptrGame->window->getSize().y * 0.05f, sf::Color::White, sf::Color(102, 153, 153), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), this->ptrGame);

	this->mapButtons["NEXT"] = new TextButton(this->ptrGame->window->getSize().x * 0.5, this->ptrGame->window->getSize().y *0.8,
		this->ptrGame->window->getSize().x * 0.1f, this->ptrGame->window->getSize().x * 0.05f,
		"->", this->ptrGame->window->getSize().y * 0.075f, sf::Color::White, sf::Color(102, 153, 153), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), this->ptrGame);

	this->mapButtons["BACK"] = new TextButton(this->ptrGame->window->getSize().x * 0.3, this->ptrGame->window->getSize().y *0.8,
		this->ptrGame->window->getSize().x * 0.1f, this->ptrGame->window->getSize().x * 0.05f,
		"<-", this->ptrGame->window->getSize().y * 0.075f, sf::Color::White, sf::Color(102, 153, 153), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), this->ptrGame);

	this->mapButtons["APPLY"]->ChangeButtonPosition(this->ptrGame->window->getSize().x * 0.8 - (this->mapButtons["APPLY"]->GetText().getGlobalBounds().width / 2.f), this->ptrGame->window->getSize().y *0.80);
	this->mapButtons["RETURN"]->ChangeButtonPosition(this->ptrGame->window->getSize().x * 0.8 - (this->mapButtons["RETURN"]->GetText().getGlobalBounds().width / 2.f), this->ptrGame->window->getSize().y *0.85);
	this->mapButtons["NEXT"]->ChangeButtonPosition(this->ptrGame->window->getSize().x * 0.65 - (this->mapButtons["NEXT"]->GetText().getGlobalBounds().width / 2.f), this->ptrGame->window->getSize().y *0.8);
	this->mapButtons["BACK"]->ChangeButtonPosition(this->ptrGame->window->getSize().x * 0.45 - (this->mapButtons["BACK"]->GetText().getGlobalBounds().width / 2.f), this->ptrGame->window->getSize().y *0.8);

	this->nameMapInput = new TextBoxInput
	(this->ptrGame->window->getSize().x * 0.28, this->ptrGame->window->getSize().y *0.35, this->ptrGame->window->getSize().x * 0.4f, this->ptrGame->window->getSize().y * 0.075f, "Resources/Fonts/Delimax.ttf");
	this->seedMapInput = new TextBoxInput
		(this->ptrGame->window->getSize().x * 0.28, this->ptrGame->window->getSize().y *0.64, this->ptrGame->window->getSize().x * 0.4f, this->ptrGame->window->getSize().y * 0.075f, "Resources/Fonts/Delimax.ttf", true);

	this->font.loadFromFile("Resources/Fonts/Delimax.ttf");

	this->sizeMapText.setFont(font);
	this->sizeMapText.setFillColor(sf::Color::White);
	this->sizeMapText.setCharacterSize(this->ptrGame->window->getSize().y * 0.075f);
	this->sizeMapText.setString(std::to_string(mapSizes[iterator]));

	this->background.setSize(sf::Vector2f(static_cast<float>(this->ptrGame->window->getSize().x),
		static_cast<float>(this->ptrGame->window->getSize().y)));

	this->background.setTexture(&this->ptrGame->textureManager.GetAsset("new_game"));
}

void StartNewGame::HoldInput()
{
	while (this->ptrGame->window->pollEvent(events))
	{
		if (this->mapButtons["APPLY"]->GetPressed())
		{
			if (this->nameMapInput->GetString().empty())
			{
				this->nameMapInput->SetString("Unknown");
			}

			if (this->seedMapInput->GetString().empty())
			{
				this->seedMapInput->SetString("1");
			}

			ptrGame->stateMachine.NewState(std::unique_ptr<IStateOfProgram>(new GameLoop(ptrGame, 
				this->nameMapInput->GetString(), std::stoll(this->seedMapInput->GetString()), mapSizes[iterator], false)), "GameLoop", true);
			ptrGame->stateMachine.PopState();
			return;
		}

		if (this->mapButtons["RETURN"]->GetPressed())
		{
			ptrGame->stateMachine.PopState();
			return;
		}

		if (this->mapButtons["NEXT"]->GetPressed())
		{
			iterator++;

			if (iterator >= 5)
				iterator = 0;

			std::stringstream ss;
			ss << mapSizes[iterator];
			this->sizeMapText.setString(ss.str());
		}

		if (this->mapButtons["BACK"]->GetPressed())
		{
			iterator--;
			if (iterator <= -1)
				iterator = 4;

			std::stringstream ss;
			ss << mapSizes[iterator];
			this->sizeMapText.setString(ss.str());
		}

		this->seedMapInput->Update(events, sf::Vector2f(this->ptrGame->mousePositionWindow.x, this->ptrGame->mousePositionWindow.y));
		this->nameMapInput->Update(events, sf::Vector2f(this->ptrGame->mousePositionWindow.x, this->ptrGame->mousePositionWindow.y));

		this->sizeMapText.setPosition(this->ptrGame->window->getSize().x * 0.55 - (this->sizeMapText.getGlobalBounds().width / 2.f), this->ptrGame->window->getSize().y *0.8);


		if (this->events.type==sf::Event::Closed)
		{
			this->ptrGame->window->close();
		}
	}
}

#pragma endregion