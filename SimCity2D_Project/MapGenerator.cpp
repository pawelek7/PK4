#include "MapGenerator.h"

#pragma region Constructors

MapGenerator::MapGenerator(SeedGenerator & seedRandomise) : seedRandomise(seedRandomise)
{
	//nothing
}

#pragma endregion

#pragma region ClassMethods

void MapGenerator::GenerateMapBaseOnSeed(unsigned int n)
{
	const PerlinNoise perlin(seedRandomise.GetSeed());

	double delta = 1.0f / n;

	generatedMap.resize(n*n);
	basicTileMap.resize(n*n);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			this->generatedMap[i*n + j] = std::move(perlin.octaveNoise0_1(i * delta, j * delta, 5));
		}
	}

	double minElement = *std::min_element(generatedMap.begin(), generatedMap.end());
	double maxElement = *std::max_element(generatedMap.begin(), generatedMap.end());

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			double tmp = (generatedMap[i*n + j] - minElement) / (maxElement - minElement);
			this->generatedMap[i*n + j] = tmp;
		}
	}

	double waterChance = 0.25f;
	double treeChance = 0.10f;
	double rockChance = 0.70f;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			basicTileMap[i*n + j] = SmallTile::TileSpecialise::FLOOR;

			if (generatedMap[i*n + j] < treeChance)
			{
				basicTileMap[i*n + j] = SmallTile::TileSpecialise::ROCK;
			}
			else if (generatedMap[i*n + j] < waterChance)
			{
				basicTileMap[i*n + j] = SmallTile::TileSpecialise::WATER;
			}
			else if (generatedMap[i*n + j] > rockChance)
			{
				basicTileMap[i*n + j] = SmallTile::TileSpecialise::TREE;
			}
		}
	}
}

#pragma endregion