#pragma once

#include "StateOfProgram.h"
#include "GameAssets.h"
#include "Gui.h"
#include "MainMenu.h"

class Options : public StateOfProgram
{
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, Gui::Button*> buttons;
	std::map<std::string, Gui::DropDownList*> dropDownList;

	sf::Text optionsText;

	std::vector<sf::VideoMode> modes;
	std::shared_ptr<GameAssets> ptrGame = nullptr;

public:
	Options(std::shared_ptr<GameAssets> ptrGame);
	virtual ~Options();
	void UpdateObject(float elapsedTime);
	void DrawObject();
	void InitializeObject();

};