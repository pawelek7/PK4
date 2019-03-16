#ifndef MainMenu_hpp
#define MainMenu_hpp

#include "StateOfProgram.h"
#include "GameAssets.h"
#include "Gui.h"
#include "Options.h"
#include "GameLoop.h"
#include "CreateMap.h"

class MainMenu : public StateOfProgram
{
	std::map<std::string, Gui::Button*> buttons;
	std::shared_ptr<GameAssets> ptrGame = nullptr;

//	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

public:
	MainMenu(std::shared_ptr<GameAssets> ptrGame);
	virtual ~MainMenu();

	void UpdateObject(float elapsedTime) override;
	void DrawObject(float elapsedTime) override;
	void InitializeObject() override;
	void HoldInput() override;
};

#endif // !MainMenu_hpp