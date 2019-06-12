#include "GameEventInfo.h"

GameEventInfo::GameEventInfo(std::shared_ptr<AssetsOfGame> ptrGame, int windowPosCorrection)
{
	this->ptrGame = ptrGame;

	this->centre = sf::Vector2f(windowPosCorrection, windowPosCorrection * 0.5);
	this->centre *= float(TILE_SIZE);

	this->ptrGame->textureManager.LoadAsset("envelope", "Resources/Textures/envelope.png");
	this->envelope.setTexture(&this->ptrGame->textureManager.GetAsset("envelope"));
	this->envelope.setSize(sf::Vector2f(calcCharSize(this->ptrGame->videoMode, 50), calcCharSize(this->ptrGame->videoMode, 50)));

	this->InitializeTextParameters();
}

void GameEventInfo::InitializeTextParameters()
{
	this->ptrGame->fontManager.LoadAsset("Delimax","Resources/Fonts/Delimax.ttf");

	this->informationText.setFont(this->ptrGame->fontManager.GetAsset("Delimax"));
	this->informationText.setCharacterSize(calcCharSize(this->ptrGame->videoMode));
	this->informationText.setPosition(p2pX(40.0f, this->ptrGame->videoMode) - (this->informationText.getGlobalBounds().width / 2.f) + this->centre.x, p2pY(90.0f, this->ptrGame->videoMode) + this->centre.y);
	this->envelope.setPosition(p2pX(33.0f, this->ptrGame->videoMode) - (this->informationText.getGlobalBounds().width / 2.f) + this->centre.x, p2pY(88.0f, this->ptrGame->videoMode) + this->centre.y);

	this->counterText.setFont(this->ptrGame->fontManager.GetAsset("Delimax"));
	this->counterText.setFillColor(sf::Color::Red);
	this->counterText.setCharacterSize(calcCharSize(this->ptrGame->videoMode, 80));
	this->counterText.setPosition(p2pX(35.0f, this->ptrGame->videoMode) - (this->informationText.getGlobalBounds().width / 2.f) + this->centre.x, p2pY(90.0f, this->ptrGame->videoMode) + this->centre.y);
}

void GameEventInfo::DrawInformation()
{
	if (!this->informationQueue.empty())
	{
		this->informationQueue.front().information.setFillColor(sf::Color(
			this->informationQueue.front().information.getFillColor().r,
			this->informationQueue.front().information.getFillColor().g,
			this->informationQueue.front().information.getFillColor().b,
			255 - this->informationQueue.front().counterLife));

		this->ptrGame->window->draw(this->informationQueue.front().information);
		this->ptrGame->window->draw(this->envelope);
		this->ptrGame->window->draw(this->counterText);
	}
}

void GameEventInfo::PushInformationToQueue(const std::string & information, InfoType infoType)
{
	switch (infoType)
	{
	case InfoType::BUTTON:
		this->informationText.setFillColor(sf::Color::Blue);
		break;
	case InfoType::GOOD_INFO:
		this->informationText.setFillColor(sf::Color::Green);
		break;
	case InfoType::BAD_INFO:
		this->informationText.setFillColor(sf::Color::Red);
		break;
	}

	this->informationText.setString(information);

	this->informationQueue.push(Information{ informationText, 0 });
	this->counterInformation++;
}

void GameEventInfo::UpdateInformationText()
{
	this->counterText.setString(std::to_string(this->counterInformation));

	if (!this->informationQueue.empty())
	{
		this->informationQueue.front().counterLife++;
		if (this->informationQueue.front().counterLife > this->lifeTimeInformation)
		{
			this->informationQueue.pop();
			this->counterInformation--;
		}
	}
}