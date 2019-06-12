#ifndef Game_hpp
#define Game_hpp

#include <SFML/Graphics.hpp>

#include "defines.h"
#include "AssetsOfGame.h"
#include "Launcher.h"
#include "AudioManagement.h"
#include "NoCopyNoMove.h"

/*
A class that supports the entire game application.

@author
Pawel Salicki
*/

class Game : public NoCopyNoMove
{
	float elapsedTime = 0.0f; //time between calls to the functions responsible for drawing and updating
	std::shared_ptr<AssetsOfGame> ptrGame = std::make_shared<AssetsOfGame>(); //smart indicator on the asset structure

	sf::Event holdEvents; //window events (resizing, mouse etc...)
	sf::Text framesPerSecond; //text that shows frames per second

	sf::Clock clock; //clock
	sf::Time accumulator = sf::Time::Zero; //accumulator
	sf::Time update = sf::seconds(FPS); //update time

	void MouseUpdate(); //mouse update
	void LoadBasicAssets(); //loading basic assets
	void ShowFPS(const float elapsedTime); //drawing frames per second

public:
	Game(); //game constructor
	virtual ~Game(); //destructor

	void HoldGame(); //run game
};

#endif // !Game_hpp