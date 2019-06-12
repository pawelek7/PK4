#ifndef StartNewGame_hpp
#define StartMewGame_hpp

#include <sstream>

#include "TextBoxInput.h"
#include "StateOfProgram.h"
#include "AssetsOfGame.h"
#include "TextButton.h"
#include "GameLoop.h"

class StartNewGame : public IStateOfProgram
{
	std::shared_ptr<AssetsOfGame> ptrGame = nullptr;

	TextBoxInput *nameMapInput = nullptr;
	TextBoxInput *seedMapInput = nullptr;

	std::map<std::string, TextButton*> mapButtons;

	bool nameActife = false;
	bool seedActive = false;

	int mapSizes[4] = { 16, 32, 64, 128 };
	int iterator = 0;

	sf::Font font;
	sf::Text sizeMapText;
	sf::RectangleShape background;
	sf::Event events;

public:
	StartNewGame() = default;
	StartNewGame(std::shared_ptr<AssetsOfGame> ptrGame);
	virtual ~StartNewGame();

	void UpdateObject(float elapsedTime) override;
	void DrawObject(float elapsedTime) override;
	void InitializeObject() override;
	void HoldInput() override;
};

#endif // !StartNewGame_hpp