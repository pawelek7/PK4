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
	std::vector<SmallTile::TileSpecialise> basicTileMap;

public:
	MapGenerator() = default;
	MapGenerator(SeedGenerator & seedRandomise);
	virtual ~MapGenerator() = default;

	void GenerateMapBaseOnSeed(unsigned int n);

	inline std::vector<SmallTile::TileSpecialise> & GetBasicTileMap()
	{
		return this->basicTileMap;
	}
};

#endif // !MapGenerator_hpp