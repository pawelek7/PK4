#include "TextureBuildManager.h"

#pragma region Class_Methods

#pragma region Description of the method
/*
A method that randomise texture of building
and load it from file.

method parameters:
____________________
textureType - type of texture (House, Hospital or Factory)
levelBuilding - level of structure

the return value:
____________________
pair<bool, sf::Texture> - is animated, texture

@author
Pawel Salicki
*/
#pragma endregion

std::pair<bool, sf::Texture&> TextureBuildManager::GetTexture(TextureType textureType, int levelBuilding)
{
	std::string levelS = std::to_string(levelBuilding); //level of buildign as string

	int textureVariant = (int)this->randomEngine.RandomiseEvent(RANDOM_FROM, RANDOM_TO); //randomise texture variant from two available
	std::string textureVariantS = std::to_string(textureVariant); //set string of texture variant

	switch (textureType) //load texxture from file depending on type od structure (if house, factory or shop)
	{
	case TextureType::HOUSE:
		this->textureManager.LoadAsset("house_lv" + levelS + "_v" + textureVariantS, "Resources/Textures/house_lv" + levelS + "_v" + textureVariantS + ".png");
		this->texture = this->textureManager.GetAsset("house_lv" + levelS + "_v" + textureVariantS);
		this->textureName = "house_lv" + levelS + "_v" + textureVariantS;
		break;
	case TextureType::SHOP:
		this->textureManager.LoadAsset("shop_lv" + levelS + "_v" + textureVariantS, "Resources/Textures/shop_lv" + levelS + "_v" + textureVariantS + ".png");
		this->texture = this->textureManager.GetAsset("shop_lv" + levelS + "_v" + textureVariantS);
		this->textureName = "shop_lv" + levelS + "_v" + textureVariantS;
		break;
	case TextureType::FACTORY:
		this->textureManager.LoadAsset("factory_lv" + levelS + "_v" + textureVariantS, "Resources/Textures/factory_lv" + levelS + "_v" + textureVariantS + ".png");
		this->texture = this->textureManager.GetAsset("factory_lv" + levelS + "_v" + textureVariantS);
		this->textureName = "factory_lv" + levelS + "_v" + textureVariantS;
		break;
	}

	if (this->texture.getSize().x > 64) //check if texture can be animated
	{
		hasAnimation = true;
	}

	if (this->texture.getSize().y <= 32) //get size of texture
	{
		this->heightTexture = 1;
	}
	else if (this->texture.getSize().y <= 64)
	{
		this->heightTexture = 2;
	}
	else if (this->texture.getSize().y <= 96)
	{
		this->heightTexture = 3;
	}
	else
	{
		this->heightTexture = 4;
	}

	return std::pair<bool, sf::Texture&>(this->hasAnimation, this->texture);
}

#pragma region Description of the method
/*
A method that read texture from file
depending on her name.

method parameters:
____________________
textureType - type of texture (House, Hospital or Factory)
levelBuilding - level of structure

the return value:
____________________
pair<bool, sf::Texture> - is animated, texture

@author
Pawel Salicki
*/
#pragma endregion

sf::Texture & TextureBuildManager::GetAppropriateTexture(const std::string & textureName)
{
	this->textureManager.LoadAsset(textureName, "Resources/Textures/" + textureName + ".png"); //read texture from file

	return textureManager.GetAsset(textureName);
}

#pragma endregion

#pragma region Getters
//getters

sf::Texture & TextureBuildManager::GetBuildingTexture() 
{
	this->textureManager.LoadAsset("building", "Resources/Textures/building.png");
	return this->textureManager.GetAsset("building");
}

sf::Texture & TextureBuildManager::GetNormalTexture()
{
	return this->texture;
}

const std::string & TextureBuildManager::GetTextureName() const
{
	return this->textureName;
}

int TextureBuildManager::GetTextureHeight() const
{
	return this->heightTexture;
}

int TextureBuildManager::GetBuildingProcessHeight() const
{
	return this->buildingHeight;
}

#pragma endregion