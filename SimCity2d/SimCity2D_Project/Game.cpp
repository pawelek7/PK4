#include "Game.h"

Game::Game()
{
	ptrGame->window.create(sf::VideoMode(800, 600), "Project - Simcity 2000", sf::Style::Close | sf::Style::Titlebar);
	ptrGame->stateMachine.NewState(std::unique_ptr<StateOfProgram>(new MainMenu(ptrGame)), "MainMenu");
}

void Game::RunGame()
{
	while (ptrGame->window.isOpen())
	{
		this->ptrGame->stateMachine.ChangeState();
		while (accumulator > update)
		{
			accumulator -= update;
			elapsedTime = update.asSeconds();
			ptrGame->stateMachine.GetStateFromStack()->HoldInput();
			EventUpdate();
			ptrGame->stateMachine.GetStateFromStack()->UpdateObject(elapsedTime);
		}
		this->ptrGame->stateMachine.ChangeState();

		ptrGame->window.clear();
		ptrGame->stateMachine.GetStateFromStack()->DrawObject(elapsedTime);
		ptrGame->window.display();

		accumulator += clock.restart();
		UpdateMouse();
	} 
}

void Game::EventUpdate()
{
	while (this->ptrGame->window.pollEvent(this->event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			this->ptrGame->window.close();
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
			{
				this->ptrGame->window.close();
			}
			break;
		}

		/*
		if (this->event.type == sf::Event::Closed)
		{
			this->ptrGame->window.close();
		}
		*/
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