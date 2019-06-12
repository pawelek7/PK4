#include "TextButton.h"

#pragma region Constructors

TextButton::TextButton(float x, float y, float width, float height, std::string text,
	unsigned short int characterSize, sf::Color textIdliing, sf::Color textHover, sf::Color textActive,
	sf::Color buttonIdling, sf::Color buttonHover, sf::Color buttonActive, std::shared_ptr<AssetsOfGame> ptrGame, bool drawHitbox,
	unsigned short int buttonID,sf::Color outlineIdleColor, sf::Color outlineHoverColor, sf::Color outlineActiveColor)
	:ButtonBase(x, y, width, height, buttonID, ptrGame)
{
	this->drawHitbox = drawHitbox;

	this->ptrGame->fontManager.LoadAsset("Delimax", "Resources/Fonts/Delimax.ttf");
	this->text.setFont(this->ptrGame->fontManager.GetAsset("Delimax"));
	this->text.setString(text);
	this->text.setFillColor(textIdling);
	this->text.setCharacterSize(characterSize);

	this->text.setPosition(
		this->buttonHitbox.getPosition().x + (this->buttonHitbox.getGlobalBounds().width / 2.0f) - this->text.getGlobalBounds().width / 2.0f,
		this->buttonHitbox.getPosition().y);

	this->textIdling = textIdliing;
	this->textHover = textHover;
	this->textActive = textActive;

	this->buttonHover = buttonHover;
	this->buttonActive = buttonActive;
	this->buttonIdling = buttonIdling;

	this->outlineIdleColor = outlineActiveColor;
	this->outlineHoverColor = outlineHoverColor;
	this->outlineIdleColor = outlineIdleColor;
}

#pragma endregion

#pragma region Class_Methods

void TextButton::ChangePositionAndSize(float x, float y, float width, float height, int characterSize)
{
	this->UpdateButtonParameters(x, y, width, height);

	this->text.setCharacterSize(characterSize);

	this->text.setPosition(
		this->buttonHitbox.getPosition().x + (this->buttonHitbox.getGlobalBounds().width / 2.0f) - this->text.getGlobalBounds().width / 2.0f,
		this->buttonHitbox.getPosition().y);
}

void TextButton::DrawButton(sf::RenderTarget *renderTarget)
{
	if (drawHitbox == true)
	{
		renderTarget->draw(this->buttonHitbox);
	}

	renderTarget->draw(this->text);
}

void TextButton::UpdateLook()
{
	switch (GetButtonState())
	{
	case ButtonState::IDLING:
		this->buttonHitbox.setFillColor(this->buttonIdling);
		this->text.setFillColor(this->textIdling);
		break;
	case ButtonState::HOVER:
		this->buttonHitbox.setFillColor(this->buttonHover);
		this->text.setFillColor(this->textHover);
		break;
	case ButtonState::ACTIVE:
		this->buttonHitbox.setFillColor(this->textActive);
		this->text.setFillColor(this->textActive);
		break;
	default:
		this->buttonHitbox.setFillColor(sf::Color::Red);
		this->text.setFillColor(sf::Color::White);
		break;
	}
}

void TextButton::ChangeElementPosition(float x, float y)
{
	this->text.setPosition(x, y);
}

#pragma endregion

#pragma region Setters
//setters

void TextButton::SetID(unsigned int id)
{
	this->buttonID = id;
}

void TextButton::SetString(const std::string & text)
{
	this->text.setString(text);
}

#pragma endregion

#pragma region Getters
//getters

std::string TextButton::GetString() const
{
	return this->text.getString();
}

sf::Text TextButton::GetText() const
{
	return this->text;
}

#pragma endregion