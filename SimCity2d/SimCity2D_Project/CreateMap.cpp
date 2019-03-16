#include "CreateMap.h"

CreateMap::CreateMap(std::shared_ptr<GameAssets> ptrGame) : ptrGame(ptrGame)
{
	
}

void CreateMap::InitializeObject()
{
	this->ptrGame->textureManager.LoadAsset("cross", "Resources/Textures/cross.png");
	this->ptrGame->textureManager.LoadAsset("dirt", "Resources/Textures/dirt.png");

	



	this->selectorRect.setSize(sf::Vector2f(64, 32));
	this->selectorRect.setFillColor(sf::Color(225, 255, 255, 150));
	this->selectorRect.setOutlineThickness(1.0f);
	this->selectorRect.setOutlineColor(sf::Color::Green);

	this->selectorRect.setTextureRect(this->textureRect);

	this->selectTexture = new Gui::SelectTexture(20.0f, 20.0f, 250.0f, 250.0f, 32.0f, &this->ptrGame->textureManager.GetAsset("dirt"));

	this->font.loadFromFile("Resources/Font/Delimax.ttf");
	nameText.setFont(font);
}

void CreateMap::HoldInput()
{
	sf::Event event;

	while (this->ptrGame->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			this->ptrGame->window.close();

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

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2f pos = this->ptrGame->window.mapPixelToCoords(sf::Mouse::getPosition(this->ptrGame->window), this->camera);
			selectTO.x = pos.y / (this->map.tileSize) + pos.x / (2 * this->map.tileSize) - this->map.width * 0.5 - 0.5;
			selectFROM.y = pos.y / (this->map.tileSize) - pos.x / (2 * this->map.tileSize) + this->map.width * 0.5 + 0.5;

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

	if (event.type == sf::Event::TextEntered)
	{
		if (event.text.unicode == '\b' && nameMapV.size() != 0)
		{
			nameMapV.pop_back();
			std::string s(nameMapV.begin(), nameMapV.end());
			nameText.setString(s);
			sizeSquare = s;
		}
		else if (event.text.unicode >= 48 && event.text.unicode <= 57)
		{
			nameMapV.push_back((char)event.text.unicode);
			std::string s(nameMapV.begin(), nameMapV.end());
			nameText.setString(s);
			sizeSquare = s;
		}
		if (event.text.unicode == 13)
		{
			CreateTilesToEdit(sizeSquare);
		}

	}
}


void CreateMap::UpdateObject(float deltaTime)
{

}

void CreateMap::DrawObject(float deltaTime)
{
	if (created == true)
		this->map.Draw(this->ptrGame->window, deltaTime);

	this->ptrGame->window.draw(this->selectorRect);
	this->selectTexture->Draw(this->ptrGame->window);
	this->ptrGame->window.draw(nameText);
	this->ptrGame->window.setView(this->camera);
}

void CreateMap::CreateTilesToEdit(std::string s)
{
	int sizeOfSquare = atoi(s.c_str());

	this->ptrGame->tile_map["dirt"] =
		Plate(32, 1, this->ptrGame->textureManager.GetAsset("dirt"), TypeOfTile::DIRT, 50, 0, 1);
	this->ptrGame->tile_map["cross"] =
		Plate(32, 1, this->ptrGame->textureManager.GetAsset("cross"), TypeOfTile::DIRT, 50, 0, 1);

	this->plate = &this->ptrGame->tile_map.at("cross"); //!!!!!!!!!!!!!!11

	map = MapTile(sizeOfSquare, sizeOfSquare, ptrGame->tile_map);

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