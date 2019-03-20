#include "MapTile.h"

MapTile::MapTile(unsigned int size_of_map, const std::string & filename, std::map<std::string, Plate> & arrayOfTerritories, std::shared_ptr<GameAssets> ptrGame)
	:ptrGame(ptrGame)
{
	this->width = size_of_map;
	this->height = size_of_map;
	this->size_of_map = size_of_map;

	std::ofstream outputFile("Resources/Maps/" + filename + ".dat", std::ios::binary);
	for (int i = 0; i < width * height; i++)
	{
		outputFile.write((char*)"1", sizeof(int));
		this->selectedTiles.push_back(0);
		this->_plate.push_back(arrayOfTerritories.at("cross"));
		Plate& plate = this->_plate.back();
	}
	outputFile.close();

	center = sf::Vector2f(this->width, this->height*0.5);
	center *= float(this->tileSize);
}

MapTile::MapTile(const std::string & filename, unsigned int width, unsigned int height, std::map<std::string, Plate> & arratyOfTerritories, std::shared_ptr<GameAssets> ptrGame)
	:ptrGame(ptrGame)
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
		this->selectedTiles.push_back(0);
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
	fromX = (this->ptrGame->mousePosGrid.x + this->ptrGame->mousePosGrid.y - tileSize * 2)/tileSize ;
	toX = (this->ptrGame->mousePosGrid.x + this->ptrGame->mousePosGrid.y + tileSize * 2)/tileSize ;

	fromY = (this->ptrGame->mousePosGrid.y - this->ptrGame->mousePosGrid.x - tileSize * 2)/tileSize ;
	toY = (this->ptrGame->mousePosGrid.y - this->ptrGame->mousePosGrid.x + tileSize * 2)/tileSize ;
	
	if (fromX < 0)
	{
		fromX = 0;
	}
	else if (fromX >= size_of_map)
	{
		fromX = size_of_map - 1;
	}
	if (fromY < 0)
	{
		fromY = 0;
	}
	else if (fromY >= size_of_map)
	{
		fromY = size_of_map - 1;
	}
	if (toX < 0)
	{
		toX = 0;
	}
	else if (toX >= size_of_map)
	{
		toX = size_of_map - 1;
	}
	if (toY < 0)
	{
		toY = 0;
	}
	else if (toY >= size_of_map)
	{
		toY = size_of_map - 1;
	}

	for (int y=fromY; y < this->toY; y++)
	{
		for (int x = fromX; x < this->toX; x++)
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
	std::cout << selected << std::endl;
}

void MapTile::Deselect()
{
	for (auto & i : this->selectedTiles)
	{
		i = 0;
	}
	this->selected = 0;
}