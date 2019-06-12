#include "DropList.h"

#pragma region Constructors

DropList::DropList(float x, float y, float width, float height, int characterSize, std::string text,
	sf::Font& font, std::string list[], std::shared_ptr<AssetsOfGame> ptrGame, 
	unsigned nrOfElements, unsigned default_index)
	: font(font)
{
	this->activatedElement = new TextButton(
		x, y, width, height, text,
		characterSize,
		sf::Color::White, sf::Color(128, 128, 128), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
		ptrGame, false,
		default_index,
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50)
	);

	for (unsigned i = 0; i < nrOfElements; i++)
	{
		this->list.push_back(
			new TextButton(
				x, y + ((i + 1) * height), width, height,
				list[i], characterSize,
				sf::Color::White, sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
				sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
				ptrGame, true,
				i,
				sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0), sf::Color(20, 20, 20, 0)
			)
		);
	}
}

DropList::~DropList()
{
	if (this->activatedElement != nullptr)
	{
		delete this->activatedElement;
		this->activatedElement = nullptr;
	}

	for (size_t i = 0; i < this->list.size(); i++)
	{
		if (this->list[i] != nullptr)
		{
			delete this->list[i];
			this->list[i] = nullptr;
		}
	}
}

#pragma endregion

#pragma region Class_Methods

void DropList::UpdateKeyTime(const float & elapsedTime)
{
	if (this->keyTime < this->keyTimeMax)
	{
		this->keyTime += 10.0f * elapsedTime;
	}
}

void DropList::Update(const sf::Vector2f& mousePosition, const float & elapsedTime)
{
	this->mouseOnList = false;
	this->UpdateKeyTime(elapsedTime);
	this->activatedElement->UpdateButton(mousePosition, elapsedTime);

	if (activatedElement->GetMouseOnButton())
	{
		this->mouseOnList = true;
	}

	if(this->activatedElement->GetPressed() && this->GetKeyTime())
	{
		if (this->showList)
		{
			this->showList = false;
		}
		else
		{
			this->showList = true;
		}
	}

	if (this->showList)
	{
		for (auto &i : this->list)
		{
			i->UpdateButton(mousePosition, elapsedTime);

			if (i->GetMouseOnButton())
			{
				this->mouseOnList = true;
			}

			if (i->GetPressed() && this->GetKeyTime())
			{
				this->showList = false;
				this->activatedElement->SetID(i->GetID());
				this->clickedElement = true;
			}
		}
	}
}

void DropList::Draw(sf::RenderTarget *renderTarget) 
{
	this->activatedElement->DrawButton(renderTarget);

	if (this->showList)
	{
		for (auto &i : this->list)
		{
			i->DrawButton(renderTarget);
		}
	}
}

#pragma endregion

#pragma region Setters
//setters

void DropList::SetClickedElement(bool clicked)
{
	this->clickedElement = clicked;
}

#pragma endregion

#pragma region Getters
//getetrs

const unsigned short & DropList::getActiveElementID() const
{
	return this->activatedElement->GetID();
}

const bool DropList::GetKeyTime()
{
	if (this->keyTime >= this->keyTimeMax)
	{
		this->keyTime = 0.0f;
		return true;
	}
	return false;
}

bool DropList::GetShowList() const
{
	return this->showList;
}

bool DropList::GetIsMouseOnList() const
{
	return this->mouseOnList;
}

bool DropList::GetIsClickedElement() const
{
	return this->clickedElement;
}

#pragma endregion