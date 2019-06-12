#ifndef HudUp_hpp
#define HudUp_hpp

#include <SFML/Graphics.hpp>

#include <vector>
#include <map>

#include "TextButton.h"
#include "AssetsOfGame.h"
#include "DropList.h"
#include "ButtonBase.h"

class HudUp
{
	std::vector<TextButton*> buttons;
	std::map<std::string, DropList*> dropList;

	bool drawDecreaseText = false;
	bool cursorOnHudUp = false;
	bool readySelectedOption = false;

	float x = 0.0f;
	float y = 0.0f;
	float windowSizeX = 0.0f;
	float windowSizeY = 0.0f;

	std::string clickedOption = "unknown";

	sf::Font& font;
	sf::RectangleShape rectangleHUD;
	sf::Text dateText, moneyText, decreateMoneyText, populationText;

public:
	HudUp() = default;
	HudUp(sf::Texture & textureHUD, sf::Texture & iconsHUD, float windowSizeX, float windowSizeY,
		float x, float y, float width, float height, sf::Font & font, std::shared_ptr<AssetsOfGame> ptrGame,
		sf::VideoMode & vm,unsigned int index = 0);
	virtual ~HudUp();

	void UpdateHUD(const sf::Vector2i& mousePosition, const float & elapsedTime);
	void DrawHUD(sf::RenderTarget *renderTarget);

	void UpdateDate(const std::string & date);
	void UpdateMoneyAmount(int moneyAmount);
	void isDrawDecreaseMoney(bool option);

	//setters
	void SetDecreaseMoneyText(int decreaseMoney);
	void SetPopulationText(int population);

	//getters
	bool GetCursorOnHudUp();
	bool GetIsReadySelectedOption();
	std::string GetClickedOption();
};

#endif // !HudUp_hpp