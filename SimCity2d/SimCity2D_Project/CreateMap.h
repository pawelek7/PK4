#ifndef CreateMap_hpp
#define CreateMap_hpp

#include "Gui.h"
#include "MapTile.h"
#include "StateOfProgram.h"
#include "GameAssets.h"

#include <string>

enum class MouseEvents //what mause do
{ VOID = 0, SELECT = 1};

class CreateMap : public StateOfProgram
{
	std::shared_ptr<GameAssets> ptrGame = nullptr; //ptr to state and assets

	unsigned int sizeMap[4] = { 32, 64, 128, 256 }; //map sizes
	unsigned short sizeMapIterator = 0; //iterator of array - sizeMap
	const float zoomAmount { 1.1f }; //zoom screen value
	bool created = false; //if map grid is created
	
	MapTile map; //object of map
	Plate* plate; //object of 1x1 tile

	std::vector<char> nameMapV; //vector stores chars of map name
	std::string sizeSquare = ""; //size of map
	std::string nameMap = ""; //name of map

	//---GUI STUFF---//

	Gui::SelectTexture *selectTexture; 
	std::map<std::string, Gui::Button*> buttons;
	std::map<std::string, Gui::GameGui> guiSystem;
	MouseEvents mouseEvent = MouseEvents::VOID; //what mouse do

	//---SFML---//
	
	sf::Vector2f center;

	sf::View camera, guiView; //camera

	sf::Font font; //font
	sf::Text cursorText; //text drawed next to cursor
	sf::Text nameText; //map name text
	sf::Text sizeMapText; //size map text
	sf::Texture table; //texture of table with settings
	sf::Sprite table_rectangle; //sprite for table with settings
	sf::IntRect textureRect; //texture selector rectangle
	sf::RectangleShape selectorRect; //texture selector rectangle
	sf::Vector2i selectFROM = sf::Vector2i(0, 0), selectTO = sf::Vector2i(0, 0); //select areas of map
	sf::Vector2i oldMousePos = sf::Vector2i(0, 0), newMousePos = sf::Vector2i(0, 0); //mouse positions
	
public:
	CreateMap(std::shared_ptr<GameAssets> ptrGame);
	virtual ~CreateMap();

	void CreateTilesToEdit(const std::string & file_name, int how_length);
	void zoomViewAt(sf::Vector2i pixel, sf::RenderWindow& window, float zoom);

	void UpdateObject(float elapsedTime) override;
	void DrawObject(float elapsedTime) override;
	void InitializeObject() override;
	void HoldInput() override;

	void InitGui();
	void InitSelector();
	void InitButtons();
	void InitFonts();
	void DrawButtons();
};

#endif // !CreateMap_hpp