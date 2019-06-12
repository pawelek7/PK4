#ifndef MainMenu_hpp
#define MainMenu_hpp

#include <SFML/Graphics.hpp>

#include <map>

#include "AssetsOfGame.h"
#include "StateOfProgram.h"
#include "TextButton.h"
#include "GameLoop.h"
#include "StartNewGame.h"
#include "ButtonBase.h"
#include "LoadGame.h"
#include "Options.h"

class MainMenu : public IStateOfProgram
{
	std::shared_ptr<AssetsOfGame> ptrGame = nullptr;

	std::map<std::string, TextButton*> mapButtons;
	std::vector<std::string> buttonNames{ "NEW GAME", "LOAD GAME", "OPTIONS", "EXIT" };

	sf::RectangleShape background;
	sf::Font font;

	void InitializeFonts();
	void InitializeButtons();
	void InitializeBackground();
	void ResetButtonsPosition();

public:
	MainMenu() = default;
	MainMenu(std::shared_ptr<AssetsOfGame> ptrGame);
	virtual ~MainMenu();

	void UpdateObject(float elapsedTime) override;
	void DrawObject(float elapsedTime) override;
	void InitializeObject() override;
	void HoldInput() override;
};

#endif // !MainMenu_hpp