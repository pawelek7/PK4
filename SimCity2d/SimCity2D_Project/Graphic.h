#ifndef Graphic_hpp
#define Graphic_hpp

#include <SFML/Graphics.hpp> //SFML library

#include <string>

class Graphic
{

public: 
	Graphic();

	//this will be private in future!
	std::string title = "SimCity 2D";
	sf::VideoMode resolution = sf::VideoMode::getDesktopMode();
	bool fullScreen = false;
	bool verticalSync = false;
	unsigned frameRateLimit = 60;
	std::vector<sf::VideoMode> videoModes = sf::VideoMode::getFullscreenModes();
};

#endif // !Graphic_hpp
