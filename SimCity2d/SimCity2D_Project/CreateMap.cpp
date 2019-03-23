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


	/* Create gui elements. */
	this->guiSystem.emplace("rightClickMenu", Gui::GameGui(sf::Vector2f(196, 16), 2, false, this->ptrGame->stylesGuis.at("button"),
		{
			std::make_pair("Flatten $" + this->ptrGame->tile_map["grass"].getCost(),         "grass"),
			std::make_pair("Forest $" + this->ptrGame->tile_map["forest"].getCost(),        "forest"),
			std::make_pair("Residential Zone $" + this->ptrGame->tile_map["residential"].getCost(),   "residential"),
			std::make_pair("Commercial Zone $" + this->ptrGame->tile_map["commercial"].getCost(),    "commercial"),
			std::make_pair("Industrial Zone $" + this->ptrGame->tile_map["industrial"].getCost(),    "industrial"),
			std::make_pair("Road $" + this->ptrGame->tile_map["road"].getCost(),          "road")
		}));

	this->guiSystem.emplace("selectionCostText", Gui::GameGui(sf::Vector2f(196, 16), 0, false, this->ptrGame->stylesGuis.at("text"),
		{ std::make_pair("", "") }));

	this->guiSystem.emplace("infoBar", Gui::GameGui(sf::Vector2f(this->ptrGame->window.getSize().x / 5, 16), 2, true, this->ptrGame->stylesGuis.at("button"),
		{
			std::make_pair("time",          "time"),
			std::make_pair("funds",         "funds"),
			std::make_pair("population",    "population"),
			std::make_pair("employment",    "employment"),
			std::make_pair("current tile",  "tile")
		}));
	this->guiSystem.at("infoBar").setPosition(sf::Vector2f(0, this->ptrGame->window.getSize().y - 16));
	this->guiSystem.at("infoBar").schow();

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

	sf::Vector2f guiPos = this->ptrGame->window.mapPixelToCoords(sf::Mouse::getPosition(this->ptrGame->window),
		this->guiView);

	while (this->ptrGame->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			this->ptrGame->window.close();

		if (created == true)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				this->ptrGame->cameraGame.move(0, 10);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				this->ptrGame->cameraGame.move(10, 0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				this->ptrGame->cameraGame.move(-10, 0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				this->ptrGame->cameraGame.move(0, -10);
			}

			/*
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				oldMousePos = newMousePos;
				newMousePos = sf::Mouse::getPosition(this->ptrGame->window);
				this->ptrGame->cameraGame.move(newMousePos.x - oldMousePos.x, newMousePos.y - oldMousePos.y);
			}
			*/
			if (event.type == sf::Event::MouseWheelScrolled)
				if (event.mouseWheelScroll.delta > 0)
					zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, this->ptrGame->window, (1.f / zoomAmount));
				else if (event.mouseWheelScroll.delta < 0)
					zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, this->ptrGame->window, zoomAmount);

			if (event.type == sf::Event::MouseMoved)
			{
				if (mouseEvent == MouseEvents::SELECT)
				{
					sf::Vector2f pos = this->ptrGame->window.mapPixelToCoords(sf::Mouse::getPosition(this->ptrGame->window), this->ptrGame->cameraGame);
					selectTO.x = pos.y / (this->map.tileSize) + pos.x / (2 * this->map.tileSize) - this->map.width * 0.5 - 0.5;
					selectTO.y = pos.y / (this->map.tileSize) - pos.x / (2 * this->map.tileSize) + this->map.width * 0.5 + 0.5;

					this->map.Deselect();
					if (this->plate->_typeOfTile == TypeOfTile::CROSS)
					{
						this->map.Select(selectFROM, selectTO, { this->plate->_typeOfTile, TypeOfTile::DIRT });
					}
					else
					{
						this->city.mapTile.Select(selectFROM, selectTO, //city zamiast map !!!!!!!!!!!
							{
								this->plate->_typeOfTile,   TypeOfTile::DIRT,
								TypeOfTile::NOTHING,                TypeOfTile::CROSS,
								TypeOfTile::HOUSES,        TypeOfTile::SHOPS,
								TypeOfTile::FACTORY
							});
					}
					this->guiSystem.at("selectionCostText").setEntryText(0, "$" + std::to_string(this->plate->value * this->city.mapTile.selected));
					if (this->city.funds <= this->city.mapTile.selected * this->plate->value)
						this->guiSystem.at("selectionCostText").highlight(0);
					else
						this->guiSystem.at("selectionCostText").highlight(-1);
					this->guiSystem.at("selectionCostText").setPosition(guiPos + sf::Vector2f(16, -16));
					this->guiSystem.at("selectionCostText").schow();
				}
				this->guiSystem.at("rightClickMenu").highlight(this->guiSystem.at("rightClickMenu").getEntry(guiPos));



			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (this->mouseEvent != MouseEvents::SELECT)
				{
					this->mouseEvent = MouseEvents::SELECT;
					sf::Vector2f pos = this->ptrGame->window.mapPixelToCoords(sf::Mouse::getPosition(this->ptrGame->window), this->ptrGame->cameraGame);
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




	//-------------------- SIMCITY GUI UPDATE

	//this->city.update(dt);
	/* Update the info bar at the bottom of the screen */

	
	this->guiSystem.at("infoBar").setEntryText(0, "Day: " + std::to_string(this->city.day));
	this->guiSystem.at("infoBar").setEntryText(1, "$" + std::to_string(long(this->city.funds)));
	this->guiSystem.at("infoBar").setEntryText(2, std::to_string(long(this->city.population)) + " (" + std::to_string(long(this->city.getHomeless())) + ")");
	this->guiSystem.at("infoBar").setEntryText(3, std::to_string(long(this->city.employable)) + " (" + std::to_string(long(this->city.getUnemployed())) + ")");
	this->guiSystem.at("infoBar").setEntryText(4, "Test Gui");//tile.tileTypeToStr(this->plate->_typeOfTile));
	

	/* Highlight entries of the right click context menu */
	this->guiSystem.at("rightClickMenu").highlight(this->guiSystem.at("rightClickMenu").getEntry(this->ptrGame->window.mapPixelToCoords(sf::Mouse::getPosition(this->ptrGame->window), this->ptrGame->cameraGame)));
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
		this->ptrGame->window.setView(this->ptrGame->cameraGame);

	if (created == false)
		this->DrawButtons();

	if (created == false)
		this->ptrGame->window.draw(sizeMapText);

	//draw gui game SIMCITY

	//this->ptrGame->window.setView(this->guiView);
	for (auto gui : this->guiSystem) this->ptrGame->window.draw(gui.second);
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
	this->ptrGame->cameraGame.setCenter(center);

	created = true;
}

void CreateMap::zoomViewAt(sf::Vector2i pixel, sf::RenderWindow& window, float zoom)
{
	const sf::Vector2f beforeCoord{ window.mapPixelToCoords(pixel) };
	this->ptrGame->cameraGame.zoom(zoom);
	window.setView(this->ptrGame->cameraGame);
	const sf::Vector2f afterCoord{ window.mapPixelToCoords(pixel) };
	const sf::Vector2f offsetCoords{ beforeCoord - afterCoord };
	this->ptrGame->cameraGame.move(offsetCoords);
	window.setView(this->ptrGame->cameraGame);
}

CreateMap::~CreateMap()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}