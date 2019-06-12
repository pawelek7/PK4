#ifndef TextureBuildManager_hpp
#define TextureBuildManager_hpp

#include <utility>
#include <string>
#include <map>

#include "AssetManager.h"
#include "RandomEngine.h"

#define RANDOM_FROM 1
#define RANDOM_TO 3

/*
A class that supports structure's textures.
Read from file, set heights.

@author
Pawel Salicki
*/

class TextureBuildManager
{
public:
	enum class TextureType
	{
		HOUSE = 0, SHOP = 1, FACTORY = 2
	};

private:
	int heightTexture = 0; //height of structure
	int buildingHeight = 2; //height of "building" texture
	bool hasAnimation = false; //is texture can be animated
	std::string textureName = "unknown"; //name of texture

	RandomEngine randomEngine; //engine of random variables

	AssetManager<sf::Texture> textureManager; //manager of reading textures from file
	sf::Texture texture; //structure texture

public:
	TextureBuildManager() = default;
	virtual ~TextureBuildManager() = default;

	std::pair<bool, sf::Texture&> GetTexture(TextureType textureType, int levelBuilding = 0); //get random texture variant of building
	sf::Texture & GetAppropriateTexture(const std::string & textureName); //get texture demepding of her name

	//getters
	const std::string & GetTextureName() const;
	int GetTextureHeight() const;
	int GetBuildingProcessHeight() const;

	sf::Texture & GetNormalTexture();
	sf::Texture & GetBuildingTexture();
};

#endif // !TextureBuildManager_hpp