#ifndef HudLeft_hpp
#define HudLeft_hpp

#include <SFML/Graphics.hpp>

#include <map>

#include "PictureButton.h"

class HudLeft
{
public:
	enum class ButtonIDs
	{
		VOID = 0, HOMES_ACTIVE = 1, HOMES_HOVER = 2, FACTORY_ACTIVE = 3, FACTORY_HOVER = 4,
		SHOPS_ACTIVE = 5, SHOPS_HOVER = 6, POWER_ACTIVE = 7, POWER_HOVER = 8,
		ROAD_ACTIVE = 9, ROAD_HOVER = 10, WATER_ACTIVE = 11, WATER_HOVER = 12,
		DESTROY_ACTIVE = 13, DESTROY_HOVER = 14, HOSPITAL_ACTIVE = 15, HOSPITAL_HOVER = 16,
		TAXES_ACTIVE = 17, TAXES_HOVER = 18, FIRE_ACTIVE = 19, FIRE_HOVER = 20,
		POLICE_ACTIVE = 21, POLICE_HOVER = 22, TREE_ACTIVE = 23, TREE_HOVER = 24,
		STATUE_ACTIVE = 25, STATUE_HOVER = 26
	};

private:
	ButtonIDs buttonID1 = ButtonIDs::VOID, buttonID2 = ButtonIDs::VOID;

	std::map<ButtonIDs, sf::RectangleShape> buttonRectangleMap;
	std::vector<PictureButton*> pictureButtons;
	std::shared_ptr<AssetsOfGame> ptrGame = nullptr;

	bool mouseOnHud = false;
	short id = 0;

	sf::Text text;
	sf::RectangleShape iconsHUD;

public:
	HudLeft() = default;
	HudLeft(float x, float y, float width, float height, float windowSizeX, float windowSizeY,
		std::shared_ptr<AssetsOfGame> ptrGame, unsigned int id = 0);
	virtual ~HudLeft();

	void UpdateHUDleft(const sf::Vector2i& mousePosition, const float & elapsedTime);
	void DrawHUDleft(sf::RenderTarget *renderTarget);

	//setters
	void SetString(const sf::String & string);

	//getters
	const unsigned short & getActiveElementId() const;
	const sf::String & GetString() const;
	bool GetMouseOnHud();
	std::string GetButtonOption1();
	std::string GetButtonOption2();
};

#endif // !HudLeft_hpp