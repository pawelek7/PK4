#ifndef GameAssets_hpp
#define GameAssets_hpp

#include <SFML/Graphics.hpp> //SFML library
#include <SFML/Audio.hpp> //SFML library

#include "AssetManager.h"
#include "StateMachine.h"
#include "Graphic.h"
#include "Plate.h"
#include "Gui.h"
//#include "MapTile.h"

struct GameAssets
{
	//load from file
	AssetManager<sf::Texture> textureManager;
	AssetManager<sf::Font> fontManager;
	AssetManager<sf::SoundBuffer> soundManager;

	//window
	sf::RenderWindow window;
	sf::View cameraGame;

	//mouse
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2u mousePosGrid;

	//other
	StateMachine stateMachine;
	Graphic graphic;

	//containers
	std::map<std::string, Plate> tile_map;
	std::map<std::string, Gui::GameGuiBase> stylesGuis;
};

#endif // !GameAssets_hpp