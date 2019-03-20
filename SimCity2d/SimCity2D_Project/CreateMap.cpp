#include "CreateMap.h"

CreateMap::CreateMap(std::shared_ptr<GameAssets> ptrGame) : ptrGame(ptrGame)
{
	this->ptrGame->textureManager.LoadAsset("cross", "Resources/Textures/cross.png"); //cross
	this->ptrGame->textureManager.LoadAsset("dirt", "Resources/Textures/dirt.png"); //dirt

	this->ptrGame->textureManager.LoadAsset("create_map", "Resources/Textures/create_map.png"); //table for size and name

	
}

void CreateMap::InitGui()
{
	//init texture_table
	this->textureRect = sf::IntRect(0, 0, static_cast<int>(64), static_cast<int>(32)); //32 x 64 ground texture


	//init tabele
	this->table_rectangle.setTexture(this->ptrGame->textureManager.GetAsset("create_map"));
	this->table_rectangle.setScale(0.7f, 0.7f);

	this->table_rectangle.setPosition(this->ptrGame->window.getSize().x / 2, this->ptrGame->window.getSize().y / 2);
	this->table_rectangle.setPosition(
		this->table_rectangle.getPosition().x - (this->table_rectangle.getGlobalBounds().width / 2.0f),
		this->table_rectangle.getPosition().y - (this->table_rectangle.getGlobalBounds().height / 2.f)
	);

}

void CreateMap::InitSelector()
{
	this->selectorRect.setSize(sf::Vector2f(64, 32));
	this->selectorRect.setFillColor(sf::Color(225, 255, 255, 150));
	this->selectorRect.setOutlineThickness(1.0f);
	this->selectorRect.setOutlineColor(sf::Color::Green);

	this->selectorRect.setTexture(&this->ptrGame->textureManager.GetAsset("dirt"));
	this->selectorRect.setTextureRect(this->textureRect);
	this->selectTexture = new Gui::SelectTexture(0.0f, 0.0f, 4 * 64.0f, 4 * 32.0f, 64.0f, 32.0f, &this->ptrGame->textureManager.GetAsset("dirt"), this->font, "TEST");
}

void CreateMap::InitButtons()
{
	this->buttons["NEXT"] = new Gui::Button(
		this->ptrGame->window.getSize().x / 2 - 225, this->ptrGame->window.getSize().y / 2 - 250, 250.f, 50.f,
		&this->font, "NEXT", 50,
		sf::Color(70, 255, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["BACK"] = new Gui::Button(
		this->ptrGame->window.getSize().x / 2 - 25, this->ptrGame->window.getSize().y / 2 - 250, 250.f, 50.f,
		&this->font, "BACK", 50,
		sf::Color(70, 255, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["OK"] = new Gui::Button(
		this->ptrGame->window.getSize().x / 2 - 125, this->ptrGame->window.getSize().y / 2 + 150, 250.f, 50.f,
		&this->font, "OK", 50,
		sf::Color(70, 255, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
}

void CreateMap::InitFonts()
{
	this->font.loadFromFile("Resources/Font/Delimax.ttf"); //init FONT!

	this->cursorText.setFont(font); //----------- cursor x y
	this->cursorText.setFillColor(sf::Color::White);
	this->cursorText.setCharacterSize(10);
	this->cursorText.setPosition(this->ptrGame->mousePosView.x, this->ptrGame->mousePosView.y);

	nameText.setFont(font);
	nameText.setPosition(this->ptrGame->window.getSize().x / 2 - (this->nameText.getGlobalBounds().width / 2.f), this->ptrGame->window.getSize().y / 2 + 75);

	sizeMapText.setFont(font);
	sizeMapText.setString(std::to_string(sizeMap[sizeMapIterator]));
	sizeMapText.setPosition(this->ptrGame->window.getSize().x / 2 - (this->sizeMapText.getGlobalBounds().width / 2.f), this->ptrGame->window.getSize().y / 2 - 65);
}

void CreateMap::InitializeObject()
{
	//init textures
	this->ptrGame->tile_map["dirt"] =
		Plate(32, 1, this->ptrGame->textureManager.GetAsset("dirt"), TypeOfTile::DIRT, 50, 0, 1);
	this->ptrGame->tile_map["cross"] =
		Plate(32, 1, this->ptrGame->textureManager.GetAsset("cross"), TypeOfTile::DIRT, 50, 0, 1);

	this->plate = &this->ptrGame->tile_map.at("cross"); //something in array must be!
	this->InitFonts();
	this->InitGui();
	this->InitButtons();

	this->InitSelector();


}

void CreateMap::HoldInput()
{
	sf::Event event;

	while (this->ptrGame->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			this->ptrGame->window.close();

		if (created == true)
		{

			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				oldMousePos = newMousePos;
				newMousePos = sf::Mouse::getPosition(this->ptrGame->window);
				camera.move(newMousePos.x - oldMousePos.x, newMousePos.y - oldMousePos.y);
			}

			if (event.type == sf::Event::MouseWheelScrolled)
				if (event.mouseWheelScroll.delta > 0)
					zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, this->ptrGame->window, (1.f / zoomAmount));
				else if (event.mouseWheelScroll.delta < 0)
					zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, this->ptrGame->window, zoomAmount);

			if (event.type == sf::Event::MouseMoved)
			{
				if (mouseEvent == MouseEvents::SELECT)
				{
					sf::Vector2f pos = this->ptrGame->window.mapPixelToCoords(sf::Mouse::getPosition(this->ptrGame->window), this->camera);
					selectTO.x = pos.y / (this->map.tileSize) + pos.x / (2 * this->map.tileSize) - this->map.width * 0.5 - 0.5;
					selectTO.y = pos.y / (this->map.tileSize) - pos.x / (2 * this->map.tileSize) + this->map.width * 0.5 + 0.5;

					this->map.Deselect();
					if (this->plate->_typeOfTile == TypeOfTile::CROSS)
					{
						this->map.Select(selectFROM, selectTO, { this->plate->_typeOfTile, TypeOfTile::DIRT });
					}
					else
					{
						this->map.Select(selectFROM, selectTO,
							{
								this->plate->_typeOfTile,   TypeOfTile::DIRT,
								TypeOfTile::NOTHING,                TypeOfTile::CROSS,
								TypeOfTile::HOUSES,        TypeOfTile::SHOPS,
								TypeOfTile::FACTORY
							});
					}

				}



			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (this->mouseEvent != MouseEvents::SELECT)
				{
					this->mouseEvent = MouseEvents::SELECT;
					sf::Vector2f pos = this->ptrGame->window.mapPixelToCoords(sf::Mouse::getPosition(this->ptrGame->window), this->camera);
					selectFROM.x = pos.y / (this->map.tileSize) + pos.x / (2 * this->map.tileSize) - this->map.width * 0.5 - 0.5;
					selectFROM.y = pos.y / (this->map.tileSize) - pos.x / (2 * this->map.tileSize) + this->map.width * 0.5 + 0.5;
				}
			}
			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (this->mouseEvent == MouseEvents::SELECT)
					{
						this->mouseEvent = MouseEvents::VOID;
						this->map.Deselect();
					}
				}
			}

			//hushfiuwehrgiuhgierhgiwjerjgwergoi4jhit
			if (!this->selectTexture->getActive())
			{

			}
		}

	}


	if (event.type == sf::Event::TextEntered)
	{
		if (event.text.unicode == '\b' && nameMapV.size() != 0)
		{
			nameMapV.pop_back();
			std::string s(nameMapV.begin(), nameMapV.end());
			nameText.setString(s);
			nameMap = s;
		}
		else if (((event.text.unicode >= 97 && event.text.unicode <= 122) || (event.text.unicode >= 48 && event.text.unicode <= 57) || (event.text.unicode >= 65 && event.text.unicode <= 90)) && nameMapV.size() < 12)
		{
			nameMapV.push_back((char)event.text.unicode);
			std::string s(nameMapV.begin(), nameMapV.end());
			nameText.setString(s);
			nameMap = s;
		}
		if (event.text.unicode == 13 && created == false)
		{
			CreateTilesToEdit(nameMap, sizeMap[sizeMapIterator]);
		}

	}


	if (this->buttons["NEXT"]->isPressed())
	{

		if (sizeMapIterator == 4)
		{
			sizeMapIterator = 0;
		}
		else
		{
			sizeMapIterator++;
		}

		sizeMapText.setString(std::to_string(sizeMap[sizeMapIterator]));
	}

	if (this->buttons["BACK"]->isPressed())
	{
		if (sizeMapIterator == 0)
		{
			sizeMapIterator = 4;
		}
		else
		{
			sizeMapIterator--;
		}
		sizeMapText.setString(std::to_string(sizeMap[sizeMapIterator]));
	}

	if (this->buttons["OK"]->isPressed())
	{
		created = true;
		CreateTilesToEdit(nameMap, sizeMap[sizeMapIterator]);
	}
}


void CreateMap::UpdateObject(float deltaTime)
{
	this->selectTexture->Update(this->ptrGame->mousePosWindow, deltaTime);
	if (!this->selectTexture->getActive())
	{
		this->selectorRect.setTextureRect(this->textureRect);
		this->selectorRect.setPosition(this->ptrGame->mousePosGrid.x * 64, this->ptrGame->mousePosGrid.y * 32);
	}

	this->cursorText.setPosition(this->ptrGame->mousePosView.x, this->ptrGame->mousePosView.y);
	std::stringstream ss;
	ss << this->ptrGame->mousePosView.x << " " << this->ptrGame->mousePosView.y <<
		"\n" << this->ptrGame->mousePosGrid.x << " " << this->ptrGame->mousePosGrid.y <<
		"\n" << this->textureRect.left << " " << this->textureRect.top;
	this->cursorText.setString(ss.str());

	//--------------------------
	sizeMapText.setPosition(this->ptrGame->window.getSize().x / 2 - (this->sizeMapText.getGlobalBounds().width / 2.f), this->ptrGame->window.getSize().y / 2 - 65);
	nameText.setPosition(this->ptrGame->window.getSize().x / 2 - (this->nameText.getGlobalBounds().width / 2.f), this->ptrGame->window.getSize().y / 2 + 75);
	for (auto &it : this->buttons)
	{
		it.second->update(this->ptrGame->mousePosView);
	}
}

void CreateMap::DrawObject(float deltaTime)
{
	if (!this->selectTexture->getActive())
		this->ptrGame->window.draw(this->selectorRect);

	this->ptrGame->window.draw(this->cursorText);

	if (created == true)
		this->map.Draw(this->ptrGame->window, deltaTime);

	if (created == false)
		this->ptrGame->window.draw(this->table_rectangle);

	if (created == true)
		this->ptrGame->window.draw(this->selectorRect);

	if (created == true)
		this->selectTexture->Draw(this->ptrGame->window);

	if (created == false)
		this->ptrGame->window.draw(nameText);

	if (created == true)
		this->ptrGame->window.setView(this->camera);

	if (created == false)
		this->DrawButtons();

	if (created == false)
		this->ptrGame->window.draw(sizeMapText);

}

void CreateMap::DrawButtons()
{
	for (auto &it : this->buttons)
	{
		it.second->render(ptrGame->window);
	}
}

void CreateMap::CreateTilesToEdit(const std::string & filename, int how_length)
{

	map = MapTile(how_length, filename, ptrGame->tile_map, ptrGame);

	center = sf::Vector2f(this->map.width, this->map.height*0.5);
	center *= float(this->map.tileSize);
	camera.setCenter(center);

	created = true;
}

void CreateMap::zoomViewAt(sf::Vector2i pixel, sf::RenderWindow& window, float zoom)
{
	const sf::Vector2f beforeCoord{ window.mapPixelToCoords(pixel) };
	camera.zoom(zoom);
	window.setView(camera);
	const sf::Vector2f afterCoord{ window.mapPixelToCoords(pixel) };
	const sf::Vector2f offsetCoords{ beforeCoord - afterCoord };
	camera.move(offsetCoords);
	window.setView(camera);
}

CreateMap::~CreateMap()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}