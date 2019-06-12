#ifndef Options_hpp
#define Options_hpp

#include <map>
#include <sstream>

#include "TextButton.h"
#include "DropList.h"
#include "StateOfProgram.h"
#include "ButtonBase.h"
#include "defines.h"

class Options : public IStateOfProgram
{
	std::shared_ptr<AssetsOfGame> ptrGame = nullptr;

	int iterator = 0, volume_iterator = 0;
	int sizeWidth[10], sizeHeight[10];

	std::string tabOfSizes[10];

	std::vector<sf::VideoMode> videoModes;
	std::vector<std::string> stringVideoModes;
	std::map<std::string, TextButton*> mapButtons;
	std::map<std::string, DropList*> dropList;

	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;
	sf::Text resolutionText, fullScreenText, musicText, volumeText, shadersText;

	void CorrectPosition();

public:
	Options(std::shared_ptr<AssetsOfGame> ptrGame);
	virtual ~Options();

	void UpdateObject(float elapsedTime) override;
	void DrawObject(float elapsedTime) override;
	void InitializeObject() override;
	void HoldInput() override;
};

#endif // !Options_hpp
