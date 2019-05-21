#include "Game.h"

#pragma region Constructors

Game::Game()
{
	this->ptrGame->window = new sf::RenderWindow(sf::VideoMode(BASIC_WIDTH, BASIC_HEIGHT), 
		GAME_NAME, sf::Style::Close | sf::Style::Titlebar);

	this->LoadBasicAssets();

	this->ptrGame->stateMachine.NewState(
		std::unique_ptr<StateOfProgram>(new Launcher(this->ptrGame)), "Launcher");

	this->ptrGame->audioManagement = new AudioManagement();
	this->ptrGame->audioManagement->AddSoundToPlaylist("Resources/Music/Magic Scout - Farm.ogg");
	this->ptrGame->audioManagement->AddSoundToPlaylist("Resources/Music/Crinoline Dreams.ogg");
	
	this->ptrGame->audioManagement->PlaySound("Resources/Music/Magic Scout - Farm.ogg");
}

Game::~Game()
{
	delete this->ptrGame->window;
}

#pragma endregion

#pragma region Class_Methods

void Game::HoldGame()
{
	while (this->ptrGame->window->isOpen())
	{
		while (this->accumulator > this->update)
		{
			this->ptrGame->stateMachine.ChangeState();

			this->accumulator -= this->update;
			this->elapsedTime = this->update.asSeconds();

			this->MouseUpdate();

			this->ptrGame->window->clear();
			this->ptrGame->stateMachine.GetStateFromStack()->DrawObject(elapsedTime);
			this->ptrGame->window->display();

			this->ptrGame->stateMachine.GetStateFromStack()->HoldInput();
	
			this->ptrGame->stateMachine.GetStateFromStack()->UpdateObject(elapsedTime);
			this->ptrGame->audioManagement->UpdateAudio();
		}
		this->ptrGame->stateMachine.ChangeState();

		this->accumulator += this->clock.restart();
	}
	
}

void Game::ShowFPS(float elapsedTime)
{
	int m_fps = 1.0f / (elapsedTime);
	std::ostringstream tmp;
	tmp << m_fps;
	framesPerSecond.setString(tmp.str() + "FPS");
	framesPerSecond.setPosition(this->ptrGame->window->getView().getCenter().x / 2, this->ptrGame->window->getView().getCenter().y / 2);
	this->ptrGame->window->draw(framesPerSecond);
}

void Game::MouseUpdate()
{
	this->ptrGame->mousePositionMap = sf::Mouse::getPosition();
	this->ptrGame->mousePositionMap = (sf::Vector2i)this->ptrGame->window->mapPixelToCoords(sf::Mouse::getPosition(*this->ptrGame->window));
	this->ptrGame->mousePositionWindow = (sf::Vector2f)sf::Mouse::getPosition(*this->ptrGame->window);
}

void Game::LoadBasicAssets()
{
	this->ptrGame->fontManager.LoadAsset("Delimax", "Resources/Fonts/Delimax.ttf");
	framesPerSecond.setFont(this->ptrGame->fontManager.GetAsset("Delimax"));
	framesPerSecond.setFillColor(sf::Color::Green);
}

#pragma endregion