#include "HudUp.h"

#pragma region Constructors

HudUp::HudUp(sf::Texture & textureHUD, sf::Texture & iconsHud, float windowSizeX, float windowSizeY,
	float x, float y, float width, float height, sf::Font & font, std::shared_ptr<AssetsOfGame> ptrGame, sf::VideoMode & vm, unsigned int index) :font(font)
{
	this->x = x;
	this->y = y;
	this->windowSizeX = windowSizeX;
	this->windowSizeY = windowSizeY;

	this->rectangleHUD.setSize(sf::Vector2f(static_cast<float>(windowSizeX),
		static_cast<float>(windowSizeY)));
	this->rectangleHUD.setTexture(&textureHUD);
	this->rectangleHUD.setPosition(sf::Vector2f(x, y));

	this->dateText.setFont(font);
	this->dateText.setString("Day 0 January Year 0");
	this->dateText.setCharacterSize(calcCharSize(vm));
	this->dateText.setFillColor(sf::Color::Black);
	this->dateText.setPosition(p2pX(5, vm)+ x, y + p2pY(7.0f, vm));

	this->moneyText.setFont(font);
	this->moneyText.setString("0$");
	this->moneyText.setCharacterSize(calcCharSize(vm));
	this->moneyText.setFillColor(sf::Color::Black);
	this->moneyText.setPosition(p2pX(35, vm) + x , y + p2pY(7.0f, vm));

	this->decreateMoneyText.setFont(font);
	this->decreateMoneyText.setString("0$");
	this->decreateMoneyText.setCharacterSize(calcCharSize(vm));
	this->decreateMoneyText.setFillColor(sf::Color::Red);
	this->decreateMoneyText.setPosition(p2pX(45, vm) + x, y + p2pY(7.0f, vm));

	this->populationText.setFont(font);
	this->populationText.setString("Population: 0");
	this->populationText.setCharacterSize(calcCharSize(vm));
	this->populationText.setPosition(p2pX(55, vm) + x, y + p2pY(7.0f, vm));
	this->populationText.setFillColor(sf::Color::Black);

	std::string file[5] = { "Save", "Load", "Pause", "Menu", "Exit" };
	std::string speed[4] = { "Slow", "Normal", "Fast", "Uber" };
	std::string view[3] = { "Short", "Medium", "Long" };
	std::string disasters[4] = { "Cyclone", "Meteorite", "Epidemic", "Fire" };
	std::string statistics[1] = { "Info" };
	std::string newspaper[2] = { "Newest"};

	this->dropList["FILE"] = new DropList((windowSizeX * (0 * width)) / 1000.0f + x, y + p2pY(1.0f, vm), p2pX(15.0f, vm), p2pY(5.0f, vm),
		calcCharSize(vm) / 1.3f, "FILE",
		font, file, ptrGame, 5);
	this->dropList["SPEED"] = new DropList((windowSizeX * (1 * width)) / 1000.0f + x, y + p2pY(1.0f, vm), p2pX(15.0f, vm), p2pY(5.0f, vm),
		calcCharSize(vm) / 1.3f, "SPEED",
		font, speed, ptrGame, 4);
	this->dropList["VIEW"] = new DropList((windowSizeX * (2 * width)) / 1000.0f + x, y + p2pY(1.0f, vm), p2pX(15.0f, vm), p2pY(5.0f, vm),
		calcCharSize(vm) / 1.3f, "VIEW",
		font, view, ptrGame, 3);
	this->dropList["NATURAL"] = new DropList((windowSizeX * (3 * width)) / 1000.0f + x, y + p2pY(1.0f, vm), p2pX(15.0f, vm), p2pY(5.0f, vm),
		calcCharSize(vm) / 1.3f, "NATURAL",
		font, disasters, ptrGame, 4);
	this->dropList["PROBE"] = new DropList((windowSizeX * (4 * width)) / 1000.0f + x, y + p2pY(1.0f, vm), p2pX(15.0f, vm), p2pY(5.0f, vm),
		calcCharSize(vm) / 1.3f, "PROBE",
		font, statistics, ptrGame, 1);
	this->dropList["DAILY"] = new DropList((windowSizeX * (5 * width)) / 1000.0f + x, y + p2pY(1.0f, vm), p2pX(15.0f, vm), p2pY(5.0f, vm),
		calcCharSize(vm) / 1.3f, "DAILY",
		font, newspaper, ptrGame, 1);
}

HudUp::~HudUp()
{
	for (int i = 0; i < this->buttons.size(); i++)
	{
		if (this->buttons[i] != nullptr)
		{
			delete this->buttons[i];
			this->buttons[i] = nullptr;
		}
	}

	for (auto i = this->dropList.begin(); i != this->dropList.end(); i++)
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

void HudUp::UpdateHUD(const sf::Vector2i & mousePosition, const float & elapsedTime)
{
	this->cursorOnHudUp = false;
	for (auto & i : this->dropList)
	{
		i.second->Update((sf::Vector2f)mousePosition, elapsedTime);

		if (i.second->GetIsMouseOnList())
		{
			this->cursorOnHudUp = true;
		}
	}

	if (this->dropList["FILE"]->GetIsClickedElement())
	{
		switch (this->dropList["FILE"]->getActiveElementID())
		{
		case 0:
			this->clickedOption = "Save";
			break;
		case 1:
			this->clickedOption = "Load";
			break;
		case 2:
			this->clickedOption = "Pause";
			break;
		case 3:
			this->clickedOption = "Menu";
			break;
		case 4:
			this->clickedOption = "Exit";
			break;
		default:
			this->clickedOption = "unknown";
			break;
		}
		this->readySelectedOption = true;
		this->dropList["FILE"]->SetClickedElement(false);
	}
	else if(this->dropList["SPEED"]->GetIsClickedElement())
	{
		switch (this->dropList["SPEED"]->getActiveElementID())
		{
		case 0:
			this->clickedOption = "Slow";
			break;
		case 1:
			this->clickedOption = "Normal";
			break;
		case 2:
			this->clickedOption = "Fast";
			break;
		case 3:
			this->clickedOption = "Uber";
			break;
		default:
			this->clickedOption = "unknown";
			break;
		}
		this->readySelectedOption = true;
		this->dropList["SPEED"]->SetClickedElement(false);
	}
	else if (this->dropList["VIEW"]->GetIsClickedElement())
	{
		switch (this->dropList["VIEW"]->getActiveElementID())
		{
		case 0:
			this->clickedOption = "Short";
			break;
		case 1:
			this->clickedOption = "Medium";
			break;
		case 2:
			this->clickedOption = "Long";
			break;
		default:
			this->clickedOption = "unknown";
			break;
		}
		this->readySelectedOption = true;
		this->dropList["VIEW"]->SetClickedElement(false);
	}
	else if (this->dropList["NATURAL"]->GetIsClickedElement())
	{
		switch (this->dropList["NATURAL"]->getActiveElementID())
		{
		case 0:
			this->clickedOption = "Cyclone";
			break;
		case 1:
			this->clickedOption = "Meteorite";
			break;
		case 2:
			this->clickedOption = "Epidemic";
			break;
		case 3:
			this->clickedOption = "Fire";
			break;
		default:
			this->clickedOption = "unknown";
			break;
		}
		this->readySelectedOption = true;
		this->dropList["NATURAL"]->SetClickedElement(false);
	}
	else if (this->dropList["PROBE"]->GetIsClickedElement())
	{
		switch (this->dropList["PROBE"]->getActiveElementID())
		{
		case 0:
			this->clickedOption = "Info";
			break;
		default:
			this->clickedOption = "unknown";
			break;
		}
		this->readySelectedOption = true;
		this->dropList["PROBE"]->SetClickedElement(false);
	}
	else if (this->dropList["DAILY"]->GetIsClickedElement())
	{
		switch (this->dropList["DAILY"]->getActiveElementID())
		{
		case 0:
			this->clickedOption = "Newest";
			break;
		default:
			this->clickedOption = "unknown";
			break;
		}
		this->readySelectedOption = true;
		this->dropList["DAILY"]->SetClickedElement(false);
	}
}

void HudUp::DrawHUD(sf::RenderTarget  *renderTarget)
{
	renderTarget->draw(rectangleHUD);

	if (this->drawDecreaseText == true)
	{
		renderTarget->draw(this->decreateMoneyText);
	}

	renderTarget->draw(this->dateText);
	renderTarget->draw(this->moneyText);
	renderTarget->draw(this->populationText);

	for (auto & i : this->dropList)
	{
		i.second->Draw(renderTarget);
	}
}

void HudUp::UpdateDate(const std::string & date)
{
	this->dateText.setString(date);
}

void HudUp::UpdateMoneyAmount(int money)
{
	this->moneyText.setString(std::to_string(money) + '$');
}

void HudUp::isDrawDecreaseMoney(bool option)
{
	this->drawDecreaseText = option;
}

#pragma endregion

#pragma region Setters

void HudUp::SetDecreaseMoneyText(int decreaseMoney)
{
	this->decreateMoneyText.setString('-' + std::to_string(decreaseMoney) + '$');
}

void HudUp::SetPopulationText(int population)
{
	this->populationText.setString("Population: " + std::to_string(population));
}

#pragma endregion

#pragma region Getters

bool HudUp::GetCursorOnHudUp()
{
	return this->cursorOnHudUp;
}

std::string HudUp::GetClickedOption()
{
	return this->clickedOption;
}

bool HudUp::GetIsReadySelectedOption()
{
	if (readySelectedOption == true)
	{
		readySelectedOption = false;
		return true;
	}
	return false;
}
#pragma endregion