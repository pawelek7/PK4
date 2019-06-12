#include "MainMenu.h"

#pragma region Constructors

MainMenu::MainMenu(std::shared_ptr<AssetsOfGame> ptrGame)
	:ptrGame(ptrGame)
{
	this->ptrGame->textureManager.LoadAsset("background", "Resources/Textures/background.png");
}

MainMenu::~MainMenu()
{
	auto iterator = this->mapButtons.begin();
	for (iterator = this->mapButtons.begin(); iterator != this->mapButtons.end(); iterator++)
	{
		if (iterator->second != nullptr)
		{
			delete iterator->second;
			iterator->second = nullptr;
		}
	}
}

#pragma endregion

#pragma region Class_Methods

void MainMenu::InitializeObject()
{
	this->InitializeFonts();
	this->InitializeButtons();
	this->InitializeBackground();
}

void MainMenu::InitializeBackground()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->ptrGame->window->getSize().x),
		static_cast<float>(this->ptrGame->window->getSize().y)));

	this->background.setTexture(&this->ptrGame->textureManager.GetAsset("background"));
}

void MainMenu::InitializeFonts()
{
	this->font.loadFromFile("Resources/Fonts/Delimax.ttf"); //temporary solution!!!
}

void MainMenu::InitializeButtons()
{
	const sf::VideoMode &vm = this->ptrGame->videoMode;

	for (int i = 0; i < buttonNames.size(); i++)
	{
		this->mapButtons[buttonNames[i]] = (new TextButton(p2pX(15.6f, vm),
			p2pY(40.0f + i * 10, vm), p2pX(13.f, vm), p2pY(6.f, vm),
			buttonNames[i],calcCharSize(vm), sf::Color(70, 255, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
			sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), this->ptrGame));
	}
}

void MainMenu::UpdateObject(float elapsedTime)
{
	this->ptrGame->window->setView(this->ptrGame->window->getDefaultView());
	this->ResetButtonsPosition();
	this->background.setSize(sf::Vector2f(static_cast<float>(this->ptrGame->window->getSize().x),
		static_cast<float>(this->ptrGame->window->getSize().y)));

	for (auto & i : this->mapButtons)
	{
		i.second->UpdateButton(this->ptrGame->mousePositionWindow, elapsedTime);
	}

	if (this->mapButtons["NEW GAME"]->GetPressed())
	{
		ptrGame->stateMachine.NewState(std::unique_ptr<IStateOfProgram>(new StartNewGame(ptrGame)), "StartNewGame", true);
	}

	if (this->mapButtons["LOAD GAME"]->GetPressed())
	{
		ptrGame->stateMachine.NewState(std::unique_ptr<IStateOfProgram>(new LoadGame(ptrGame)), "LoadGame", true);
	}

	if (this->mapButtons["OPTIONS"]->GetPressed())
	{
		ptrGame->stateMachine.NewState(std::unique_ptr<IStateOfProgram>(new Options(ptrGame)), "Options", true);
	}

	if (this->mapButtons["EXIT"]->GetPressed())
	{
		this->ptrGame->window->close();
	}
}

void MainMenu::ResetButtonsPosition()
{
	for (int i = 0; i < buttonNames.size(); i++)
	{
		this->mapButtons[buttonNames[i]]->ChangePositionAndSize(p2pX(15.6f, this->ptrGame->videoMode),
			p2pY(40.0f + i * 10, this->ptrGame->videoMode), p2pX(13.f, this->ptrGame->videoMode), p2pY(6.f, this->ptrGame->videoMode),
			calcCharSize(this->ptrGame->videoMode));
	}
}

void MainMenu::DrawObject(float elapsedTime)
{
	this->ptrGame->window->draw(background);

	for (auto & i : this->mapButtons)
	{
		i.second->DrawButton(this->ptrGame->window);
	}
}

void MainMenu::HoldInput()
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

#pragma endregion