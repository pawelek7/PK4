#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include "AnimatedTexture.h"
#include "StateOfProgram.h"

enum Region
{
	FIELD = 0,
	HOUSES = 1,
	OFFICES = 2,
	FACTORY = 3,
	ROAD = 4
};

class Territory
{
	AnimatedTexture animation;
	sf::Sprite sprite_texture;
	short type_of_building = 0;
	unsigned int regions[1];
	unsigned int value = 0;
	unsigned int inhabitants = 0;
	unsigned int populationUpgrade = 0;
	unsigned short buildingLevel = 0;
	unsigned int production = 0;
	unsigned int goods = 0;

public:
	Territory() = default;
	Territory(const unsigned int sizeOfTile, const unsigned int heightOfTile, sf::Texture & texture,
		const std::vector<Animation> & animation, const int typeOfRegion, const unsigned int value,
		const unsigned int populationUpgrade, const unsigned int buildingLevel);
	void UpdateObject(float elapsedTime);
	void DrawObject();
	void InitializeObject();

};