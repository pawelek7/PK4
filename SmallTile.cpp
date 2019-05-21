#include "SmallTile.h"

#pragma region Constructors

SmallTile::SmallTile(const unsigned int height,
	const sf::Texture & texture, const TypeOfTile typeOfTile, const TileSpecialise tileSpecialise, const std::vector<Frames> & frames)
	:AnimationSprite(frames)
{
	this->texture = texture;
	this->height = height;
	this->tileSpecialise = tileSpecialise;
	this->typeOfTile = typeOfTile;
	this->sprite.setTexture(texture);
	this->sprite.setOrigin(sf::Vector2f(0.0f, TILE_SIZE*(height - 1)));
	
	this->frameSize = sf::IntRect(0, 0, TILE_SIZE * 2, TILE_SIZE*height);
	this->UpdateAnimation(0.0f);

	tileData.level = 0;
	tileData.population = 0;
	tileData.tileSpecialise = tileSpecialise;
	tileData.texture_name = "unknown";
	tileData.height = 1;
}

SmallTile::~SmallTile()
{

}

#pragma endregion

#pragma region Class_Methods

std::unique_ptr<SmallTile> SmallTile::clone() const
{
	return std::make_unique<SmallTile>(height, texture, typeOfTile, tileSpecialise, frames);
}

void SmallTile::UpdateInformation()
{
	//...
}

bool SmallTile::SpriteClicked(const sf::Sprite & sprite, const sf::Image& image, const sf::Vector2f& position)
{
	if (sprite.getGlobalBounds().contains(position))
	{
		return true;
	}
	return false;
}

void SmallTile::UpdateHeight(int height)
{
	this->height = height;
}

void SmallTile::Draw(sf::RenderWindow & window, float elapsedTime, sf::Shader *shader, const sf::Vector2f & camera_position)
{
	if (tileSpecialise == TileSpecialise::WATER || this->isAnimation == true)
	{
		this->UpdateAnimation(elapsedTime);
		this->sprite.setTextureRect(currentSection);
	}

	if (selectionProcess == SelectionProcess::SELECTED)
	{
		sprite.setColor(sf::Color(135, 206, 250));
	}
	else
	{
		sprite.setColor(sf::Color(0xff, 0xff, 0xff));
	}

	this->ChangeFrame(0);
	this->UpdateAnimation(elapsedTime);

	if (shader)
	{
		if(this->position.x )
		shader->setUniform("hasTexture", true);
		shader->setUniform("light", camera_position);
		window.draw(this->sprite, shader);
	}
	else
	{
		window.draw(this->sprite);
	}
}

bool SmallTile::Interaction(const sf::Vector2f& position)
{
	return SpriteClicked(sprite, *image, position);
}

#pragma endregion

#pragma region Setters

TileSpecialise SmallTile::SetStringToTileSpecialise(const std::string & tileSpecialise)
{
	if (tileSpecialise == "FACTORY")
	{
		return TileSpecialise::FACTORY;
	}
	else if (tileSpecialise == "FLOOR")
	{
		return TileSpecialise::FLOOR;
	}
	else if (tileSpecialise == "HIGH_VOLTAGE_LINES")
	{
		return TileSpecialise::HIGH_VOLTAGE_LINES;
	}
	else if (tileSpecialise == "HOSPITAL")
	{
		return TileSpecialise::HOSPITAL;
	}
	else if(tileSpecialise == "HOUSE")
	{
		return TileSpecialise::HOUSE;
	}
	else if (tileSpecialise == "POWER_HOUSE")
	{
		return TileSpecialise::POWER_HOUSE;
	}
	else if (tileSpecialise == "ROAD")
	{
		return TileSpecialise::ROAD;
	}
	else if (tileSpecialise == "ROCK")
	{
		return TileSpecialise::ROCK;
	}
	else if (tileSpecialise == "SHOP")
	{
		return TileSpecialise::SHOP;
	}
	else if (tileSpecialise == "SPECTRUM_PLATE")
	{
		return TileSpecialise::SPECTRUM_PLATE;
	}
	else if (tileSpecialise == "TREE")
	{
		return TileSpecialise::TREE;
	}
	else if (tileSpecialise == "VOID")
	{
		return TileSpecialise::VOID;
	}
	else if (tileSpecialise == "WATER")
	{
		return TileSpecialise::WATER;
	}
	else if (tileSpecialise == "FIRE_STATION")
	{
		return TileSpecialise::FIRE_BRIGADE;
	}
	else
	{
		return TileSpecialise::VOID;
	}
}

std::string SmallTile::SetTileSpecialiseToString(TileSpecialise tileSpecialise)
{
	switch (tileSpecialise)
	{
	case TileSpecialise::FACTORY:
		return "FACTORY";
	case TileSpecialise::FLOOR:
		return "FLOOR";
	case TileSpecialise::HIGH_VOLTAGE_LINES:
		return "HIGH_VOLTAGE_LINES";
	case TileSpecialise::HOSPITAL:
		return "HOSPITAL";
	case TileSpecialise::HOUSE:
		return "HOUSE";
	case TileSpecialise::POWER_HOUSE:
		return "POWER_HOUSE";
	case TileSpecialise::ROAD:
		return "ROAD";
	case TileSpecialise::ROCK:
		return "ROCK";
	case TileSpecialise::SHOP:
		return "SHOP";
	case TileSpecialise::SPECTRUM_PLATE:
		return "SPECTRUM_PLATE";
	case TileSpecialise::TREE:
		return "TREE";
	case TileSpecialise::VOID:
		return "VOID";
	case TileSpecialise::WATER:
		return "WATER";
	case TileSpecialise::FIRE_BRIGADE:
		return "FIRE_STATION";
	default:
		return "VOID";
	}
}

void SmallTile::SetNewTileVariant(const SmallTile* neighbourhood[NEIGHBORING][NEIGHBORING])
{
	//... SOON
}

void SmallTile::SetPosition(int x, int y)
{
	this->position.x = x;
	this->position.y = y;
}

void SmallTile::SetTileData(TileData tileData)
{
	this->tileData = tileData;
}

void SmallTile::SetSelectionProcess(SelectionProcess selectionProcess)
{
	this->selectionProcess = selectionProcess;
}

#pragma endregion

#pragma region Getters

TypeOfTile SmallTile::GetTypeOfTile() const
{
	return this->typeOfTile;
}

bool SmallTile::GetIsRoad() const
{
	if (tileSpecialise == TileSpecialise::ROAD)
	{
		return true;
	}
	return false;
}

bool SmallTile::GetIsVoltagePylon() const
{
	if (this->tileSpecialise == TileSpecialise::HIGH_VOLTAGE_LINES)
	{
		return true;
	}
	return false;
}

bool SmallTile::GetIsPowerHouse() const
{
	if (this->tileSpecialise == TileSpecialise::POWER_HOUSE)
	{
		return true;
	}
	return false;
}

bool SmallTile::GetIsRuins() const
{
	if (this->tileSpecialise == TileSpecialise::RUINS)
	{
		return true;
	}
	return false;
}

bool SmallTile::GetIsTrees() const
{
	if (this->tileSpecialise == TileSpecialise::TREE)
	{
		return true;
	}
	return false;
}

bool SmallTile::GetIsWater() const
{
	if (this->tileSpecialise == TileSpecialise::WATER)
	{
		return true;
	}
	return false;
}

bool SmallTile::GetIsFactory() const
{
	if (this->tileSpecialise == TileSpecialise::FACTORY)
	{
		return true;
	}
	return false;
}

bool SmallTile::GetIsShops() const
{
	if (this->tileSpecialise == TileSpecialise::SHOP)
	{
		return true;
	}
	return false;
}

bool SmallTile::GetIsBuilding() const
{
	if (this->typeOfTile == TypeOfTile::STRUCTURE)
		return true;

	return false;
}

sf::Vector2f SmallTile::GetFixedPosition()
{
	return sf::Vector2f(this->sprite.getPosition().x + 32, this->sprite.getPosition().y + 16);
}

SelectionProcess SmallTile::GetSelectionProcess() const
{
	return this->selectionProcess;
}

sf::Sprite SmallTile::GetSprite() const
{
	return this->sprite;
}

TileData SmallTile::GetTileData() const
{
	return this->tileData;
}

TileSpecialise SmallTile::GetTileSpecialise() const
{
	return this->tileSpecialise;
}

sf::Vector2i SmallTile::GetPosition() const
{
	return position;
}

sf::Vector2f SmallTile::GetSpritePosition() const
{
	return this->sprite.getPosition();
}

#pragma endregion