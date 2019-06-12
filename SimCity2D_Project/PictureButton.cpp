#include "PictureButton.h"

#pragma region Constructors

PictureButton::PictureButton(float x, float y, float width, float height, unsigned short int size,
	const sf::Texture* pictureOfButtonIDLING, const sf::Texture* pictureOfButtonACTIVE, std::shared_ptr<AssetsOfGame> ptrGame,
	unsigned short int buttonID) :ButtonBase(x, y, width, height, buttonID, ptrGame)
{
	this->pictureOfButton.setTexture(pictureOfButtonIDLING);
	this->textACTIVE = *pictureOfButtonACTIVE;
	this->textIDLE = *pictureOfButtonIDLING;

	this->pictureOfButton.setPosition(x, y);
	this->pictureOfButton.setSize(sf::Vector2f(width, height));
}

#pragma endregion

#pragma region Class_Methods

void PictureButton::ChangeElementPosition(float x, float y)
{
	this->pictureOfButton.setPosition(
		this->buttonHitbox.getPosition().x + (this->buttonHitbox.getGlobalBounds().width / 2.0f) - this->pictureOfButton.getGlobalBounds().width / 2.0f,
		this->buttonHitbox.getPosition().y + (this->buttonHitbox.getGlobalBounds().height / 2.0f) - this->pictureOfButton.getGlobalBounds().height / 2.0f
	);
}

void PictureButton::DrawButton(sf::RenderTarget *renderTarget)
{
	renderTarget->draw(this->pictureOfButton);
}

void PictureButton::UpdateLook()
{
	switch (GetButtonState())
	{
	case ButtonState::IDLING:
		this->pictureOfButton.setTexture(&textIDLE);
		break;
	case ButtonState::HOVER:
		this->pictureOfButton.setTexture(&textIDLE);
		break;
	case ButtonState::ACTIVE:
		this->pictureOfButton.setTexture(&textACTIVE);
		break;
	default:
		this->buttonHitbox.setFillColor(sf::Color::Red);
		break;
	}
}

#pragma endregion