#ifndef Launher_hpp
#define Launher_hpp

#include <SFML/Graphics.hpp>

#include <sstream>
#include <map>
#include <vector>

#include "AssetsOfGame.h"
#include "StateOfProgram.h"
#include "TextButton.h"
#include "MainMenu.h"

class Launcher : public IStateOfProgram
{
	std::shared_ptr<AssetsOfGame> ptrGame = nullptr;

	std::map<std::string, TextButton*> mapButtons;
	std::vector<sf::VideoMode> videoModes;
	std::vector<std::string> stringVideoModes;

	int iterator = 0;
	int sizeWidth[10], sizeHeight[10];

	std::string tabOfSizes[10];

	sf::RectangleShape background;
	sf::RectangleShape gamelogo;
	sf::Font font;
	sf::Text resolutionText;

	void InitGui();
	void InitBackground();

public:
	Launcher() = default;
	Launcher(std::shared_ptr<AssetsOfGame> ptrGame);
	virtual ~Launcher();

	void UpdateObject(float elapsedTime) override;
	void DrawObject(float elapsedTime) override;
	void InitializeObject() override;
	void HoldInput() override;
};

#endif // !Launher_hpp