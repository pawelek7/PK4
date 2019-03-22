#include "Gui.h"


sf::Vector2f Gui::GameGui::getSize()
{
	return sf::Vector2f(this->dimensions.x, this->dimensions.y * this->entries.size());
}

int Gui::GameGui::getEntry(const sf::Vector2f mousePos)
{
	if (entries.size() == 0)
		return -1;

	if (!visible)
		return -1;

	for (int i = 0; i < this->entries.size(); i++)
	{
		sf::Vector2f point = mousePos;
		point += this->entries[i].shape.getOrigin();
		point -= this->entries[i].shape.getPosition();

		if (point.x < 0 || point.x > this->entries[i].shape.getScale().x*this->dimensions.x)
			continue;
		if (point.y < 0 || point.y > this->entries[i].shape.getScale().y*this->dimensions.y) 
			continue;

		return i;
	}
	return -1;
}

void Gui::GameGui::setEntryText(int entry, std::string text)
{
	if (entry >= entries.size() || entry < 0)
		return;

	entries[entry].text.setString(text);

	return;
}

void Gui::GameGui::setDimenstions(sf::Vector2f dimensions)
{
	this->dimensions = dimensions;

	for (auto& entry : entries)
	{
		entry.shape.setSize(dimensions);
		entry.text.setCharacterSize(dimensions.y - style.borderSize - padding);
	}

	return;
}

void Gui::GameGui::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (!visible)
		return;

	for (auto entry : this->entries)
	{
		target.draw(entry.shape);
		target.draw(entry.text);

	}
	return;
}

void Gui::GameGui::schow()
{
	sf::Vector2f offset(0.0f, 0.0f);

	this->visible = true;

	for (auto& entry : this->entries)
	{
		/* Set the origin of the entry. */
		sf::Vector2f origin = this->getOrigin();
		origin -= offset;
		entry.shape.setOrigin(origin);
		entry.text.setOrigin(origin);

		/* Compute the position of the entry. */
		entry.shape.setPosition(this->getPosition());
		entry.text.setPosition(this->getPosition());

		//if (this->horizontal) offset.x += this->dimensions.x;
	//	else offset.y += this->dimensions.y;
	}

	return;
}

void Gui::GameGui::hide()
{
	this->visible = false;

		return;
}

void Gui::GameGui::highlight(const int entry)
{
	for (int i = 0; i < entries.size(); ++i)
	{
		if (i == entry)
		{
			entries[i].shape.setFillColor(style.bodyHighlightCol);
			entries[i].shape.setOutlineColor(style.borderHighlightCol);
			entries[i].text.setFillColor(style.textHighlightCol);
		}
		else
		{
			entries[i].shape.setFillColor(style.bodyCol);
			entries[i].shape.setOutlineColor(style.borderCol);
			entries[i].text.setFillColor(style.textCol);
		}
	}

	return;
}

std::string Gui::GameGui::activate(const int entry)
{
	if (entry == -1) return "null";
	return entries[entry].message;
}

std::string Gui::GameGui::activate(sf::Vector2f mousePos)
{
	int entry = this->getEntry(mousePos);
	return this->activate(entry);
}

//---------------------------------------------

Gui::Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text, unsigned character_size,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
	sf::Color outline_idle_color, sf::Color outline_hover_color, sf::Color outline_active_color,
	short unsigned id)
{
	this->buttonState = StateOfButton::BTN_IDLE;
	this->buttonID = id;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(idle_color);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(outline_idle_color);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(text_idle_color);
	this->text.setCharacterSize(character_size);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
	);

	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_active_color;

	this->idleColor = idle_color;
	this->hoverColor = hover_color;
	this->activeColor = active_color;

	this->outlineIdleColor = outline_idle_color;
	this->outlineHoverColor = outline_hover_color;
	this->outlineActiveColor = outline_active_color;
}

void Gui::Button::ChangePosition(float x, float y)
{
	this->shape.setPosition(sf::Vector2f(x, y));
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
	);
}

const bool Gui::Button::isPressed() const
{
	if (this->buttonState == StateOfButton::BTN_ACTIVE)
		return true;

	return false;
}

const std::string Gui::Button::getText() const
{
	return this->text.getString();
}

const short unsigned & Gui::Button::getId() const
{
	return this->buttonID;
}


void Gui::Button::setText(const std::string text)
{
	this->text.setString(text);
}

void Gui::Button::setId(const short unsigned id)
{
	this->buttonID = id;
}


void Gui::Button::update(const sf::Vector2f& mousePos)
{
	//idle
	this->buttonState = StateOfButton::BTN_IDLE;

	//Hover
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = StateOfButton::BTN_HOVER;

		//Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = StateOfButton::BTN_ACTIVE;
		}
	}

	switch (this->buttonState)
	{
	case StateOfButton::BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		this->text.setFillColor(this->textIdleColor);
		this->shape.setOutlineColor(this->outlineIdleColor);
		break;

	case StateOfButton::BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);
		this->shape.setOutlineColor(this->outlineHoverColor);
		break;

	case StateOfButton::BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->textActiveColor);
		this->shape.setOutlineColor(this->outlineActiveColor);
		break;

	default:
		this->shape.setFillColor(sf::Color::Red);
		this->text.setFillColor(sf::Color::Blue);
		this->shape.setOutlineColor(sf::Color::Green);
		break;
	}
}

void Gui::Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}

//DROP DOWN LIST =============================================

Gui::DropDownList::DropDownList(float x, float y, float width, float height,
	sf::Font& font, std::string list[],
	unsigned nrOfElements, unsigned default_index)
	: font(font), showList(false), keytimeMax(1.f), keytime(0.f)
{
	//unsigned nrOfElements = sizeof(list) / sizeof(std::string);

	this->activeElement = new Gui::Button(
		x, y, width, height,
		&this->font, list[default_index], 14,
		sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 200), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50)
	);

	for (size_t i = 0; i < nrOfElements; i++)
	{
		this->list.push_back(
			new Gui::Button(
				x, y + ((i + 1) * height), width, height,
				&this->font, list[i], 14,
				sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
				sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
				sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0), sf::Color(20, 20, 20, 0),
				i
			)
		);
	}
}

Gui::DropDownList::~DropDownList()
{
	delete this->activeElement;
	for (size_t i = 0; i < this->list.size(); i++)
	{
		delete this->list[i];
	}
}

//Accessors
const bool Gui::DropDownList::getKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}

	return false;
}

const unsigned short & Gui::DropDownList::getActiveElementId() const
{
	return this->activeElement->getId();
}

//Functions
void Gui::DropDownList::UpdateKeytime(const float& dt)
{
	if (this->keytime < this->keytimeMax)
		this->keytime += 10.f * dt;
}

void Gui::DropDownList::Update(const sf::Vector2f & mousePos, const float& dt)
{
	this->UpdateKeytime(dt);

	this->activeElement->update(mousePos);

	//Show and hide the list
	if (this->activeElement->isPressed() && this->getKeytime())
	{
		if (this->showList)
			this->showList = false;
		else
			this->showList = true;
	}

	if (this->showList)
	{
		for (auto &i : this->list)
		{
			i->update(mousePos);

			if (i->isPressed() && this->getKeytime())
			{
				this->showList = false;
				this->activeElement->setText(i->getText());
				this->activeElement->setId(i->getId());
			}
		}
	}
}

void Gui::DropDownList::Draw(sf::RenderTarget & target)
{
	this->activeElement->render(target);

	if (this->showList)
	{
		for (auto &i : this->list)
		{
			i->render(target);
		}
	}
}

Gui::SelectTexture::SelectTexture(float x, float y, float width, float height, float sizeX, float sizeY, const sf::Texture *texture_sheet,
sf::Font & font, std::string text)
{
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	this->active = false;

	this->bounds.setSize(sf::Vector2f(width, height));
	this->bounds.setPosition(x, y);
	this->bounds.setFillColor(sf::Color(50, 50, 50, 100));
	this->bounds.setOutlineThickness(1.0f);
	this->bounds.setOutlineColor(sf::Color(255, 255, 255, 200));

	this->sheet.setTexture(*texture_sheet);
	this->sheet.setPosition(x, y);

	if (this->sheet.getGlobalBounds().width > this->bounds.getGlobalBounds().width)
	{
		this->sheet.setTextureRect(sf::IntRect(0, 0, this->bounds.getGlobalBounds().width, this->sheet.getGlobalBounds().height));
	}
	if (this->sheet.getGlobalBounds().height > this->bounds.getGlobalBounds().height)
	{
		this->sheet.setTextureRect(sf::IntRect(0, 0, this->sheet.getGlobalBounds().width, this->bounds.getGlobalBounds().height));
	}

	this->selector.setPosition(x, y);
	this->selector.setSize(sf::Vector2f(sizeX, sizeY));
	this->selector.setFillColor(sf::Color::Transparent);
	this->selector.setOutlineThickness(1.0f);
	this->selector.setOutlineColor(sf::Color::Red);

	this->textureRect.width = static_cast<int>(sizeX);
	this->textureRect.height = static_cast<int>(sizeY);

	this->hide_btn = new Gui::Button(
		y, x, 50.f, 50.f,
		&font, text, 30,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
}

Gui::SelectTexture::~SelectTexture()
{
	delete this->hide_btn;
}

const bool& Gui::SelectTexture::getActive() const
{
	return this->active;
}

const bool Gui::SelectTexture::getKeyTime()
{
	if (this->keyTime >= this->keyTimeMax)
	{
		this->keyTime = 0.f;
		return true;
	}

	return false;
}

void Gui::SelectTexture::UpdateKeyTime(const float& dt)
{
	if (this->keyTime < this->keyTimeMax)
		this->keyTime += 10.f * dt;
}

void Gui::SelectTexture::Update(const sf::Vector2i & mousePosWindow, const float& dt)
{
	this->UpdateKeyTime(dt);
	this->hide_btn->update(static_cast<sf::Vector2f>(mousePosWindow));

	if (this->hide_btn->isPressed() && this->getKeyTime())
	{
		if (this->hidden)
			this->hidden = false;
		else
			this->hidden = true;
	}

	if (!this->hidden)
	{
		if (this->bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
			this->active = true;
		else
			this->active = false;

		if (this->active)
		{
			this->mousePosGrid.x = (mousePosWindow.x - static_cast<int>(this->bounds.getPosition().x)) / static_cast<unsigned>(this->sizeX);
			this->mousePosGrid.y = (mousePosWindow.y - static_cast<int>(this->bounds.getPosition().y)) / static_cast<unsigned>(this->sizeY);

			this->selector.setPosition(
				this->bounds.getPosition().x + this->mousePosGrid.x * this->sizeX,
				this->bounds.getPosition().y + this->mousePosGrid.y * this->sizeY
			);

			//Update texture rectangle
			this->textureRect.left = static_cast<int>(this->selector.getPosition().x - this->bounds.getPosition().x);
			this->textureRect.top = static_cast<int>(this->selector.getPosition().y - this->bounds.getPosition().y);
		}
	}
}

const sf::IntRect & Gui::SelectTexture::getTextureRect() const
{
	return this->textureRect;
}

void Gui::SelectTexture::Draw(sf::RenderTarget & target)
{
	if (!this->hidden)
	{
		target.draw(this->bounds);
		target.draw(this->sheet);

		if (this->active)
		{
			target.draw(this->selector);
		}
	}
	this->hide_btn->render(target);
}