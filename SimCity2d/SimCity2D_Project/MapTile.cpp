#include "MapTile.h"

MapTile::MapTile(unsigned int width, unsigned int height, std::map<std::string, Plate> & arrayOfTerritories)
{
	std::ifstream inputFile;

	this->width = width;
	this->height = height;

	inputFile.open("city_map.dat", std::ios::in | std::ios::binary);
	for (int i = 0; i < width * height; i++)
	{
		this->_plate.push_back(arrayOfTerritories.at("cross"));
		Plate& plate = this->_plate.back();
	}
	inputFile.close();
}

MapTile::MapTile(const std::string & filename, unsigned int width, unsigned int height, std::map<std::string, Plate> & arratyOfTerritories)
{
	LoadMap(filename, width, height, arratyOfTerritories);
}

void MapTile::LoadMap(const std::string & filename, unsigned int width, unsigned int height, std::map<std::string, Plate> & arratyOfTerritories)
{
	std::ifstream inputFile;
	inputFile.open(filename, std::ios::in | std::ios::binary);

	this->width = width;
	this->height = height;

	for (int i = 0; i < width * height; i++)
	{
		this->resources.push_back(255);

		TypeOfTile typeofTile;
		inputFile.read((char*)&typeofTile, sizeof(int));
		switch (typeofTile)
		{
		case TypeOfTile::NOTHING:
		case TypeOfTile::DIRT:
			this->_plate.push_back(arratyOfTerritories.at("dirt"));
			break;
		default: //TypeOfTile::DIRT:
			this->_plate.push_back(arratyOfTerritories.at("dirt"));
			break;
		}
		Plate& plate = this->_plate.back();
		//....
	}
	inputFile.close();

}

void MapTile::SaveMap(const std::string & filename)
{
	std::ofstream outputFile;
	outputFile.open(filename, std::ios::out | std::ios::binary);

	for (auto i : this->_plate)
	{
		outputFile.write((char*)&i._typeOfTile, sizeof(int));
		//...
	}
	outputFile.close();

}

void MapTile::Draw(sf::RenderWindow& window, float dt)
{
	for (int y = 0; y < this->height; ++y)
	{
		for (int x = 0; x < this->width; ++x)
		{
			sf::Vector2f pos;
			pos.x = (x - y) * this->tileSize + this->width * this->tileSize;
			pos.y = (x + y) * this->tileSize * 0.5;
			this->_plate[y*this->width + x]._sprite.setPosition(pos);

			this->_plate[y*this->width + x].Draw(window, dt);







			if (this->selectedTiles[y*this->width + x])
				this->_plate[y*this->width + x]._sprite.setColor(sf::Color(0x7d, 0x7d, 0x7d));
			else
				this->_plate[y*this->width + x]._sprite.setColor(sf::Color(0xff, 0xff, 0xff));

			/* Draw the tile */
			this->_plate[y*this->width + x].Draw(window, dt);
		}
	}


}

void MapTile::AddTile(int x, int y, const sf::IntRect & texture_rect)
{

}

void  MapTile::Select(sf::Vector2i from, sf::Vector2i to, std::vector<TypeOfTile> cant_affect)
{
	if (to.y < from.y)
	{
		std::swap(from.y, to.y);
	}
	if (to.x < from.x)
	{
		std::swap(from.x, to.x);
	}

	if (to.x >= this->width)
	{
		to.x = this->width - 1;
	}
	else if (to.x < 0)
	{
		to.x = 0;
	}
		
	if (to.y >= this->height)
	{
		to.y = this->height - 1;
	}
	else if (to.y < 0)
	{
		to.y = 0;
	}
	
	if (from.x >= this->width)
	{
		from.x = this->width - 1;
	}
	else if (from.x < 0)
	{
		from.x = 0;
	}
		
	if (from.y >= this->height)
	{
		from.y = this->height - 1;
	}
	else if (from.y < 0)
	{
		from.y = 0;
	}

	for (int y = from.y; y <= to.y; ++y)
	{
		for (int x = from.x; x <= to.x; ++x)
		{
			this->selectedTiles[y*this->width + x] = 1;
			++this->selected;
			for (auto type : cant_affect)
			{
				if (this->_plate[y*this->width + x]._typeOfTile == type)
				{
					this->selectedTiles[y*this->width + x] = 2;
					--this->selected;
					break;
				}
			}
		}
	}
}

void MapTile::Deselect()
{
	for (auto & i : this->selectedTiles)
	{
		i = 0;
	}
	this->selected = 0;
}