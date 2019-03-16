#pragma once

#include <SFML/Graphics.hpp>
#include "GameAssets.h"

#include "MainMenu.h"

class Game
{
	float elapsedTime = 0.0f;
	std::shared_ptr<GameAssets> ptrGame = std::make_shared<GameAssets>();

	sf::Event event;
	sf::Text framesPerSecond;
	sf::Clock clock;
	sf::Time accumulator;
	sf::Time update = sf::seconds(1.0f/60.0f);

public:
	Game();
	~Game() = default;

	void DrawFramesPerSecond(float actualTime);
	void EventUpdate();
	void UpdateMouse();
	void RunGame();
};