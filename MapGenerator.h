#ifndef MapGenerator_hpp
#define MapGenerator_hpp

#include <vector>

#include "SeedGenerator.h"
#include "SmallTile.h"
#include "PerlinNoise.h"

class MapGenerator
{
	SeedGenerator & seedRandomise;

	std::vector<double> generatedMap;
	std::vector<TileSpecialise> basicTileMap;

public:
	MapGenerator(SeedGenerator & seedRandomise);

	void GenerateMapBaseOnSeed(unsigned int n);

	inline std::vector<TileSpecialise> & GetBasicTileMap()
	{
		return this->basicTileMap;
	}
};

#endif // !MapGenerator_hpp