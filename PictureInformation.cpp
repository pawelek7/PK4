#include "PictureInformation.h"

#pragma region Constructors

PictureInformation::PictureInformation(ID buildingID)
{
	this->buildingID = buildingID;

	this->textureManager.LoadAsset("up_people", "Resources/Textures/up_people.png");
	this->textureManager.LoadAsset("goods_out", "Resources/Textures/goods_out.png");
	this->textureManager.LoadAsset("goods_in", "Resources/Textures/goods_in.png");
	this->textureManager.LoadAsset("sick", "Resources/Textures/sick.png");
	this->textureManager.LoadAsset("money", "Resources/Textures/money.png");
	this->textureManager.LoadAsset("energy_out", "Resources/Textures/energy_out.png");

	this->pictureInformationMap.insert(std::pair<PictureType, sf::Texture>(PictureType::PEOPLE_UP,
		this->textureManager.GetAsset("up_people")));
	this->pictureInformationMap.insert(std::pair<PictureType, sf::Texture>(PictureType::GOODS_IN,
		this->textureManager.GetAsset("goods_in")));
	this->pictureInformationMap.insert(std::pair<PictureType, sf::Texture>(PictureType::GOODS_OUT,
		this->textureManager.GetAsset("goods_out")));
	this->pictureInformationMap.insert(std::pair<PictureType, sf::Texture>(PictureType::SICK,
		this->textureManager.GetAsset("sick")));
	this->pictureInformationMap.insert(std::pair<PictureType, sf::Texture>(PictureType::MONEY,
		this->textureManager.GetAsset("money")));
	this->pictureInformationMap.insert(std::pair<PictureType, sf::Texture>(PictureType::ENERGY_OUT,
		this->textureManager.GetAsset("energy_out")));
}

#pragma endregion

#pragma region Class_Methods

void PictureInformation::InitializePictureInformation(PictureType pictureType)
{
	switch (pictureType)
	{
	case PictureType::PEOPLE_UP:
		this->pictureSprite.setTexture(this->pictureInformationMap.find(PictureType::PEOPLE_UP)->second);
		this->animationType = false;
		break;
	case PictureType::GOODS_IN:
		this->pictureSprite.setTexture(this->pictureInformationMap.find(PictureType::GOODS_IN)->second);
		this->animationType = false;
		break;
	case PictureType::GOODS_OUT:
		this->pictureSprite.setTexture(this->pictureInformationMap.find(PictureType::GOODS_OUT)->second);
		this->animationType = true;
		break;
	case PictureType::SICK:
		this->pictureSprite.setTexture(this->pictureInformationMap.find(PictureType::SICK)->second);
		this->animationType = true;
		break;
	case PictureType::MONEY:
		this->pictureSprite.setTexture(this->pictureInformationMap.find(PictureType::MONEY)->second);
		this->animationType = false;
		break;
	case PictureType::ENERGY_OUT:
		this->pictureSprite.setTexture(this->pictureInformationMap.find(PictureType::ENERGY_OUT)->second);
		this->animationType = true;
		break;
	}

	this->pictureSprite.setScale(0.5f, 0.5f);
}

void PictureInformation::UpdatePictureInformation(float elapsedTime)
{
	this->counterLife++;

	if (this->counterLife > this->lifeTime)
	{
		this->deletePicture = true;
		this->counterLife = 0;
	}

	if (this->animationType == false)
	{
		if (counterLife < 250)
		{
			this->pictureSprite.setColor(sf::Color(255, 255, 255, 255 - counterLife));
		}

		this->pictureSprite.setScale(0.5, 0.5);
		this->pictureRectangle.move(0, -(this->pictureSpeed * elapsedTime));
	}
	else
	{
		this->pictureRectangle.setScale(std::abs(std::sin(elapsedTime * counterLife/2)), std::abs(std::sin(elapsedTime * counterLife/2)));
		this->pictureSprite.setScale(this->pictureRectangle.getScale());

		if (this->counterLife > 100)
		{
			this->counterLife = 0;
		}
	}
	this->pictureSprite.setPosition(this->pictureRectangle.getPosition());
}

void PictureInformation::DrawPictureInformation(sf::RenderTarget *renderTarget)
{
	renderTarget->draw(pictureSprite);
}

void PictureInformation::ForceDelete()
{
	this->deletePicture = true;
}

#pragma endregion

#pragma region Setters

void PictureInformation::SetPictureInformationPosition(const sf::Vector2f & position)
{
	this->pictureRectangle.setPosition(position);
	this->pictureRectangle.setOrigin(32, 32);
	this->pictureSprite.setOrigin(32, 32);
}

void PictureInformation::SetHoldInformation(bool holdInformation)
{
	this->holdInformation = holdInformation;
}

#pragma endregion

#pragma region Getters

bool PictureInformation::GetIsDeleted() const
{
	return this->deletePicture;
}

ID PictureInformation::GetPictureID() const
{
	return this->buildingID;
}

bool PictureInformation::GetHoldInformation() const
{
	return this->holdInformation;
}

#pragma endregion