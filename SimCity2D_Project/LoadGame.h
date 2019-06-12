#ifndef LoadGame_hpp
#define LoadGame_hpp

#include "StateOfProgram.h"
#include "AssetsOfGame.h"
#include "TableInformation.h"
#include "ButtonBase.h"
#include "TextButton.h"
#include "GameLoop.h"

class LoadGame : public IStateOfProgram
{
	std::shared_ptr<AssetsOfGame> ptrGame = nullptr;

	std::string mapName = "unknown";

	std::map<std::string, TableInformation> tableInfSystem;
	std::map<std::string, TextButton*> mapButtons;
	std::vector<std::string> mapNamesVector;

	sf::RectangleShape background;
	sf::Text displayingText;
	sf::Font font;
	sf::Event events;

public:
	LoadGame() = default;
	LoadGame(std::shared_ptr<AssetsOfGame> ptrGame);
	virtual ~LoadGame();

	void UpdateObject(float elapsedTime) override;
	void DrawObject(float elapsedTime) override;
	void InitializeObject() override;
	void HoldInput() override;
};

#endif // !LoadGame_hpp