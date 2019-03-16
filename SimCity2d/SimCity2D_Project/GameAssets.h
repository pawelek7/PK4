#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "AssetManager.h"
#include "StateMachine.h"
#include "Graphic.h"
#include "Plate.h"
#include "MapTile.h"

struct GameAssets
{
	//load from file
	AssetManager<sf::Texture> textureManager;
	AssetManager<sf::Font> fontManager;
	AssetManager<sf::SoundBuffer> soundManager;

	//window
	sf::RenderWindow window;

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
};