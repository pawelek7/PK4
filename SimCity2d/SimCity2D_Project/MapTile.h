#ifndef MapTile_hpp
#define MapTile_hpp

#include <SFML/Graphics.hpp> //SFML library

#include "Plate.h"

#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

class MapTile
{
	friend class CreateMap;

private:
	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int selected = 0;
	unsigned int tileSize = 32;

	std::vector<Plate> _plate;
	std::vector<int> resources;
	std::vector<char> selectedTiles;
	
public:
	MapTile() = default;
	MapTile(unsigned int width, unsigned int height, std::map<std::string, Plate> & arratyOfTerritories);
	MapTile(const std::string & filename, unsigned int width, unsigned int height, std::map<std::string, Plate> & arratyOfTerritories);
	void LoadMap(const std::string & filename, unsigned int width, unsigned int height, std::map<std::string, Plate> & arratyOfTerritories);
	void SaveMap(const std::string & filename);
	void Select(sf::Vector2i from, sf::Vector2i to, std::vector<TypeOfTile> cant_affect);
	void Deselect();
	void Draw(sf::RenderWindow& window, float dt);

	void AddTile(int x, int y, const sf::IntRect & texture_rect);
	//void RemoveTile(int x, int y);
};

#endif // !MapTile_hpp