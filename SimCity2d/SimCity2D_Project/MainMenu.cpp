#include "MainMenu.h"

MainMenu::MainMenu(std::shared_ptr<GameAssets> ptrGame) :ptrGame(ptrGame)
{
	this->ptrGame->fontManager.LoadAsset("Delimax", "Resources/Font/Delimax.ttf");
	this->ptrGame->textureManager.LoadAsset("SimCity_background", "Resources/Textures/SimCity_background.jpg");
	//this->ptrGame->soundManager.LoadAsset("SimCity Music - The Long Construction", "Resources/Music/SimCity Music - The Long Construction.mp3");
};

void MainMenu::InitializeObject()
{
	//musicMenu.loadFromFile("Resources/Music/SimCity.ogg"); 
	//! do not forget to fix reading from file music

	this->background.setSize(
		sf::Vector2f
		(
		static_cast<float>(ptrGame->window.getSize().x),
		static_cast<float>(ptrGame->window.getSize().y)
		)
	);
	this->background.setTexture(&this->ptrGame->textureManager.GetAsset("SimCity_background"));
	this->font.loadFromFile("Resources/Font/Delimax.ttf"); //temporary solution!!!

	this->buttons["GAME"] = new Gui::Button(
		this->ptrGame->window.getSize().x/2 - 100, this->ptrGame->window.getSize().y / 2-250, 250.f, 50.f,
		&this->font, "New Game", 50,
		sf::Color(70, 255, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["SETTINGS"] = new Gui::Button(
		this->ptrGame->window.getSize().x / 2 - 100, this->ptrGame->window.getSize().y / 2 -175, 250.f, 50.f,
		&this->font, "Settings", 50,
		sf::Color(70, 255, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["CREATE_MAP"] = new Gui::Button(
		this->ptrGame->window.getSize().x / 2 - 100, this->ptrGame->window.getSize().y / 2 - 100, 250.f, 50.f,
		&this->font, "Create Map", 50,
		sf::Color(70, 255, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["EXIT"] = new Gui::Button(
		this->ptrGame->window.getSize().x / 2 - 100, this->ptrGame->window.getSize().y / 2 - 25 , 250.f, 50.f,
		&this->font, "Quit", 50,
		sf::Color(70, 255, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

MainMenu::~MainMenu()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void MainMenu::UpdateObject(float elapsedTime)
{
	for (auto &it : this->buttons)
	{
		it.second->update(this->ptrGame->mousePosView);
	}
}

void MainMenu::DrawObject(float elapsedTime)
{
	
	this->ptrGame->window.draw(background);
	for (auto &it : this->buttons)
	{
		it.second->render(ptrGame->window);
	}
}

void MainMenu::HoldInput()
{
	//New game
	if (this->buttons["GAME"]->isPressed())
	{
		ptrGame->stateMachine.NewState(std::unique_ptr<StateOfProgram>(new GameLoop(ptrGame)), "Game");
	}

	//Settings
	if (this->buttons["SETTINGS"]->isPressed())
	{
		ptrGame->stateMachine.NewState(std::unique_ptr<StateOfProgram>(new Options(ptrGame)), "Options");
	}

	if (this->buttons["CREATE_MAP"]->isPressed())
	{
		ptrGame->stateMachine.NewState(std::unique_ptr<StateOfProgram>(new CreateMap(ptrGame)), "Create map");
	}

	//Quit the game
	if (this->buttons["EXIT"]->isPressed())
	{
		this->ptrGame->window.close();
	}
}