#include "Launcher.h"

#pragma region Constructors

Launcher::Launcher(std::shared_ptr<AssetsOfGame> ptrGame) :ptrGame(ptrGame)
{
	this->videoModes = sf::VideoMode::getFullscreenModes();

	this->ptrGame->textureManager.LoadAsset("launcher_background", "Resources/Textures/launcher_background.png");
	this->ptrGame->textureManager.LoadAsset("game_logo", "Resources/Textures/game_logo.png");
}

Launcher::~Launcher()
{
	auto i = this->mapButtons.begin();
	for (i = this->mapButtons.begin(); i != this->mapButtons.end(); i++)
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

void Launcher::UpdateObject(float elapsedTime)
{
	this->ptrGame->window->setView(this->ptrGame->window->getDefaultView());

	for (auto & i : this->mapButtons)
	{
		i.second->UpdateButton((sf::Vector2f)this->ptrGame->mousePositionWindow, elapsedTime);
	}

	if (this->mapButtons["NEXT"]->GetPressed())
	{
		iterator--;
		if (iterator <= -1)
			iterator = 9;

		std::stringstream ss;
		ss << tabOfSizes[iterator];
		this->resolutionText.setString(ss.str());

	}

	if (this->mapButtons["BACK"]->GetPressed())
	{
		iterator++;
		if (iterator >= 10)
			iterator = 0;

		std::stringstream ss;
		ss << tabOfSizes[iterator];
		this->resolutionText.setString(ss.str());
	}
	this->resolutionText.setPosition(this->ptrGame->window->getSize().x / 2 - (this->resolutionText.getGlobalBounds().width / 2.f), this->ptrGame->window->getSize().y / 2);

	if (this->mapButtons["OK"]->GetPressed())
	{
		this->ptrGame->window->create(sf::VideoMode(sizeWidth[iterator], sizeHeight[iterator]), GAME_NAME, sf::Style::Close | sf::Style::Titlebar);
		this->ptrGame->videoMode.width = sizeWidth[iterator];
		this->ptrGame->videoMode.height = sizeHeight[iterator];
		this->ptrGame->stateMachine.NewState(std::unique_ptr<IStateOfProgram>(new MainMenu(this->ptrGame)), "MainMenu");
		this->~Launcher();
	}
}

void Launcher::DrawObject(float elapsedTime)
{
	this->ptrGame->window->draw(background);
	for (auto & i : this->mapButtons)
	{
		i.second->DrawButton(this->ptrGame->window);
	}
	this->ptrGame->window->draw(gamelogo);
	this->ptrGame->window->draw(resolutionText);
}

void Launcher::HoldInput()
{
	sf::Event sfmlEvent;

	while (this->ptrGame->window->pollEvent(sfmlEvent))
	{
		switch (sfmlEvent.type)
		{
		case sf::Event::Closed:
			this->ptrGame->window->close();
			break;
		case sf::Event::KeyPressed:
			if (sfmlEvent.key.code == sf::Keyboard::Escape)
			{
				this->ptrGame->window->close();
			}
			break;
		}
	}
}

void Launcher::InitializeObject()
{
	this->InitBackground();
	this->InitGui();
}

void Launcher::InitBackground()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->ptrGame->window->getSize().x),
		static_cast<float>(this->ptrGame->window->getSize().y)));
	this->gamelogo.setSize(sf::Vector2f(464, 145));

	this->gamelogo.setPosition(this->ptrGame->window->getSize().x / 2-232, this->ptrGame->window->getSize().y / 2 - 250);

	this->background.setTexture(&this->ptrGame->textureManager.GetAsset("launcher_background"));
	this->gamelogo.setTexture(&this->ptrGame->textureManager.GetAsset("game_logo"));
}

void Launcher::InitGui()
{
	this->font.loadFromFile("Resources/Fonts/Delimax.ttf"); //! fix later!

	this->mapButtons["NEXT"] = new TextButton(540.0f, this->ptrGame->window->getSize().y - 300, 250.0f, 50.0f,
		"->", 50, sf::Color::Yellow, sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), this->ptrGame);

	this->mapButtons["BACK"] = new TextButton(0.0f, this->ptrGame->window->getSize().y - 300, 250.0f, 50.0f,
		"<-", 50, sf::Color::Yellow, sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), this->ptrGame);

	this->mapButtons["OK"] = new TextButton(270.0f, this->ptrGame->window->getSize().y - 100, 250.0f, 50.0f,
		"APPLY", 50, sf::Color::Yellow, sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), this->ptrGame);

	for (auto &i : this->videoModes)
	{
		tabOfSizes[iterator] = std::to_string(i.width) + 'x' + std::to_string(i.height);
		sizeWidth[iterator] = i.width;
		sizeHeight[iterator] = i.height;
		iterator++;

		if (iterator > 9)
		{
			break;
		}
	}
	iterator = 0;

	this->resolutionText.setFont(font);
	this->resolutionText.setFillColor(sf::Color::Magenta);
	this->resolutionText.setCharacterSize(50);
	this->resolutionText.setPosition(this->ptrGame->window->getSize().x / 2 - (this->resolutionText.getGlobalBounds().width / 2.f), this->ptrGame->window->getSize().y / 2);
	this->resolutionText.setString(tabOfSizes[iterator]);
}

#pragma endregion