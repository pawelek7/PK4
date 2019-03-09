#pragma once

#include "StateOfProgram.h"
#include "GameAssets.h"
#include "Gui.h"
#include "Options.h"

class MainMenu : public StateOfProgram
{
	sf::SoundBuffer musicMenu;
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, Gui::Button*> buttons;

	std::shared_ptr<GameAssets> ptrGame = nullptr;
public:
	MainMenu(std::shared_ptr<GameAssets> ptrGame);
	virtual ~MainMenu();

	void UpdateObject(float elapsedTime);
	void DrawObject();
	void InitializeObject();
};