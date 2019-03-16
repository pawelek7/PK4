#pragma once

#include "StateOfProgram.h"
#include "GameAssets.h"
#include "Gui.h"
#include "MainMenu.h"

class Options : public StateOfProgram
{
	std::shared_ptr<GameAssets> ptrGame = nullptr;
	std::vector<sf::VideoMode> modes;
	std::map<std::string, Gui::Button*> buttons;
	std::map<std::string, Gui::DropDownList*> dropDownList;

	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;
	sf::Text optionsText;

public:
	Options(std::shared_ptr<GameAssets> ptrGame);
	virtual ~Options();

	void UpdateObject(float elapsedTime) override;
	void DrawObject(float elapsedTime) override;
	void InitializeObject() override;
	void HoldInput() override;
};