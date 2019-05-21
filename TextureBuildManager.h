#ifndef TextureBuildManager_hpp
#define TextureBuildManager_hpp

#include <random>
#include <chrono>
#include <utility>
#include <string>
#include <map>

#include "AssetManager.h"

enum class StructureType
{
	HOUSE = 0, SHOP = 1, FACTORY = 2
};

class TextureBuildManager
{
	int heightTexture = 0;
	int buildingHeight = 2;

	bool hasAnimation = false;

	std::string textureName = "unknown";

	AssetManager<sf::Texture> textureManager;
	sf::Texture texture;

	int RandomiseTextureVariant(int from, int to);

public:
	TextureBuildManager() = default;

	std::pair<bool, sf::Texture&> GetTexture(StructureType structureType, int levelBuilding = 0);
	sf::Texture & GetAppropriateTexture(const std::string & textureName);

	const std::string & GetTextureName() const;
	int GetTextureHeight() const;
	int GetBuildingProcessHeight() const;

	sf::Texture & GetNormalTexture();
	sf::Texture & GetBuildingTexture();
};

#endif // !TextureBuildManager_hpp