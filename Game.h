#ifndef Game_hpp
#define Game_hpp

#include <SFML/Graphics.hpp>

#include "defines.h"
#include "AssetsOfGame.h"
#include "Launcher.h"
#include "AudioManagement.h"

class Game
{
	float elapsedTime = 0.0f;
	std::shared_ptr<AssetsOfGame> ptrGame = std::make_shared<AssetsOfGame>();

	sf::Event holdEvents;
	sf::Text framesPerSecond;

	sf::Clock clock;
	sf::Time accumulator = sf::Time::Zero;
	sf::Time update = sf::seconds(FPS);

	void MouseUpdate();
	void LoadBasicAssets();
	void ShowFPS(float elapsedTime);

public:
	Game();
	virtual ~Game();

	void HoldGame();
};

#endif // !Game_hpp