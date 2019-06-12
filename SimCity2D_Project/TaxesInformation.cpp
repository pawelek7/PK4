#include "TaxesInformation.h"

#pragma region Constructors

TaxesInformation::TaxesInformation(std::shared_ptr<AssetsOfGame> ptrGame, int sizeMap)
	:TableBase(ptrGame, sizeMap)
{
	this->InitializeFont();
	this->InitializeText();
	this->InitializeBackground();
	this->InitializeButtons();
}

TaxesInformation::~TaxesInformation()
{
	auto i = mapButtons.begin();
	for (i = mapButtons.begin(); i != mapButtons.end(); i++)
	{
		if (i->second != nullptr)
		{
			delete i->second;
			i->second = nullptr;
		}
	}
}

#pragma endregion

#pragma region Class_Methods

void TaxesInformation::InitializeButtons()
{
	this->mapButtons["DONE"] = new TextButton(p2pX(30.0f, this->ptrGame->videoMode) + this->centre.x, p2pY(35.0f, this->ptrGame->videoMode) + this->centre.y,
		p2pX(10.0f, this->ptrGame->videoMode), calcCharSize(this->ptrGame->videoMode),
		"APPLY", calcCharSize(this->ptrGame->videoMode), sf::Color(0, 128,0), sf::Color(102, 153, 153), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), this->ptrGame);

	this->mapButtons["CANCEL"] = new TextButton(p2pX(30.0f, this->ptrGame->videoMode) + this->centre.x, p2pY(40.0f, this->ptrGame->videoMode) + this->centre.y,
		p2pX(10.0f, this->ptrGame->videoMode), calcCharSize(this->ptrGame->videoMode),
		"CANCEL", calcCharSize(this->ptrGame->videoMode), sf::Color::Red, sf::Color(102, 153, 153), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), this->ptrGame);

	this->mapButtons["NEXT_TAXES"] = new TextButton(p2pX(67.0f, this->ptrGame->videoMode) + this->centre.x, p2pY(47.0f, this->ptrGame->videoMode) + this->centre.y,
		p2pX(10.0f, this->ptrGame->videoMode), p2pY(10.0f, this->ptrGame->videoMode),
		">", calcCharSize(this->ptrGame->videoMode), sf::Color::Yellow, sf::Color(102, 153, 153), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), this->ptrGame);

	this->mapButtons["BACK_TAXES"] = new TextButton(p2pX(53.0f, this->ptrGame->videoMode) + this->centre.x, p2pY(47.0f, this->ptrGame->videoMode) + this->centre.y,
		p2pX(10.0f, this->ptrGame->videoMode), p2pY(10.0f, this->ptrGame->videoMode),
		"<", calcCharSize(this->ptrGame->videoMode), sf::Color::Yellow, sf::Color(102, 153, 153), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), this->ptrGame);

	this->mapButtons["NEXT_ORDINANCES"] = new TextButton(p2pX(67.0f, this->ptrGame->videoMode) + this->centre.x, p2pY(55.0f, this->ptrGame->videoMode) + this->centre.y,
		p2pX(10.0f, this->ptrGame->videoMode), p2pY(10.0f, this->ptrGame->videoMode),
		">", calcCharSize(this->ptrGame->videoMode), sf::Color::Yellow, sf::Color(102, 153, 153), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), this->ptrGame);

	this->mapButtons["BACK_ORDINANCES"] = new TextButton(p2pX(53.0f, this->ptrGame->videoMode) + this->centre.x, p2pY(55.0f, this->ptrGame->videoMode) + this->centre.y,
		p2pX(10.0f, this->ptrGame->videoMode), p2pY(10.0f, this->ptrGame->videoMode),
		"<", calcCharSize(this->ptrGame->videoMode), sf::Color::Yellow, sf::Color(102, 153, 153), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), this->ptrGame);

	this->mapButtons["NEXT_POLICE"] = new TextButton(p2pX(67.0f, this->ptrGame->videoMode) + this->centre.x, p2pY(64.0f, this->ptrGame->videoMode) + this->centre.y,
		p2pX(10.0f, this->ptrGame->videoMode), p2pY(10.0f, this->ptrGame->videoMode),
		">", calcCharSize(this->ptrGame->videoMode), sf::Color::Yellow, sf::Color(102, 153, 153), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), this->ptrGame);

	this->mapButtons["BACK_POLICE"] = new TextButton(p2pX(53.0f, this->ptrGame->videoMode) + this->centre.x, p2pY(64.0f, this->ptrGame->videoMode) + this->centre.y,
		p2pX(10.0f, this->ptrGame->videoMode), p2pY(10.0f, this->ptrGame->videoMode),
		"<", calcCharSize(this->ptrGame->videoMode), sf::Color::Yellow, sf::Color(102, 153, 153), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), this->ptrGame);

	this->mapButtons["NEXT_FIRE"] = new TextButton(p2pX(67.0f, this->ptrGame->videoMode) + this->centre.x, p2pY(72.0f, this->ptrGame->videoMode) + this->centre.y,
		p2pX(10.0f, this->ptrGame->videoMode), p2pY(10.0f, this->ptrGame->videoMode),
		">", calcCharSize(this->ptrGame->videoMode), sf::Color::Yellow, sf::Color(102, 153, 153), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), this->ptrGame);

	this->mapButtons["BACK_FIRE"] = new TextButton(p2pX(53.0f, this->ptrGame->videoMode) + this->centre.x, p2pY(72.0f, this->ptrGame->videoMode) + this->centre.y,
		p2pX(10.0f, this->ptrGame->videoMode), p2pY(10.0f, this->ptrGame->videoMode),
		"<", calcCharSize(this->ptrGame->videoMode), sf::Color::Yellow, sf::Color(102, 153, 153), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), this->ptrGame);

	this->mapButtons["NEXT_HEALTH"] = new TextButton(p2pX(67.0f, this->ptrGame->videoMode) + this->centre.x, p2pY(80.0f, this->ptrGame->videoMode) + this->centre.y,
		p2pX(10.0f, this->ptrGame->videoMode), p2pY(10.0f, this->ptrGame->videoMode),
		">", calcCharSize(this->ptrGame->videoMode), sf::Color::Yellow, sf::Color(102, 153, 153), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), this->ptrGame);

	this->mapButtons["BACK_HEALTH"] = new TextButton(p2pX(53.0f, this->ptrGame->videoMode) + this->centre.x, p2pY(80.0f, this->ptrGame->videoMode) + this->centre.y,
		p2pX(10.0f, this->ptrGame->videoMode), p2pY(10.0f, this->ptrGame->videoMode),
		"<", calcCharSize(this->ptrGame->videoMode), sf::Color::Yellow, sf::Color(102, 153, 153), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), this->ptrGame);
}

void TaxesInformation::InitializeText()
{
	this->propertyTaxesText.setFont(font);
	this->propertyTaxesText.setFillColor(sf::Color::Black);
	this->propertyTaxesText.setCharacterSize(calcCharSize(this->ptrGame->videoMode, 45));
	this->propertyTaxesText.setString(std::to_string(propertyTaxesIterator) + "%");
	this->propertyTaxesText.setPosition(p2pX(65.0f, this->ptrGame->videoMode) - (this->propertyTaxesText.getGlobalBounds().width / 2.f) + this->centre.x, p2pY(46.0f, this->ptrGame->videoMode) + this->centre.y);

	this->cityOrdiancesText.setFont(font);
	this->cityOrdiancesText.setFillColor(sf::Color::Black);
	this->cityOrdiancesText.setCharacterSize(calcCharSize(this->ptrGame->videoMode, 45));
	this->cityOrdiancesText.setString(std::to_string(cityOrdiancesIterator) + "%");
	this->cityOrdiancesText.setPosition(p2pX(65.0f, this->ptrGame->videoMode) - (this->cityOrdiancesText.getGlobalBounds().width / 2.f) + this->centre.x, p2pY(54.0f, this->ptrGame->videoMode) + this->centre.y);

	this->policeDepartmentText.setFont(font);
	this->policeDepartmentText.setFillColor(sf::Color::Black);
	this->policeDepartmentText.setCharacterSize(calcCharSize(this->ptrGame->videoMode, 45));
	this->policeDepartmentText.setString(std::to_string(policeDepartmentIterator) + "%");
	this->policeDepartmentText.setPosition(p2pX(65.0f, this->ptrGame->videoMode) - (this->policeDepartmentText.getGlobalBounds().width / 2.f) + this->centre.x, p2pY(62.0f, this->ptrGame->videoMode) + this->centre.y);


	this->fireDepartmentText.setFont(font);
	this->fireDepartmentText.setFillColor(sf::Color::Black);
	this->fireDepartmentText.setCharacterSize(calcCharSize(this->ptrGame->videoMode, 45));
	this->fireDepartmentText.setString(std::to_string(fireDepartmentIterator) + "%");
	this->fireDepartmentText.setPosition(p2pX(65.0f, this->ptrGame->videoMode) - (this->fireDepartmentText.getGlobalBounds().width / 2.f) + this->centre.x, p2pY(70.0f, this->ptrGame->videoMode) + this->centre.y);


	this->healthWelfareText.setFont(font);
	this->healthWelfareText.setFillColor(sf::Color::Black);
	this->healthWelfareText.setCharacterSize(calcCharSize(this->ptrGame->videoMode, 45));
	this->healthWelfareText.setString(std::to_string(healthWelfareIterator) + "%");
	this->healthWelfareText.setPosition(p2pX(65.0f, this->ptrGame->videoMode) - (this->healthWelfareText.getGlobalBounds().width / 2.f) + this->centre.x, p2pY(78.0f, this->ptrGame->videoMode) + this->centre.y);


	this->currentTreasuryText.setFont(font);
	this->currentTreasuryText.setFillColor(sf::Color::Black);
	this->currentTreasuryText.setCharacterSize(calcCharSize(this->ptrGame->videoMode, 45));
	this->currentTreasuryText.setString("0$");
	this->currentTreasuryText.setPosition(p2pX(72.0f, this->ptrGame->videoMode) - (this->currentTreasuryText.getGlobalBounds().width / 2.f) + this->centre.x, p2pY(38.0f, this->ptrGame->videoMode) + this->centre.y);
}

void TaxesInformation::InitializeBackground()
{
	this->ptrGame->textureManager.LoadAsset("taxestable", "Resources/Textures/taxestable.png");

	this->background.setSize(sf::Vector2f(static_cast<float>(this->ptrGame->window->getSize().x),
		static_cast<float>(this->ptrGame->window->getSize().y)));
	this->background.setTexture(&this->ptrGame->textureManager.GetAsset("taxestable"));
	this->background.setPosition(this->centre.x, this->centre.y);

}

void TaxesInformation::InitializeFont()
{
	this->font.loadFromFile("Resources/Fonts/CRACKERS BRUSHER.otf");
}

void TaxesInformation::DrawTable()
{
	this->ptrGame->window->draw(this->background);

	for (auto & i : this->mapButtons)
	{
		i.second->DrawButton(this->ptrGame->window);
	}

	this->ptrGame->window->draw(this->propertyTaxesText);
	this->ptrGame->window->draw(this->cityOrdiancesText);
	this->ptrGame->window->draw(this->policeDepartmentText);
	this->ptrGame->window->draw(this->fireDepartmentText);
	this->ptrGame->window->draw(this->healthWelfareText);
	this->ptrGame->window->draw(this->currentTreasuryText);
}

void TaxesInformation::UpdateTable(float elapsedTime)
{
	for (auto & i : this->mapButtons)
	{
		i.second->UpdateButton((sf::Vector2f)this->ptrGame->mousePositionMap, elapsedTime);
	}

	if (this->mapButtons["DONE"]->GetPressed())
	{
		this->makeChanges = true;
		this->tableOpen = false;
	}

	if (this->mapButtons["CANCEL"]->GetPressed())
	{
		this->tableOpen = false;
	}

	if (this->mapButtons["NEXT_TAXES"]->GetPressed())
	{
		if (this->propertyTaxesIterator >= 100)
		{
			this->propertyTaxesIterator = 100;
		}
		else
		{
			this->propertyTaxesIterator++;
		}

		this->propertyTaxesText.setString(std::to_string(this->propertyTaxesIterator) + "%");

	}
	if (this->mapButtons["BACK_TAXES"]->GetPressed())
	{
		if (this->propertyTaxesIterator <= 0)
		{
			this->propertyTaxesIterator = 0;
		}
		else
		{
			this->propertyTaxesIterator--;
		}
		this->propertyTaxesText.setString(std::to_string(this->propertyTaxesIterator) + "%");
	}
	if (this->mapButtons["NEXT_ORDINANCES"]->GetPressed())
	{
		if (this->cityOrdiancesIterator >= 100)
		{
			this->cityOrdiancesIterator = 100;
		}
		else
		{
			this->cityOrdiancesIterator++;
		}

		this->cityOrdiancesText.setString(std::to_string(this->cityOrdiancesIterator) + "%");
	}
	if (this->mapButtons["BACK_ORDINANCES"]->GetPressed())
	{
		if (this->cityOrdiancesIterator <= 0)
		{
			this->cityOrdiancesIterator = 0;
		}
		else
		{
			this->cityOrdiancesIterator--;
		}
		this->cityOrdiancesText.setString(std::to_string(this->cityOrdiancesIterator) + "%");
	}
	if (this->mapButtons["NEXT_POLICE"]->GetPressed())
	{
		if (this->policeDepartmentIterator >= 100)
		{
			this->policeDepartmentIterator = 100;
		}
		else
		{
			this->policeDepartmentIterator++;
		}

		this->policeDepartmentText.setString(std::to_string(this->policeDepartmentIterator) + "%");
	}
	if (this->mapButtons["BACK_POLICE"]->GetPressed())
	{
		if (this->policeDepartmentIterator <= 0)
		{
			this->policeDepartmentIterator = 0;
		}
		else
		{
			this->policeDepartmentIterator--;
		}
		this->policeDepartmentText.setString(std::to_string(this->policeDepartmentIterator) + "%");
	}

	if (this->mapButtons["NEXT_FIRE"]->GetPressed())
	{
		if (this->fireDepartmentIterator >= 100)
		{
			this->fireDepartmentIterator = 100;
		}
		else
		{
			this->fireDepartmentIterator++;
		}

		this->fireDepartmentText.setString(std::to_string(this->fireDepartmentIterator) + "%");
	}

	if (this->mapButtons["BACK_FIRE"]->GetPressed())
	{
		if (this->fireDepartmentIterator <= 0)
		{
			this->fireDepartmentIterator = 0;
		}
		else
		{
			this->fireDepartmentIterator--;
		}
		this->fireDepartmentText.setString(std::to_string(this->fireDepartmentIterator) + "%");
	}

	if (this->mapButtons["NEXT_HEALTH"]->GetPressed())
	{
		if (this->healthWelfareIterator >= 100)
		{
			this->healthWelfareIterator = 100;
		}
		else
		{
			this->healthWelfareIterator++;
		}

		this->healthWelfareText.setString(std::to_string(this->healthWelfareIterator) + "%");
	}
	if (this->mapButtons["BACK_HEALTH"]->GetPressed())
	{
		if (this->healthWelfareIterator <= 0)
		{
			this->healthWelfareIterator = 0;
		}
		else
		{
			this->healthWelfareIterator--;
		}
		this->healthWelfareText.setString(std::to_string(this->healthWelfareIterator) + "%");
	}
}

#pragma endregion

#pragma region Setters

void TaxesInformation::SetVariables(int propertyTaxesIterator, int cityOrdiancesIterator, int policeDepartmentIterator,
	int fireDepartmentIterator, int healthWelfareIterator, int currentTreasury)
{
	this->propertyTaxesIterator = propertyTaxesIterator;
	this->cityOrdiancesIterator = cityOrdiancesIterator;
	this->policeDepartmentIterator = policeDepartmentIterator;
	this->fireDepartmentIterator = fireDepartmentIterator;
	this->healthWelfareIterator = healthWelfareIterator;

	this->propertyTaxesText.setString(std::to_string(propertyTaxesIterator) + "%");
	this->cityOrdiancesText.setString(std::to_string(cityOrdiancesIterator) + "%");
	this->fireDepartmentText.setString(std::to_string(fireDepartmentIterator) + "%");
	this->policeDepartmentText.setString(std::to_string(policeDepartmentIterator) + "%");
	this->healthWelfareText.setString(std::to_string(healthWelfareIterator) + "%");
	
	this->currentTreasuryText.setString(std::to_string(currentTreasury) + "$");

	this->alreadyInitializedVariables = true;
}

void TaxesInformation::SetAlreadyInitializedVariables(bool alreadyInitializedVariables)
{
	this->alreadyInitializedVariables = alreadyInitializedVariables;
}

void TaxesInformation::SetMakeChanges(bool makeChanges)
{
	this->makeChanges = makeChanges;
}

#pragma endregion

#pragma region Getters

bool TaxesInformation::GetAlreadyInitializedVariables() const
{
	return this->alreadyInitializedVariables;
}

bool TaxesInformation::GetMakeChanges() const
{
	return this->makeChanges;
}

int TaxesInformation::GetPropertyTaxesIterator() const
{
	return this->propertyTaxesIterator;
}

int TaxesInformation::GetCityOrdiancesIterator() const
{
	return this->cityOrdiancesIterator;
}

int TaxesInformation::GetPoliceDepartmentIterator() const
{
	return this->policeDepartmentIterator;
}

int TaxesInformation::GetFireDepartmentIterator() const
{
	return this->fireDepartmentIterator;
}

int TaxesInformation::GetHealthWelfareIterator() const
{
	return this->healthWelfareIterator;
}

#pragma endregion