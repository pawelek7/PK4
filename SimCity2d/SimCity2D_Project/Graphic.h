#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Graphic
{
public: //tmp all public for tests
	std::string title = "SimCity 2D";
	sf::VideoMode resolution = sf::VideoMode::getDesktopMode();
	bool fullScreen = false;
	bool verticalSync = false;
	unsigned frameRateLimit = 60;
	std::vector<sf::VideoMode> videoModes = sf::VideoMode::getFullscreenModes();


	Graphic();
};