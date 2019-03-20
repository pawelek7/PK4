#ifndef MapTile_hpp
#define MapTile_hpp

#include <SFML/Graphics.hpp> //SFML library
#include "GameAssets.h"
#include "Plate.h"

#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

#include <iostream> //for test


class MapTile
{
	friend class CreateMap;
	std::shared_ptr<GameAssets> ptrGame = nullptr;
	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int selected = 0; //number of selected tiles
	unsigned int tileSize = 32;
	unsigned int size_of_map = 0;

	int fromX = 0;
	int toX = 0;
	int fromY = 0;
	int toY = 0;

	std::vector<Plate> _plate;
	std::vector<int> resources;
	std::vector<char> selectedTiles; //store selected 1x1 tiles

	sf::Vector2f center;
	
public:
	MapTile() = default;
	MapTile(unsigned int size_of_map, const std::string & filename, std::map<std::string, Plate> & arratyOfTerritories, std::shared_ptr<GameAssets> ptrGame);
	MapTile(const std::string & filename, unsigned int width, unsigned int height, std::map<std::string, Plate> & arratyOfTerritories, std::shared_ptr<GameAssets> ptrGame);

	void LoadMap(const std::string & filename, unsigned int width, unsigned int height, std::map<std::string, Plate> & arratyOfTerritories);
	void SaveMap(const std::string & filename);
	void Select(sf::Vector2i from, sf::Vector2i to, std::vector<TypeOfTile> cant_affect);
	void Deselect();
	void Draw(sf::RenderWindow& window, float dt);

	void AddTile(int x, int y, const sf::IntRect & texture_rect);
	//void RemoveTile(int x, int y);

};

#endif // !MapTile_hpp