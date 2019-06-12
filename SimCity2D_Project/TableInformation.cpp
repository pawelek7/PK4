#include "TableInformation.h"

#pragma region Constructors

TableLook::TableLook(sf::Font* font, float tableSizeX, float tableSizeY, float characterSize,
	sf::Color tableColor, sf::Color textColor, sf::Color bolderColor, sf::Color highLightColor)
{
	this->tableColor = tableColor;
	this->textColor = textColor;
	this->bolderColor = bolderColor;
	this->highLightColor = highLightColor;

	this->tableSizeX = tableSizeX;
	this->tableSizeY = tableSizeY;

	this->font = font;
	this->characterSize = characterSize;
}

GuiTableOption::GuiTableOption(const std::string & guiString, sf::RectangleShape rectangleShape, sf::Text text)
{
	this->guiString = guiString;
	this->rectangleShape = rectangleShape;
	this->text = text;
}

TableInformation::TableInformation(std::vector<std::pair<std::string, std::string>> text, TableLook tableLook)
{
	this->hide = false;
	this->tableLook = tableLook;

	sf::RectangleShape rectangleShape;
	rectangleShape.setSize(sf::Vector2f(tableLook.tableSizeX, tableLook.tableSizeY));
	rectangleShape.setFillColor(tableLook.tableColor);
	rectangleShape.setOutlineColor(tableLook.bolderColor);
	rectangleShape.setOutlineThickness(1);

	for (auto & it : text)
	{
		sf::Text _text;
		_text.setString(it.first);
		_text.setFont(*tableLook.font);
		_text.setFillColor(tableLook.textColor);
		_text.setCharacterSize(tableLook.characterSize);

		this->textLines.push_back(GuiTableOption(it.second, rectangleShape, _text));
	}
}

#pragma endregion

#pragma region Class_Methods

void TableInformation::draw(sf::RenderTarget & renderTarget, sf::RenderStates renderStates) const
{
	if (!this->hide)
	{
		return;
	}

	for (auto & it : this->textLines)
	{
		renderTarget.draw(it.rectangleShape);
		renderTarget.draw(it.text);
	}
}

void TableInformation::ShowTable()
{
	sf::Vector2f offset(0.0f, 0.0f);

	this->hide = true;

	for (auto & it : this->textLines)
	{
		sf::Vector2f origin = this->getOrigin();
		origin -= offset;
		it.rectangleShape.setOrigin(origin);
		it.text.setOrigin(origin);

		it.rectangleShape.setPosition(this->getPosition());
		it.text.setPosition(this->getPosition().x, this->getPosition().y);

		offset.y += this->tableLook.characterSize + 1;
	}
}

void TableInformation::Hidetable()
{
	this->hide = false;
}

void TableInformation::GlowElement(int it)
{
	this->activated = false;

	for (int i = 0; i < this->textLines.size(); i++)
	{
		if (i == it)
		{
			this->textLines[i].rectangleShape.setFillColor(this->tableLook.highLightColor);
			this->activated = true;
		}
		else
		{
			this->textLines[i].rectangleShape.setFillColor(this->tableLook.tableColor);
		}
	}
}

std::string TableInformation::ActivatedElement(int it)
{
	return this->textLines[it].text.getString();
}

std::string TableInformation::ActivatedElement(const sf::Vector2f & mousePosition)
{
	int it = this->GetOption(mousePosition);

	if (it == -1)
	{
		return "unknown";
	}

	return this->ActivatedElement(it);
}

#pragma endregion

#pragma region Setters
//setters

void TableInformation::SetTableText(int entry, std::string text)
{
	if (entry >= textLines.size() || entry < 0) return;

	textLines[entry].text.setString(text);
}

#pragma endregion

#pragma region Getters
//getters

int TableInformation::GetOption(const sf::Vector2f & mousePosition)
{
	if (!this->hide)
	{
		return -1;
	}

	for (int i = 0; i < this->textLines.size(); i++)
	{
		
		sf::Vector2f pos = mousePosition;
		pos += this->textLines[i].rectangleShape.getOrigin();
		pos -= this->textLines[i].rectangleShape.getPosition();
		
		if (!this->textLines[i].rectangleShape.getGlobalBounds().contains(mousePosition))
		{
			continue;
		}

		return i;
	}

	return -1;
}

bool TableInformation::GetIsActivated()
{
	return this->activated;
}

#pragma endregion