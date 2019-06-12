#include "Newspaper.h"

#pragma region Constructors

Newspaper::Newspaper(std::shared_ptr<AssetsOfGame> ptrGame, HoldGameplay *holdGameplay, int sizeMap)
	:TableBase(ptrGame, sizeMap)
{
	createNewspaper = new CreateNewspaper(holdGameplay);

	this->InitializeFont();
	this->InitializeButtons();
	this->InitializeText();
	this->InitializeBackground();
}

Newspaper::~Newspaper()
{
	if (this->createNewspaper != nullptr)
	{
		delete this->createNewspaper;
		this->createNewspaper = nullptr;
	}

	if (this->exitButton != nullptr)
	{
		delete this->exitButton;
		this->exitButton = nullptr;
	}
}

#pragma endregion

#pragma region Class_Methods

void Newspaper::InitializeButtons()
{
	this->exitButton = new TextButton(p2pX(40.0f, this->ptrGame->videoMode) + this->centre.x, p2pY(86.0f, this->ptrGame->videoMode) + this->centre.y,
		p2pX(10.0f, this->ptrGame->videoMode), p2pY(10.0f, this->ptrGame->videoMode),
		"DONE", calcCharSize(this->ptrGame->videoMode), sf::Color::Green, sf::Color(102, 153, 153), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), this->ptrGame);
}

void Newspaper::InitializeText()
{
	this->titleText.setFont(this->ptrGame->fontManager.GetAsset("Chomsky"));
	this->titleText.setFillColor(sf::Color::Black);
	this->titleText.setCharacterSize(calcCharSize(this->ptrGame->videoMode, 55));
	this->titleText.setString("unknown");
	this->titleText.setPosition(p2pX(45.0f, this->ptrGame->videoMode) - (this->titleText.getGlobalBounds().width / 2.f) + this->centre.x, p2pY(40.0f, this->ptrGame->videoMode) + this->centre.y);

	this->dataText.setFont(this->ptrGame->fontManager.GetAsset("AnticDidone-Regular"));
	this->dataText.setFillColor(sf::Color::Black);
	this->dataText.setCharacterSize(calcCharSize(this->ptrGame->videoMode, 70));
	this->dataText.setString("unknown");
	this->dataText.setPosition(p2pX(55.0f, this->ptrGame->videoMode) - (this->dataText.getGlobalBounds().width / 2.f) + this->centre.x, p2pY(45.0f, this->ptrGame->videoMode) + this->centre.y);

	this->bodyText.setFont(this->ptrGame->fontManager.GetAsset("AnticDidone-Regular"));
	this->bodyText.setFillColor(sf::Color::Black);
	this->bodyText.setCharacterSize(calcCharSize(this->ptrGame->videoMode, 70));
	this->bodyText.setString("unknown");
	this->bodyText.setPosition(p2pX(40.0f, this->ptrGame->videoMode) - (this->bodyText.getGlobalBounds().width / 2.f) + this->centre.x, p2pY(60.0f, this->ptrGame->videoMode) + this->centre.y);
}

void Newspaper::InitializeFont()
{
	this->ptrGame->fontManager.LoadAsset("Chomsky", "Resources/Fonts/Chomsky.otf");
	this->ptrGame->fontManager.LoadAsset("AnticDidone-Regular", "Resources/Fonts/AnticDidone-Regular.ttf");
}

void Newspaper::InitializeBackground()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->ptrGame->window->getSize().x),
		static_cast<float>(this->ptrGame->window->getSize().y)));
	this->ptrGame->textureManager.LoadAsset("newspaper", "Resources/Textures/newspaper.png");
	this->background.setTexture(&this->ptrGame->textureManager.GetAsset("newspaper"));
	this->background.setPosition(this->centre.x, this->centre.y);
}

void Newspaper::DrawTable()
{
	this->ptrGame->window->draw(this->background);
	this->exitButton->DrawButton(this->ptrGame->window);

	this->ptrGame->window->draw(this->dataText);
	this->ptrGame->window->draw(this->titleText);
	this->ptrGame->window->draw(this->bodyText);
}

void Newspaper::UpdateTable(float elapsedTime)
{
	this->exitButton->UpdateButton((sf::Vector2f)this->ptrGame->mousePositionMap, elapsedTime);

	if (this->exitButton->GetPressed())
	{
		this->tableOpen = false;
	}
}

void Newspaper::NewspaperEvent(TypeOfNewspaper typeOfNewspaper)
{
	switch (typeOfNewspaper)
	{
	case TypeOfNewspaper::NEW_GAME:
		this->createNewspaper->LoadNewspapersFromFile("Resources/Newspapers/new_game_article.txt");
		break;
	case TypeOfNewspaper::REGULAR:
		this->createNewspaper->LoadNewspapersFromFile("Resources/Newspapers/regular_article.txt");
		break;
	}

	this->templateNewspaper2 = this->createNewspaper->GenerateNewspaper(typeOfNewspaper);

	this->dataText.setString(this->templateNewspaper2.date);
	this->titleText.setString(this->templateNewspaper2.title);
	this->bodyText.setString(this->templateNewspaper2.text);
}

#pragma endregion