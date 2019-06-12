#include "Statistics.h"

#pragma region Constructors

Statistics::Statistics(std::shared_ptr<AssetsOfGame> ptrGame, int sizeMap)
	:TableBase(ptrGame, sizeMap)
{
	this->InitializeFont();
	this->InitializeButtons();
	this->InitializeText();
	this->InitializeBackground();
}

Statistics::~Statistics()
{
	if (this->closeButton != nullptr)
	{
		delete this->closeButton;
		this->closeButton = nullptr;
	}
}

#pragma endregion

#pragma region Class_Methods

void Statistics::InitializeFont()
{
	this->ptrGame->fontManager.LoadAsset("CRACKERS BRUSHER", "Resources/Fonts/CRACKERS BRUSHER.otf");
}

void Statistics::InitializeButtons()
{
	this->closeButton = new TextButton(p2pX(35.0f, this->ptrGame->videoMode) + this->centre.x, p2pY(30.0f, this->ptrGame->videoMode) + this->centre.y,
		p2pX(10.0f, this->ptrGame->videoMode), p2pY(10.0f, this->ptrGame->videoMode),
		"DONE", calcCharSize(this->ptrGame->videoMode), sf::Color::White, sf::Color(102, 153, 153), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), this->ptrGame);
}

void Statistics::InitializeText()
{
	this->populationText.setFont(this->ptrGame->fontManager.GetAsset("CRACKERS BRUSHER"));
	this->populationText.setFillColor(sf::Color::Black);
	this->populationText.setCharacterSize(calcCharSize(this->ptrGame->videoMode, 70));
	this->populationText.setString("unknown");
	this->populationText.setPosition(p2pX(70.0f, this->ptrGame->videoMode) - (this->populationText.getGlobalBounds().width / 2.f) + this->centre.x, p2pY(30.0f, this->ptrGame->videoMode) + this->centre.y);

	this->workingText.setFont(this->ptrGame->fontManager.GetAsset("CRACKERS BRUSHER"));
	this->workingText.setFillColor(sf::Color::Black);
	this->workingText.setCharacterSize(calcCharSize(this->ptrGame->videoMode, 70));
	this->workingText.setString("unknown");
	this->workingText.setPosition(p2pX(70.0f, this->ptrGame->videoMode) - (this->workingText.getGlobalBounds().width / 2.f) + this->centre.x, p2pY(35.0f, this->ptrGame->videoMode) + this->centre.y);

	this->homelessText.setFont(this->ptrGame->fontManager.GetAsset("CRACKERS BRUSHER"));
	this->homelessText.setFillColor(sf::Color::Black);
	this->homelessText.setCharacterSize(calcCharSize(this->ptrGame->videoMode, 70));
	this->homelessText.setString("unknown");
	this->homelessText.setPosition(p2pX(70.0f, this->ptrGame->videoMode) - (this->homelessText.getGlobalBounds().width / 2.f) + this->centre.x, p2pY(40.0f, this->ptrGame->videoMode) + this->centre.y);

	this->happinessText.setFont(this->ptrGame->fontManager.GetAsset("CRACKERS BRUSHER"));
	this->happinessText.setFillColor(sf::Color::Black);
	this->happinessText.setCharacterSize(calcCharSize(this->ptrGame->videoMode, 70));
	this->happinessText.setString("unknown");
	this->happinessText.setPosition(p2pX(70.0f, this->ptrGame->videoMode) - (this->happinessText.getGlobalBounds().width / 2.f) + this->centre.x, p2pY(45.0f, this->ptrGame->videoMode) + this->centre.y);

	this->attractivnessText.setFont(this->ptrGame->fontManager.GetAsset("CRACKERS BRUSHER"));
	this->attractivnessText.setFillColor(sf::Color::Black);
	this->attractivnessText.setCharacterSize(calcCharSize(this->ptrGame->videoMode, 70));
	this->attractivnessText.setString("unknown");
	this->attractivnessText.setPosition(p2pX(70.0f, this->ptrGame->videoMode) - (this->attractivnessText.getGlobalBounds().width / 2.f) + this->centre.x, p2pY(50.0f, this->ptrGame->videoMode) + this->centre.y);

	this->moneyText.setFont(this->ptrGame->fontManager.GetAsset("CRACKERS BRUSHER"));
	this->moneyText.setFillColor(sf::Color::Black);
	this->moneyText.setCharacterSize(calcCharSize(this->ptrGame->videoMode, 70));
	this->moneyText.setString("unknown");
	this->moneyText.setPosition(p2pX(70.0f, this->ptrGame->videoMode) - (this->moneyText.getGlobalBounds().width / 2.f) + this->centre.x, p2pY(55.0f, this->ptrGame->videoMode) + this->centre.y);

	this->dateText.setFont(this->ptrGame->fontManager.GetAsset("CRACKERS BRUSHER"));
	this->dateText.setFillColor(sf::Color::Black);
	this->dateText.setCharacterSize(calcCharSize(this->ptrGame->videoMode, 70));
	this->dateText.setString("unknown");
	this->dateText.setPosition(p2pX(70.0f, this->ptrGame->videoMode) - (this->dateText.getGlobalBounds().width / 2.f) + this->centre.x, p2pY(60.0f, this->ptrGame->videoMode) + this->centre.y);

	this->cityNameText.setFont(this->ptrGame->fontManager.GetAsset("CRACKERS BRUSHER"));
	this->cityNameText.setFillColor(sf::Color::Black);
	this->cityNameText.setCharacterSize(calcCharSize(this->ptrGame->videoMode, 70));
	this->cityNameText.setString("unknown");
	this->cityNameText.setPosition(p2pX(70.0f, this->ptrGame->videoMode) - (this->dateText.getGlobalBounds().width / 2.f) + this->centre.x, p2pY(65.0f, this->ptrGame->videoMode) + this->centre.y);

	this->incomeThisMonthText.setFont(this->ptrGame->fontManager.GetAsset("CRACKERS BRUSHER"));
	this->incomeThisMonthText.setFillColor(sf::Color::Black);
	this->incomeThisMonthText.setCharacterSize(calcCharSize(this->ptrGame->videoMode, 70));
	this->incomeThisMonthText.setString("unknown");
	this->incomeThisMonthText.setPosition(p2pX(70.0f, this->ptrGame->videoMode) - (this->dateText.getGlobalBounds().width / 2.f) + this->centre.x, p2pY(70.0f, this->ptrGame->videoMode) + this->centre.y);

	this->incomePreviousMonthText.setFont(this->ptrGame->fontManager.GetAsset("CRACKERS BRUSHER"));
	this->incomePreviousMonthText.setFillColor(sf::Color::Black);
	this->incomePreviousMonthText.setCharacterSize(calcCharSize(this->ptrGame->videoMode, 70));
	this->incomePreviousMonthText.setString("unknown");
	this->incomePreviousMonthText.setPosition(p2pX(70.0f, this->ptrGame->videoMode) - (this->dateText.getGlobalBounds().width / 2.f) + this->centre.x, p2pY(75.0f, this->ptrGame->videoMode) + this->centre.y);
}


void Statistics::InitializeBackground()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->ptrGame->window->getSize().x),
		static_cast<float>(this->ptrGame->window->getSize().y)));
	this->ptrGame->textureManager.LoadAsset("statistics_information", "Resources/Textures/statistics_information.png");
	this->background.setTexture(&this->ptrGame->textureManager.GetAsset("statistics_information"));
	this->background.setPosition(this->centre.x, this->centre.y);
}

void Statistics::UpdateTable(float elapsedTime)
{
	this->closeButton->UpdateButton((sf::Vector2f)this->ptrGame->mousePositionMap, elapsedTime);

	if (this->closeButton->GetPressed())
	{
		this->tableOpen = false;
	}
}

void Statistics::DrawTable()
{
	this->ptrGame->window->draw(this->background);
	this->closeButton->DrawButton(this->ptrGame->window);

	this->ptrGame->window->draw(this->populationText);
	this->ptrGame->window->draw(this->workingText);
	this->ptrGame->window->draw(this->homelessText);
	this->ptrGame->window->draw(this->happinessText);
	this->ptrGame->window->draw(this->attractivnessText);
	this->ptrGame->window->draw(this->moneyText);
	this->ptrGame->window->draw(this->dateText);
	this->ptrGame->window->draw(this->cityNameText);
	this->ptrGame->window->draw(this->incomePreviousMonthText);
	this->ptrGame->window->draw(this->incomeThisMonthText);
}

#pragma endregion

#pragma region Setters

void Statistics::SetPopulationText(const std::string & text)
{
	this->populationText.setString("Population: " + text);
}

void Statistics::SetWorkingText(const std::string & text)
{
	this->workingText.setString("Workers: " + text);
}

void Statistics::SetHomelessText(const std::string & text)
{
	this->homelessText.setString("Homeless: "+text);
}

void Statistics::SetHappinessText(const std::string & text)
{
	this->happinessText.setString("Happiness: " + text + "%");
}

void Statistics::SetAttractivnessText(const std::string & text)
{
	this->attractivnessText.setString("Attractivness: " + text + "%");
}

void Statistics::SetMoneyText(const std::string & text)
{
	this->moneyText.setString("Money: " + text + "$");
}

void Statistics::SetDateText(const std::string & text)
{
	this->dateText.setString("Date: " + text);
}

void Statistics::SetCityNameText(const std::string & text)
{
	this->cityNameText.setString("City name: " + text);
}

void Statistics::SetIncomeThisMonthText(const std::string & text)
{
	this->incomeThisMonthText.setString("Newest income: " + text + "$");
}

void Statistics::SetIncomePreviousMonth(const std::string & text)
{
	this->incomePreviousMonthText.setString("Previous income: " + text + "$");
}

#pragma endregion