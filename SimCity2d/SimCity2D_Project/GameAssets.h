#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "AssetManager.h"
#include "StateMachine.h"
#include "Graphic.h"

struct GameAssets
{
	AssetManager<sf::Texture> textureManager;
	AssetManager<sf::Font> fontManager;
	AssetManager<sf::SoundBuffer> soundManager;

	sf::RenderWindow window;
	//sf::RenderWindow *ptrWindow;
	StateMachine stateMachine;

	Graphic graphic;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2u mousePosGrid;
};