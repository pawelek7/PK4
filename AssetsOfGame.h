#ifndef AssetsOfGame_hpp
#define AssetsOfGame_hpp

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "AssetManager.h"
#include "StateMachine.h"
#include "AudioManagement.h"

struct AssetsOfGame
{
	//---Load resources
	AssetManager<sf::Texture> textureManager;
	AssetManager<sf::Font> fontManager;
	AssetManager<sf::SoundBuffer> soundManager;

	//---Window holding
	sf::RenderWindow *window = nullptr;
	sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();
	sf::View camera, HUDcamera;

	//---Engine parts
	StateMachine stateMachine;
	AudioManagement *audioManagement = nullptr;

	//---Mouse
	sf::Vector2f mousePositionWindow;
	sf::Vector2i mousePositionMap;
};

#endif // !AssetsOfGame_hpp