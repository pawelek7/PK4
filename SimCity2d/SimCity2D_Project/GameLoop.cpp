#include "GameLoop.h"

GameLoop::GameLoop(std::shared_ptr<GameAssets> ptrGame) : ptrGame(ptrGame)
{
	sf::Vector2f pos = sf::Vector2f(this->ptrGame->window.getSize());
	this->camera.setSize(pos);
	pos *= 0.5f;
	this->camera.setCenter(pos);
	/*
	std::ofstream outputFile;
	outputFile.open("city_map.dat", std::ios::out | std::ios::binary);

	for (int i =0; i < 64*64; i++)
	{
		outputFile.write((char*)"1", sizeof(int));

	}

	outputFile.close();
	*/
}

void GameLoop::UpdateObject(float elapsedTime)
{
	
	
}

void GameLoop::HoldInput()
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

		/*
		if (event.type == sf::Event::TextEntered)
		{
			text.setFont(font);
			if (event.text.unicode < 128)
			{
				str += static_cast<char>(event.text.unicode);
				text.setString(str);
			}
		}
		*/
	}
}

void GameLoop::zoomViewAt(sf::Vector2i pixel, sf::RenderWindow& window, float zoom)
{
	const sf::Vector2f beforeCoord{ window.mapPixelToCoords(pixel) };
	camera.zoom(zoom);
	window.setView(camera);
	const sf::Vector2f afterCoord{ window.mapPixelToCoords(pixel) };
	const sf::Vector2f offsetCoords{ beforeCoord - afterCoord };
	camera.move(offsetCoords);
	window.setView(camera);
}

void GameLoop::DrawObject(float elapsedTime)
{
	this->map.Draw(this->ptrGame->window, elapsedTime);
	this->ptrGame->window.setView(this->camera);
}

void GameLoop::InitializeObject()
{
	//this->font.loadFromFile("Resources/Font/Delimax.ttf");
	this->ptrGame->textureManager.LoadAsset("dirt", "Resources/Textures/dirt.png");
	this->ptrGame->tile_map["dirt"] =
		Plate(32, 1, this->ptrGame->textureManager.GetAsset("dirt"),TypeOfTile::DIRT , 50 , 0, 1);

	
	map = MapTile("city_map.dat", 32, 32, ptrGame->tile_map);
}
