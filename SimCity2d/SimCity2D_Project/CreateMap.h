#ifndef CreateMap_hpp
#define CreateMap_hpp

#include "Gui.h"
#include "MapTile.h"
#include "StateOfProgram.h"
#include "GameAssets.h"

#include <string>

enum class MouseEvents
{ VOID = 0, SELECT = 1};

class CreateMap : public StateOfProgram
{
	std::shared_ptr<GameAssets> ptrGame = nullptr;
	std::map<std::string, Gui::Button*> button;
	std::vector<char> nameMapV;
	MapTile map;
	Plate* plate;
	Gui::SelectTexture *selectTexture;
	std::string sizeSquare = "";
	std::string nameMap = "";
	const float zoomAmount { 1.1f };
	bool created = false;
	MouseEvents mouseEvent = MouseEvents::VOID;
	
	sf::View camera, guiView;

	sf::Font font;
	sf::Text cursorText;
	sf::Text nameText;
	sf::Texture table;
	sf::Sprite table_rectangle;
	sf::IntRect textureRect;
	sf::RectangleShape selectorRect;
	sf::Vector2i selectFROM = sf::Vector2i(0, 0), selectTO = sf::Vector2i(0, 0);
	sf::Vector2i oldMousePos = sf::Vector2i(0, 0), newMousePos = sf::Vector2i(0, 0);
	
public:
	CreateMap(std::shared_ptr<GameAssets> ptrGame);
	virtual ~CreateMap() = default;

	void CreateTilesToEdit(std::string s);
	void zoomViewAt(sf::Vector2i pixel, sf::RenderWindow& window, float zoom);

	void UpdateObject(float elapsedTime) override;
	void DrawObject(float elapsedTime) override;
	void InitializeObject() override;
	void HoldInput() override;
};

#endif // !CreateMap_hpp