#include "TextureBuildManager.h"

#pragma region Class_Methods

std::pair<bool, sf::Texture&> TextureBuildManager::GetTexture(StructureType structureType, int levelBuilding)
{
	std::string levelS = std::to_string(levelBuilding);
	int textureVariant = this->RandomiseTextureVariant(1, 3);
	std::string textureVariantS = std::to_string(textureVariant);

	if (structureType == StructureType::HOUSE)
	{
		this->textureManager.LoadAsset("house_lv" + levelS + "_v" + textureVariantS, "Resources/Textures/house_lv" + levelS + "_v" + textureVariantS + ".png");
		this->texture = this->textureManager.GetAsset("house_lv" + levelS + "_v" + textureVariantS);
		this->textureName = "house_lv" + levelS + "_v" + textureVariantS;
	}
	else if (structureType == StructureType::FACTORY)
	{
		this->textureManager.LoadAsset("factory_lv" + levelS + "_v" + textureVariantS, "Resources/Textures/factory_lv" + levelS + "_v" + textureVariantS + ".png");
		this->texture = this->textureManager.GetAsset("factory_lv" + levelS + "_v" + textureVariantS);
		this->textureName = "factory_lv" + levelS + "_v" + textureVariantS;
	}
	else if (structureType == StructureType::SHOP)
	{
		this->textureManager.LoadAsset("shop_lv" + levelS + "_v" + textureVariantS, "Resources/Textures/shop_lv" + levelS + "_v" + textureVariantS + ".png");
		this->texture = this->textureManager.GetAsset("shop_lv" + levelS + "_v" + textureVariantS);
		this->textureName = "shop_lv" + levelS + "_v" + textureVariantS;
	}

	if (this->texture.getSize().x > 64)
	{
		hasAnimation = true;
	}

	if (this->texture.getSize().y <= 32)
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

	return std::pair<bool, sf::Texture&>(hasAnimation, texture);
}

int TextureBuildManager::RandomiseTextureVariant(int from, int to)
{
	std::default_random_engine engine;
	std::uniform_real_distribution<double> distribution(from, to);

	auto czas = std::chrono::system_clock::now();
	auto interwal = czas.time_since_epoch();
	engine.seed(interwal.count());

	return static_cast<int>(distribution(engine));
}

sf::Texture & TextureBuildManager::GetAppropriateTexture(const std::string & textureName)
{
	this->textureManager.LoadAsset(textureName, "Resources/Textures/" + textureName + ".png");

	return textureManager.GetAsset(textureName);
}

#pragma endregion

#pragma region Getters

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