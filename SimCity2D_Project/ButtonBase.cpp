#include "ButtonBase.h"

#pragma region SizeModifer

const float p2pX(const float perc, const sf::VideoMode & vm)
{
	return std::floor(static_cast<float>(vm.width)*(perc / 100.0f));
}

const float p2pY(const float perc, const sf::VideoMode& vm)
{
	return std::floor(static_cast<float>(vm.height)*(perc / 100.0f));
}

const unsigned calcCharSize(const sf::VideoMode& vm, const unsigned modifier)
{
	return static_cast<unsigned>((vm.width + vm.height) / modifier);
}

#pragma endregion

#pragma region Constructors

ButtonBase::ButtonBase(float x, float y, float width, float height, short unsigned int buttonID, std::shared_ptr<AssetsOfGame> ptrGame)
{
	this->ptrGame = ptrGame;

	this->buttonState = ButtonState::IDLING;
	this->buttonID = buttonID;

	this->buttonHitbox.setPosition(sf::Vector2f(x, y));
	this->buttonHitbox.setSize(sf::Vector2f(width, height));
	this->buttonHitbox.setOutlineColor(sf::Color::Black);
	this->buttonHitbox.setOutlineThickness(2.0f);
}

#pragma endregion

#pragma region Class_Methods

void ButtonBase::UpdateButtonParameters(float x, float y, float width, float height)
{
	this->buttonHitbox.setPosition(sf::Vector2f(x, y));
	this->buttonHitbox.setSize(sf::Vector2f(width, height));
}

void ButtonBase::UpdateButton(const sf::Vector2f & mousePosition, const float & elapsedTime)
{
	this->buttonState = ButtonState::IDLING;
	this->mouseOnButton = false;

	if (this->buttonHitbox.getGlobalBounds().contains(mousePosition))
	{
		this->mouseOnButton = true;

		this->buttonState = ButtonState::HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = ButtonState::ACTIVE;
		}
	}

	this->UpdateKeyTime(elapsedTime);
	this->UpdateLook();
}


void ButtonBase::UpdateKeyTime(const float & elapsedTime)
{
	if (this->keyTime < this->keyTimeMax)
	{
		this->keyTime += 10.0f * elapsedTime;
	}
}

void ButtonBase::ChangeButtonPosition(float x, float y)
{
	this->buttonHitbox.setPosition(sf::Vector2f(x, y));
	this->ChangeElementPosition(x, y);
}

#pragma endregion

#pragma region Getters
//getters

bool ButtonBase::GetKeyTime()
{
	if (this->keyTime >= this->keyTimeMax)
	{
		this->keyTime = 0.0f;
		return true;
	}

	return false;
}

const bool ButtonBase::GetPressed()
{
	if (this->GetKeyTime())
	{
		if (this->buttonState == ButtonState::ACTIVE)
		{
			return true;
		}
	}

	return false;
}

const short unsigned int & ButtonBase::GetID() const
{
	return this->buttonID;
}

ButtonBase::ButtonState ButtonBase::GetButtonState() const
{
	return this->buttonState;
}

bool ButtonBase::GetMouseOnButton()
{
	return this->mouseOnButton;
}

#pragma endregion