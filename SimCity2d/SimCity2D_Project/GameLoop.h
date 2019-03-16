#pragma once

#include "MapTile.h"
#include "StateMachine.h"
#include "StateOfProgram.h"
#include "GameAssets.h"

class GameLoop : public StateOfProgram
{
	std::shared_ptr<GameAssets> ptrGame = nullptr;
	MapTile map;

	sf::Vector2i oldMousePos, newMousePos;

	sf::View camera;
	const float zoomAmount{ 1.1f };

	/*
	std::string str;
	sf::Text text;
	sf::Font font;
	*/

	
public:
	GameLoop() = default;
	GameLoop(std::shared_ptr<GameAssets> ptrGame);

	void zoomViewAt(sf::Vector2i pixel, sf::RenderWindow& window, float zoom);
	void UpdateObject(float elapsedTime);
	void DrawObject(float elapsedTime);
	void InitializeObject();
	void HoldInput();
};
