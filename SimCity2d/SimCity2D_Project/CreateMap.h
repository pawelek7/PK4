#pragma once

//!!! NOT IMPLEMENTED YET !!!

#include "CreateMap.h"
#include "Gui.h"
#include "MapTile.h"
#include "StateOfProgram.h"
#include "GameAssets.h"

#include <string>


class CreateMap : public StateOfProgram
{
	std::shared_ptr<GameAssets> ptrGame = nullptr;
	std::map<std::string, Gui::Button*> button;
	MapTile map;

	sf::Vector2i oldMousePos, newMousePos;
	sf::View camera, guiView;
	const float zoomAmount{ 1.1f };

	sf::Font font;
	sf::Text cursorText;
	sf::Text nameText;
	sf::IntRect textureRect;
	sf::RectangleShape selectorRect;
	Gui::SelectTexture *selectTexture;
	std::string sizeSquare = "";
	std::string nameMap = "";
	std::vector<char> nameMapV;
	bool created = false;
	sf::Vector2i selectFROM = sf::Vector2i(0, 0), selectTO = sf::Vector2i(0, 0);
	Plate* plate;

public:
	CreateMap(std::shared_ptr<GameAssets> ptrGame);
	virtual ~CreateMap() = default;
	void UpdateObject(float elapsedTime) override;
	void DrawObject(float elapsedTime) override;
	void InitializeObject() override;
	void HoldInput() override;
	void CreateTilesToEdit(std::string s);
	void zoomViewAt(sf::Vector2i pixel, sf::RenderWindow& window, float zoom);
};