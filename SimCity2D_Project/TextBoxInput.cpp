#include "TextBoxInput.h"
#include <typeinfo>

#pragma region Constructors

TextBoxInput::TextBoxInput()
{
	maxChars = 100;
	LoadFont("Resources/Fonts/Delimax.ttf");

	currentTextDisplayT.setFont(font);
	currentTextDisplayT.setCharacterSize(12.0f);
	currentTextDisplayT.setFillColor(sf::Color::White);
	currentTextDisplayT.setPosition(0, 0);

	rightTextBound = int(currentTextDisplayT.getPosition().x + 100);

	cursorShape.setSize(sf::Vector2f(3.0f, 12.0f * 5 / 4));

	bounds.left = 0;
	bounds.top = 0;
	bounds.width = 100;
	bounds.height = 12;

	shouldEnter = true;
	SetCursor(0);
}

TextBoxInput::TextBoxInput(float x, float y, int boxWidth, float fontSize, const std::string & fonrPath,
	bool onlyNumbers, int maxChars, sf::Color color)
	:cursorShape(sf::Vector2f(3.0f, fontSize * 5 / 4))
{
	this->maxChars = maxChars;
	this->onlyNumbers = onlyNumbers;
	LoadFont(fonrPath);

	currentTextDisplayT.setFont(font);
	currentTextDisplayT.setCharacterSize(fontSize);
	currentTextDisplayT.setFillColor(sf::Color::White);
	currentTextDisplayT.setPosition(x, y);

	cursorShape.setFillColor(sf::Color::White);

	bounds.left = x;
	bounds.top = y;
	bounds.width = x + boxWidth + 25;
	bounds.height = fontSize;

	rightTextBound = int(currentTextDisplayT.getPosition().x + boxWidth);

	shouldEnter = true;
	SetCursor(0);
}

#pragma endregion

#pragma region Class_Methods

void TextBoxInput::Update(sf::Event &events, const sf::Vector2f & mousePosition)
{
	if (this->bounds.contains(mousePosition) && events.mouseButton.button == sf::Mouse::Left)
	{
		focus = true;
	}
	else if (!this->bounds.contains(mousePosition) && events.mouseButton.button == sf::Mouse::Left)
	{
		focus = false;

	}

	if (this->focus == true)
	{
		HandleLocalTextInput(events, mousePosition);
	}
}


void TextBoxInput::HandleLocalTextInput(sf::Event & events, const sf::Vector2f & mousePosition)
{
	if ((events.type == sf::Event::TextEntered))
	{
		if ((events.text.unicode < 128) && (events.text.unicode != 8) && (events.text.unicode != 13)
			&& (tempBuffer.size() < (size_t)maxChars))
		{
			if (this->onlyNumbers == true && (events.text.unicode < 48 || events.text.unicode > 57))
			{
				return;
			}

			cursor++;

			sendBuffer += static_cast<char>(events.text.unicode);
			tempBuffer += static_cast<char>(events.text.unicode);

			currentTextDisplayT.setString(tempBuffer);

			if (currentTextDisplayT.getGlobalBounds().width > rightTextBound)
			{
				int charsToShiftOff = int((currentTextDisplayT.getLocalBounds().width - (rightTextBound)));
				for (int i = 0; i < charsToShiftOff; i++)
				{
					tempBuffer.erase(tempBuffer.begin());
				}
				currentTextDisplayT.setString(tempBuffer);
			}
		}
		else if (events.text.unicode == 8)
		{
			if (sendBuffer.size() > 0)
			{
				sendBuffer.resize(sendBuffer.size() - 1);
				cursor--;
			}
			if (tempBuffer.size() > 0)
			{
				tempBuffer.resize(tempBuffer.size() - 1);
			}
			if (currentTextDisplayT.getGlobalBounds().width < (rightTextBound))
			{
				if (sendBuffer.size() - tempBuffer.size() > 0)
				{
					tempBuffer = sendBuffer[sendBuffer.size() - (tempBuffer.size() + 1)] + tempBuffer;
				}
				currentTextDisplayT.setString(tempBuffer);
			}
			currentTextDisplayT.setString(tempBuffer);
		}
		SetCursor(cursor);
	}
}

void TextBoxInput::Draw(sf::RenderWindow *renderWindow)
{
	renderWindow->draw(currentTextDisplayT);

	elapsedTime = (elapsedTime + clock.restart().asMilliseconds()) % 200;

	if (focus && elapsedTime < 100)
	{
		renderWindow->draw(cursorShape);
	}

}

void TextBoxInput::LoadFont(const std::string & fontPath)
{
	if (!font.loadFromFile(fontPath))
	{
		std::cout << " Text box input was not loaded." << std::endl;
	}
}

void TextBoxInput::EraseButtons()
{
	tempBuffer.clear();
	sendBuffer.clear();
	currentTextDisplayT.setString(sendBuffer);
}

void TextBoxInput::ResetClock() const
{
	elapsedTime = 0;
	clock.restart();
}

#pragma endregion

#pragma region Setters

void TextBoxInput::SetPosition(float x, float y)
{
	currentTextDisplayT.setPosition(x, y);
}

void TextBoxInput::SetCursor(std::size_t cursor)
{
	this->cursor = cursor;
	if (cursor >= currentTextDisplayT.getString().getSize())
	{
		cursorShape.setPosition(sf::Vector2f(currentTextDisplayT.getGlobalBounds().left + currentTextDisplayT.getGlobalBounds().width, currentTextDisplayT.getPosition().y));
	}
	else
	{
		cursorShape.setPosition(currentTextDisplayT.findCharacterPos(cursor));
	}
	ResetClock();
}

void TextBoxInput::SetString(const std::string & text)
{
	this->currentTextDisplayT.setString(text);
}

#pragma endregion

#pragma region Getters

sf::Vector2f TextBoxInput::GetPosition()
{
	return currentTextDisplayT.getPosition();
}

std::string TextBoxInput::GetString() const
{
	return this->currentTextDisplayT.getString();
}

#pragma endregion