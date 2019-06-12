#include "HudLeft.h"

#pragma region Constructors

HudLeft::HudLeft(float x, float y, float width, float height, float windowSizeX, float windowSizeY,
	std::shared_ptr<AssetsOfGame> ptrGame, unsigned int id)
{
	this->ptrGame = ptrGame;
	this->ptrGame->textureManager.LoadAsset("icon_city_1", "Resources/Textures/icon_city_1.png");
	this->ptrGame->textureManager.LoadAsset("icon_city_2", "Resources/Textures/icon_city_2.png");
	this->ptrGame->textureManager.LoadAsset("icon_factory_1", "Resources/Textures/icon_factory_1.png");
	this->ptrGame->textureManager.LoadAsset("icon_factory_2", "Resources/Textures/icon_factory_2.png");
	this->ptrGame->textureManager.LoadAsset("icon_home_1", "Resources/Textures/icon_home_1.png");
	this->ptrGame->textureManager.LoadAsset("icon_home_2", "Resources/Textures/icon_home_2.png");
	this->ptrGame->textureManager.LoadAsset("icon_power_1", "Resources/Textures/icon_power_1.png");
	this->ptrGame->textureManager.LoadAsset("icon_power_2", "Resources/Textures/icon_power_2.png");
	this->ptrGame->textureManager.LoadAsset("icon_road_1", "Resources/Textures/icon_road_1.png");
	this->ptrGame->textureManager.LoadAsset("icon_road_2", "Resources/Textures/icon_road_2.png");
	this->ptrGame->textureManager.LoadAsset("icon_water_1", "Resources/Textures/icon_water_1.png");
	this->ptrGame->textureManager.LoadAsset("icon_water_2", "Resources/Textures/icon_water_2.png");
	this->ptrGame->textureManager.LoadAsset("icon_destroy_1", "Resources/Textures/icon_destroy_1.png");
	this->ptrGame->textureManager.LoadAsset("icon_destroy_2", "Resources/Textures/icon_destroy_2.png");
	this->ptrGame->textureManager.LoadAsset("icon_hospital_1", "Resources/Textures/icon_hospital_1.png");
	this->ptrGame->textureManager.LoadAsset("icon_hospital_2", "Resources/Textures/icon_hospital_2.png");
	this->ptrGame->textureManager.LoadAsset("icon_taxes_1", "Resources/Textures/icon_taxes_1.png");
	this->ptrGame->textureManager.LoadAsset("icon_taxes_2", "Resources/Textures/icon_taxes_2.png");
	this->ptrGame->textureManager.LoadAsset("icon_fire_1", "Resources/Textures/icon_fire_1.png");
	this->ptrGame->textureManager.LoadAsset("icon_fire_2", "Resources/Textures/icon_fire_2.png");
	this->ptrGame->textureManager.LoadAsset("icon_police_1", "Resources/Textures/icon_police_1.png");
	this->ptrGame->textureManager.LoadAsset("icon_police_2", "Resources/Textures/icon_police_2.png");
	this->ptrGame->textureManager.LoadAsset("icon_tree_1", "Resources/Textures/icon_tree_1.png");
	this->ptrGame->textureManager.LoadAsset("icon_tree_2", "Resources/Textures/icon_tree_2.png");
	this->ptrGame->textureManager.LoadAsset("icon_statue_1", "Resources/Textures/icon_statue_1.png");
	this->ptrGame->textureManager.LoadAsset("icon_statue_2", "Resources/Textures/icon_statue_2.png");
	this->ptrGame->textureManager.LoadAsset("HUD_2", "Resources/Textures/HUD_2.png");

	buttonRectangleMap[ButtonIDs::HOMES_ACTIVE].setTexture(&this->ptrGame->textureManager.GetAsset("icon_home_1"));
	buttonRectangleMap[ButtonIDs::HOMES_HOVER].setTexture(&this->ptrGame->textureManager.GetAsset("icon_home_2"));
	buttonRectangleMap[ButtonIDs::FACTORY_ACTIVE].setTexture(&this->ptrGame->textureManager.GetAsset("icon_factory_1"));
	buttonRectangleMap[ButtonIDs::FACTORY_HOVER].setTexture(&this->ptrGame->textureManager.GetAsset("icon_factory_2"));
	buttonRectangleMap[ButtonIDs::SHOPS_ACTIVE].setTexture(&this->ptrGame->textureManager.GetAsset("icon_city_1"));
	buttonRectangleMap[ButtonIDs::SHOPS_HOVER].setTexture(&this->ptrGame->textureManager.GetAsset("icon_city_2"));
	buttonRectangleMap[ButtonIDs::POWER_ACTIVE].setTexture(&this->ptrGame->textureManager.GetAsset("icon_power_1"));
	buttonRectangleMap[ButtonIDs::POWER_HOVER].setTexture(&this->ptrGame->textureManager.GetAsset("icon_power_2"));
	buttonRectangleMap[ButtonIDs::ROAD_ACTIVE].setTexture(&this->ptrGame->textureManager.GetAsset("icon_road_1"));
	buttonRectangleMap[ButtonIDs::ROAD_HOVER].setTexture(&this->ptrGame->textureManager.GetAsset("icon_road_2"));
	buttonRectangleMap[ButtonIDs::WATER_ACTIVE].setTexture(&this->ptrGame->textureManager.GetAsset("icon_water_1"));
	buttonRectangleMap[ButtonIDs::WATER_HOVER].setTexture(&this->ptrGame->textureManager.GetAsset("icon_water_2"));
	buttonRectangleMap[ButtonIDs::DESTROY_ACTIVE].setTexture(&this->ptrGame->textureManager.GetAsset("icon_destroy_1"));
	buttonRectangleMap[ButtonIDs::DESTROY_HOVER].setTexture(&this->ptrGame->textureManager.GetAsset("icon_destroy_2"));
	buttonRectangleMap[ButtonIDs::HOSPITAL_ACTIVE].setTexture(&this->ptrGame->textureManager.GetAsset("icon_hospital_1"));
	buttonRectangleMap[ButtonIDs::HOSPITAL_HOVER].setTexture(&this->ptrGame->textureManager.GetAsset("icon_hospital_2"));
	buttonRectangleMap[ButtonIDs::TAXES_ACTIVE].setTexture(&this->ptrGame->textureManager.GetAsset("icon_taxes_1"));
	buttonRectangleMap[ButtonIDs::TAXES_HOVER].setTexture(&this->ptrGame->textureManager.GetAsset("icon_taxes_2"));
	buttonRectangleMap[ButtonIDs::FIRE_ACTIVE].setTexture(&this->ptrGame->textureManager.GetAsset("icon_fire_1"));
	buttonRectangleMap[ButtonIDs::FIRE_HOVER].setTexture(&this->ptrGame->textureManager.GetAsset("icon_fire_2"));
	buttonRectangleMap[ButtonIDs::POLICE_ACTIVE].setTexture(&this->ptrGame->textureManager.GetAsset("icon_police_1"));
	buttonRectangleMap[ButtonIDs::POLICE_HOVER].setTexture(&this->ptrGame->textureManager.GetAsset("icon_police_2"));
	buttonRectangleMap[ButtonIDs::TREE_ACTIVE].setTexture(&this->ptrGame->textureManager.GetAsset("icon_tree_1"));
	buttonRectangleMap[ButtonIDs::TREE_HOVER].setTexture(&this->ptrGame->textureManager.GetAsset("icon_tree_2"));
	buttonRectangleMap[ButtonIDs::STATUE_ACTIVE].setTexture(&this->ptrGame->textureManager.GetAsset("icon_statue_1"));
	buttonRectangleMap[ButtonIDs::STATUE_HOVER].setTexture(&this->ptrGame->textureManager.GetAsset("icon_statue_2"));

	int tmp = 1;
	int tmp2 = 2;
	for (int i = 0; i < buttonRectangleMap.size() / 2; i++)
	{
		this->pictureButtons.push_back(
			new PictureButton(p2pX(0.2f, this->ptrGame->videoMode) + ((i % 2) *calcCharSize(this->ptrGame->videoMode, 30)) + x, p2pY(8.75f, this->ptrGame->videoMode) + ((i / 2) * calcCharSize(this->ptrGame->videoMode, 30)) + y + p2pY(5.0f, this->ptrGame->videoMode), calcCharSize(this->ptrGame->videoMode, 30), calcCharSize(this->ptrGame->videoMode, 30), 0,
				buttonRectangleMap[buttonID1 = (ButtonIDs)tmp].getTexture(), buttonRectangleMap[buttonID2 = (ButtonIDs)tmp2].getTexture(),
				ptrGame, tmp));

		tmp += 2;
		tmp2 += 2;
	}

	this->id = id;

	this->iconsHUD.setSize(sf::Vector2f(static_cast<float>(windowSizeX),
		static_cast<float>(windowSizeY)));
	this->iconsHUD.setTexture(&this->ptrGame->textureManager.GetAsset("HUD_2"));
	this->iconsHUD.setPosition(sf::Vector2f(x, y));
}

HudLeft::~HudLeft()
{
	for (size_t i = 0; i < this->pictureButtons.size(); i++)
	{
		if (this->pictureButtons[i] != nullptr)
		{
			delete this->pictureButtons[i];
			this->pictureButtons[i] = nullptr;
		}
	}
}

#pragma endregion

#pragma region Class_Methods

void HudLeft::UpdateHUDleft(const sf::Vector2i& mousePosition, const float & elapsedTime)
{
	this->mouseOnHud = false;

	for (auto & i : this->pictureButtons)
	{
		i->UpdateButton((sf::Vector2f)mousePosition, elapsedTime);

		if (i->GetPressed())
		{
			id = i->GetID();
		}

		if (i->GetMouseOnButton())
		{
			this->mouseOnHud = true;
		}
	}
}

void HudLeft::DrawHUDleft(sf::RenderTarget *renderTarget)
{
	this->ptrGame->window->draw(iconsHUD);
	for (auto & i : this->pictureButtons)
	{
		i->DrawButton(renderTarget);
	}
}

#pragma endregion

#pragma region Setters

void HudLeft::SetString(const sf::String & string)
{
	if (string != text.getString())
	{
		text.setString(string);
	}
}

#pragma endregion

#pragma region Getters

const unsigned short & HudLeft::getActiveElementId() const
{
	return this->id;
}

const sf::String & HudLeft::GetString() const
{
	return this->text.getString();
}

bool HudLeft::GetMouseOnHud()
{
	return this->mouseOnHud;
}

std::string  HudLeft::GetButtonOption1()
{
	switch (ButtonIDs(id))
	{
	case ButtonIDs::HOMES_ACTIVE:
		return "Build Houses";
	case ButtonIDs::DESTROY_ACTIVE:
		return "Destroy terrain";
	case ButtonIDs::SHOPS_ACTIVE:
		return "Build Shops";
	case ButtonIDs::FACTORY_ACTIVE:
		return "Build Factory";
	case ButtonIDs::ROAD_ACTIVE:
		return "Build roads";
	case ButtonIDs::POWER_ACTIVE:
		return "Build Power Lines";
	case ButtonIDs::TAXES_ACTIVE:
		return "Change Taxes";
	case ButtonIDs::FIRE_ACTIVE:
		return "Build FireStation";
	case ButtonIDs::POLICE_ACTIVE:
		return "Build PoliceStation";
	case ButtonIDs::TREE_ACTIVE:
		return "Plant Tree";
	case ButtonIDs::STATUE_ACTIVE:
		return "Set Statue";
	default:
		return "<Nothing>";
	}
}

std::string HudLeft::GetButtonOption2()
{
	switch (ButtonIDs(id))
	{
	case ButtonIDs::HOMES_ACTIVE:
		return "<Nothing>";
	case ButtonIDs::DESTROY_ACTIVE:
		return "<Nothing>";
	case ButtonIDs::SHOPS_ACTIVE:
		return "<Nothing>";
	case ButtonIDs::FACTORY_ACTIVE:
		return "<Nothing>";
	case ButtonIDs::ROAD_ACTIVE:
		return "<Nothing>";
	case ButtonIDs::POWER_ACTIVE:
		return "Build PowerStation";
	case ButtonIDs::WATER_ACTIVE:
		return "<Nothing>";
	case ButtonIDs::HOSPITAL_ACTIVE:
		return "Build Hospital";
	case ButtonIDs::TREE_ACTIVE:
		return "Plant Tree and Grass";
	default:
		return "<Nothing>";
	}
}

#pragma endregion