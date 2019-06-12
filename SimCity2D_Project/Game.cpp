#include "Game.h"

#pragma region Constructors

#pragma region Description of the method

/*
A non-parameter constructur of GameClass.
This method create new application window
and loads basic resources.

method parameters:
____________________
no parameters

the return value:
____________________
no return value

@author
Pawel Salicki
*/

#pragma endregion

Game::Game()
{
	this->ptrGame->window = new sf::RenderWindow(sf::VideoMode(BASIC_WIDTH, BASIC_HEIGHT), 
		GAME_NAME, sf::Style::Close | sf::Style::Titlebar); //create window 800x600 no-resize

	this->ptrGame->stateMachine.NewState(
		std::unique_ptr<IStateOfProgram>(new Launcher(this->ptrGame)), "Launcher"); //create new state - Launher

	this->ptrGame->audioManagement = new AudioManagement(); //create audio

	this->LoadBasicAssets();
}

//destructor
Game::~Game()
{
	if (this->ptrGame->window != nullptr)
	{
		delete this->ptrGame->window; //delete application window
		this->ptrGame->window = nullptr;
	}

	if (this->ptrGame->audioManagement != nullptr)
	{
		delete this->ptrGame->audioManagement; //delete audio
		this->ptrGame->audioManagement = nullptr;
	}

}

#pragma endregion

#pragma region Class_Methods

#pragma region Description of the method

/*
A method that contains the main loop of the game. 
Invokes functions that are responsible for drawing and updating objects.
Makes sure that the game works in a stable number of frames.

method parameters:
____________________
no parameters

the return value:
____________________
no return value

@author
Pawel Salicki
*/

#pragma endregion

void Game::HoldGame()
{
	while (this->ptrGame->window->isOpen()) //while window of application is open
	{
		while (this->accumulator > this->update)
		{
			this->ptrGame->stateMachine.ChangeState(); //check if state of game is changed

			this->accumulator -= this->update; //update time
			this->elapsedTime = this->update.asSeconds();

			this->MouseUpdate(); //update mouse position and input

			this->ptrGame->window->clear(); //clear window of old pictures
			this->ptrGame->stateMachine.GetStateFromStack()->DrawObject(elapsedTime); //draw pictures
			this->ptrGame->window->display(); //display new pictures

			this->ptrGame->stateMachine.GetStateFromStack()->HoldInput(); //hold input from mouse and keyboard
	
			this->ptrGame->stateMachine.GetStateFromStack()->UpdateObject(elapsedTime); //update object
			this->ptrGame->audioManagement->UpdateAudio(); //update audio
		}
		this->ptrGame->stateMachine.ChangeState(); //check if state of game is changed

		this->accumulator += this->clock.restart(); //restart time
	}
}

#pragma region Description of the Method

/*
A method that draws frames per second on screen;

method parameters:
____________________
no parameters

the return value:
____________________
no return value

@author
Pawel Salicki
*/

#pragma endregion

void Game::ShowFPS(const float elapsedTime)
{
	int m_fps = 1.0f / (elapsedTime); //get fps number
	std::ostringstream tmp;
	tmp << m_fps;
	this->framesPerSecond.setString(tmp.str() + "FPS");
	this->framesPerSecond.setPosition(this->ptrGame->window->getView().getCenter().x / 2, this->ptrGame->window->getView().getCenter().y / 2);
	this->ptrGame->window->draw(framesPerSecond); //draw fps on screen
}

#pragma region Description of the Method

/*
A method that update mouse positions.

method parameters:
____________________
no parameters

the return value:
____________________
no return value

@author
Pawel Salicki
*/

#pragma endregion

void Game::MouseUpdate()
{
	this->ptrGame->mousePositionMap = sf::Mouse::getPosition(); //set position of mouse

	//mouse position on map in game
	this->ptrGame->mousePositionMap = (sf::Vector2i)this->ptrGame->window->mapPixelToCoords(sf::Mouse::getPosition(*this->ptrGame->window));

	//mouse position on window
	this->ptrGame->mousePositionWindow = (sf::Vector2f)sf::Mouse::getPosition(*this->ptrGame->window);
}

#pragma region Description of the method

/*
A method that loads basic assets from resources folder.
Music, textures, etc...

method parameters:
____________________
no parameters

the return value:
____________________
no return value

@author
Pawel Salicki
*/

#pragma endregion

void Game::LoadBasicAssets()
{
	this->ptrGame->fontManager.LoadAsset("Delimax", "Resources/Fonts/Delimax.ttf"); //load font
	this->framesPerSecond.setFont(this->ptrGame->fontManager.GetAsset("Delimax")); //set font
	this->framesPerSecond.setFillColor(sf::Color::Green);

	//load music and play it
	this->ptrGame->audioManagement->AddSoundToPlaylist("Resources/Music/Magic Scout - Farm.ogg");
	this->ptrGame->audioManagement->AddSoundToPlaylist("Resources/Music/Crinoline Dreams.ogg");

	this->ptrGame->audioManagement->PlaySound("Resources/Music/Magic Scout - Farm.ogg");
}

#pragma endregion