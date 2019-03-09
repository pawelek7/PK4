#include "Game.h"

Game::Game()
{
	ptrGame->window.create(sf::VideoMode(800, 600), "test", sf::Style::Close | sf::Style::Titlebar);
	ptrGame->stateMachine.NewState(std::unique_ptr<StateOfProgram>(new MainMenu(ptrGame)));
}


void Game::RunGame()
{
	do
	{
		this->ptrGame->stateMachine.ChangeState();
		while (accumulator > update)
		{
			accumulator -= update;
			elapsedTime = update.asSeconds();
			ptrGame->stateMachine.GetStateFromStack()->UpdateObject(elapsedTime);
		}
		this->ptrGame->stateMachine.ChangeState();

		ptrGame->window.clear();
		ptrGame->stateMachine.GetStateFromStack()->DrawObject();
		ptrGame->window.display();
		accumulator += clock.restart();
		EventUpdate();
		UpdateMouse();
	} while (ptrGame->window.isOpen());
}

void Game::EventUpdate()
{
	while (this->ptrGame->window.pollEvent(this->event))
	{
		if (this->event.type == sf::Event::Closed)
		{
			this->ptrGame->window.close();
		}
	}
}

void Game::UpdateMouse()
{
	this->ptrGame->mousePosScreen = sf::Mouse::getPosition();
	this->ptrGame->mousePosWindow = sf::Mouse::getPosition(this->ptrGame->window);
	this->ptrGame->mousePosView = this->ptrGame->window.mapPixelToCoords(sf::Mouse::getPosition(this->ptrGame->window));
	this->ptrGame->mousePosGrid = sf::Vector2u(
		static_cast<unsigned>(this->ptrGame->mousePosView.x),
		static_cast<unsigned>(this->ptrGame->mousePosView.y)
		);
}

void Game::DrawFramesPerSecond(float actualTime)
{

}