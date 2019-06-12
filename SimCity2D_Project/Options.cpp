#include "Options.h"

#pragma region Constructors

Options::Options(std::shared_ptr<AssetsOfGame> ptrGame) : ptrGame(ptrGame)
{
	this->videoModes = sf::VideoMode::getFullscreenModes();

	this->ptrGame->textureManager.LoadAsset("options", "Resources/Textures/options.png");
}

Options::~Options()
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

void Options::UpdateObject(float elapsedTime)
{
	this->ptrGame->window->setView(this->ptrGame->window->getDefaultView());

	for (auto & i : this->mapButtons)
	{
		i.second->UpdateButton(this->ptrGame->mousePositionWindow, elapsedTime);
	}

	if (this->mapButtons["APPLY"]->GetPressed())
	{
		this->ptrGame->audioManagement->SetVolume(this->volume_iterator);
		
		if (this->fullScreenText.getString() == "Yes")
		{
			this->ptrGame->window->create(sf::VideoMode(this->sizeWidth[iterator], this->sizeHeight[iterator]), GAME_NAME, sf::Style::Close | sf::Style::Fullscreen);
		}
		else
		{
			this->ptrGame->window->create(sf::VideoMode(this->sizeWidth[iterator], this->sizeHeight[iterator]), GAME_NAME, sf::Style::Close | sf::Style::Titlebar);
		}

		if (this->musicText.getString() == "No")
		{
			this->ptrGame->audioManagement->SetVolume(0);
		}
		
		this->ptrGame->videoMode.width = this->sizeWidth[iterator];
		this->ptrGame->videoMode.height = this->sizeHeight[iterator];
		this->CorrectPosition();
	}

	if (this->mapButtons["RETURN"]->GetPressed())
	{
		ptrGame->stateMachine.PopState();
		return;
	}
	if (this->mapButtons["NEXT_RESOLUTION"]->GetPressed())
	{
		iterator--;
		if (iterator <= -1)
			iterator = 9;

		std::stringstream ss;
		ss << tabOfSizes[iterator];
		this->resolutionText.setString(ss.str());
		this->resolutionText.setPosition(p2pX(65.0f, this->ptrGame->videoMode) - (this->resolutionText.getGlobalBounds().width / 2.f), p2pY(16.0f, this->ptrGame->videoMode));
	}
	if (this->mapButtons["BACK_RESOLUTION"]->GetPressed())
	{
		iterator++;
		if (iterator >= 10)
			iterator = 0;

		std::stringstream ss;
		ss << tabOfSizes[iterator];
		this->resolutionText.setString(ss.str());
		this->resolutionText.setPosition(p2pX(65.0f, this->ptrGame->videoMode) - (this->resolutionText.getGlobalBounds().width / 2.f), p2pY(16.0f, this->ptrGame->videoMode));
	}
	if (this->mapButtons["NEXT_FULLSCREEN"]->GetPressed())
	{
		if (this->fullScreenText.getString() == "No")
		{
			this->fullScreenText.setString("Yes");
		}
		else
		{
			this->fullScreenText.setString("No");
		}
		this->fullScreenText.setPosition(p2pX(65.0f, this->ptrGame->videoMode) - (this->fullScreenText.getGlobalBounds().width / 2.f), p2pY(33.0f, this->ptrGame->videoMode));
	}
	if (this->mapButtons["BACK_FULLSCREEN"]->GetPressed())
	{
		if (this->fullScreenText.getString() == "No")
		{
			this->fullScreenText.setString("Yes");
		}
		else
		{
			this->fullScreenText.setString("No");
		}
		this->fullScreenText.setPosition(p2pX(65.0f, this->ptrGame->videoMode) - (this->fullScreenText.getGlobalBounds().width / 2.f), p2pY(33.0f, this->ptrGame->videoMode));
	}
	if (this->mapButtons["NEXT_MUSIC"]->GetPressed())
	{
		if (this->musicText.getString() == "No")
		{
			this->musicText.setString("Yes");
		}
		else
		{
			this->musicText.setString("No");
		}
		this->musicText.setPosition(p2pX(65.0f, this->ptrGame->videoMode) - (this->musicText.getGlobalBounds().width / 2.f), p2pY(48.0f, this->ptrGame->videoMode));
	}
	if (this->mapButtons["BACK_MUSIC"]->GetPressed())
	{
		if (this->musicText.getString() == "No")
		{
			this->musicText.setString("Yes");
		}
		else
		{
			this->musicText.setString("No");
		}
		this->musicText.setPosition(p2pX(65.0f, this->ptrGame->videoMode) - (this->musicText.getGlobalBounds().width / 2.f), p2pY(48.0f, this->ptrGame->videoMode));
	}

	if (this->mapButtons["NEXT_VOLUME"]->GetPressed())
	{
		if (this->volume_iterator >= 100)
		{
			this->volume_iterator = 100;
		}
		else
		{
			this->volume_iterator += 5;
		}

		this->volumeText.setString(std::to_string(this->volume_iterator));
		this->volumeText.setPosition(p2pX(65.0f, this->ptrGame->videoMode) - (this->volumeText.getGlobalBounds().width / 2.f), p2pY(63.0f, this->ptrGame->videoMode));
	}

	if (this->mapButtons["BACK_VOLUME"]->GetPressed())
	{
		if (this->volume_iterator <= 0)
		{
			this->volume_iterator = 0;
		}
		else
		{
			this->volume_iterator -= 5;
		}
		this->volumeText.setString(std::to_string(this->volume_iterator));
		this->volumeText.setPosition(p2pX(65.0f, this->ptrGame->videoMode) - (this->volumeText.getGlobalBounds().width / 2.f), p2pY(63.0f, this->ptrGame->videoMode));
	}

	if (this->mapButtons["NEXT_SHADERS"]->GetPressed())
	{
		if (this->shadersText.getString() == "No")
		{
			this->shadersText.setString("Yes");
		}
		else
		{
			this->shadersText.setString("No");
		}
		this->shadersText.setPosition(p2pX(65.0f, this->ptrGame->videoMode) - (this->shadersText.getGlobalBounds().width / 2.f), p2pY(78.0f, this->ptrGame->videoMode));
	}
	if (this->mapButtons["BACK_SHADERS"]->GetPressed())
	{
		if (this->shadersText.getString() == "No")
		{
			this->shadersText.setString("Yes");
		}
		else
		{
			this->shadersText.setString("No");
		}
		this->shadersText.setPosition(p2pX(65.0f, this->ptrGame->videoMode) - (this->shadersText.getGlobalBounds().width / 2.f), p2pY(78.0f, this->ptrGame->videoMode));
	}

}

void Options::DrawObject(float elapsedTime)
{
	this->ptrGame->window->draw(background);

	for (auto & i : this->mapButtons)
	{
		i.second->DrawButton(this->ptrGame->window);
	}

	this->ptrGame->window->draw(this->resolutionText);
	this->ptrGame->window->draw(this->fullScreenText);
	this->ptrGame->window->draw(this->musicText);
	this->ptrGame->window->draw(this->volumeText);
	this->ptrGame->window->draw(this->shadersText);
}

void Options::InitializeObject()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->ptrGame->window->getSize().x),
		static_cast<float>(this->ptrGame->window->getSize().y)));

	this->background.setTexture(&this->ptrGame->textureManager.GetAsset("options"));

	this->font.loadFromFile("Resources/Fonts/Delimax.ttf"); //temporary solution!!!

	this->mapButtons["APPLY"] = new TextButton(p2pX(20.0f, this->ptrGame->videoMode), p2pY(86.0f, this->ptrGame->videoMode),
		p2pX(10.0f, this->ptrGame->videoMode), p2pY(10.0f, this->ptrGame->videoMode),
		"APPLY", calcCharSize(this->ptrGame->videoMode), sf::Color::White, sf::Color(102, 153, 153), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), this->ptrGame);

	this->mapButtons["RETURN"] = new TextButton(p2pX(40.0f, this->ptrGame->videoMode), p2pY(86.0f, this->ptrGame->videoMode),
		p2pX(10.0f, this->ptrGame->videoMode), p2pY(10.0f, this->ptrGame->videoMode),
		"RETURN", calcCharSize(this->ptrGame->videoMode), sf::Color::White, sf::Color(102, 153, 153), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), this->ptrGame);

	this->mapButtons["NEXT_RESOLUTION"] = new TextButton(p2pX(70.0f, this->ptrGame->videoMode), p2pY(16.0f, this->ptrGame->videoMode),
		p2pX(10.0f, this->ptrGame->videoMode), p2pY(10.0f, this->ptrGame->videoMode),
		"->", calcCharSize(this->ptrGame->videoMode), sf::Color::White, sf::Color(102, 153, 153), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), this->ptrGame);

	this->mapButtons["BACK_RESOLUTION"] = new TextButton(p2pX(50.0f, this->ptrGame->videoMode), p2pY(16.0f, this->ptrGame->videoMode),
		p2pX(10.0f, this->ptrGame->videoMode), p2pY(10.0f, this->ptrGame->videoMode),
		"<-", calcCharSize(this->ptrGame->videoMode), sf::Color::White, sf::Color(102, 153, 153), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), this->ptrGame);

	this->mapButtons["NEXT_FULLSCREEN"] = new TextButton(p2pX(70.0f, this->ptrGame->videoMode), p2pY(33.0f, this->ptrGame->videoMode),
		p2pX(10.0f, this->ptrGame->videoMode), p2pY(10.0f, this->ptrGame->videoMode),
		"->", calcCharSize(this->ptrGame->videoMode), sf::Color::White, sf::Color(102, 153, 153), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), this->ptrGame);

	this->mapButtons["BACK_FULLSCREEN"] = new TextButton(p2pX(50.0f, this->ptrGame->videoMode), p2pY(33.0f, this->ptrGame->videoMode),
		p2pX(10.0f, this->ptrGame->videoMode), p2pY(10.0f, this->ptrGame->videoMode),
		"<-", calcCharSize(this->ptrGame->videoMode), sf::Color::White, sf::Color(102, 153, 153), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), this->ptrGame);

	this->mapButtons["NEXT_MUSIC"] = new TextButton(p2pX(70.0f, this->ptrGame->videoMode), p2pY(48.0f, this->ptrGame->videoMode),
		p2pX(10.0f, this->ptrGame->videoMode), p2pY(10.0f, this->ptrGame->videoMode),
		"->", calcCharSize(this->ptrGame->videoMode), sf::Color::White, sf::Color(102, 153, 153), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), this->ptrGame);

	this->mapButtons["BACK_MUSIC"] = new TextButton(p2pX(50.0f, this->ptrGame->videoMode), p2pY(48.0f, this->ptrGame->videoMode),
		p2pX(10.0f, this->ptrGame->videoMode), p2pY(10.0f, this->ptrGame->videoMode),
		"<-", calcCharSize(this->ptrGame->videoMode), sf::Color::White, sf::Color(102, 153, 153), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), this->ptrGame);

	this->mapButtons["NEXT_VOLUME"] = new TextButton(p2pX(70.0f, this->ptrGame->videoMode), p2pY(63.0f, this->ptrGame->videoMode),
		p2pX(10.0f, this->ptrGame->videoMode), p2pY(10.0f, this->ptrGame->videoMode),
		"->", calcCharSize(this->ptrGame->videoMode), sf::Color::White, sf::Color(102, 153, 153), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), this->ptrGame);

	this->mapButtons["BACK_VOLUME"] = new TextButton(p2pX(50.0f, this->ptrGame->videoMode), p2pY(63.0f, this->ptrGame->videoMode),
		p2pX(10.0f, this->ptrGame->videoMode), p2pY(10.0f, this->ptrGame->videoMode),
		"<-", calcCharSize(this->ptrGame->videoMode), sf::Color::White, sf::Color(102, 153, 153), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), this->ptrGame);

	this->mapButtons["NEXT_SHADERS"] = new TextButton(p2pX(70.0f, this->ptrGame->videoMode), p2pY(78.0f, this->ptrGame->videoMode),
		p2pX(10.0f, this->ptrGame->videoMode), p2pY(10.0f, this->ptrGame->videoMode),
		"->", calcCharSize(this->ptrGame->videoMode), sf::Color::White, sf::Color(102, 153, 153), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), this->ptrGame);

	this->mapButtons["BACK_SHADERS"] = new TextButton(p2pX(50.0f, this->ptrGame->videoMode), p2pY(78.0f, this->ptrGame->videoMode),
		p2pX(10.0f, this->ptrGame->videoMode), p2pY(10.0f, this->ptrGame->videoMode),
		"<-", calcCharSize(this->ptrGame->videoMode), sf::Color::White, sf::Color(102, 153, 153), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), this->ptrGame);

	for (auto &i : this->videoModes)
	{
		tabOfSizes[iterator] = std::to_string(i.width) + 'x' + std::to_string(i.height);
		sizeWidth[iterator] = i.width;
		sizeHeight[iterator] = i.height;
		iterator++;

		if (iterator > 9)
		{
			break;
		}
	}
	iterator = 0;

	this->resolutionText.setFont(font);
	this->resolutionText.setFillColor(sf::Color::White);
	this->resolutionText.setCharacterSize(calcCharSize(this->ptrGame->videoMode,70));
	this->resolutionText.setString(tabOfSizes[iterator]);
	this->resolutionText.setPosition(p2pX(65.0f, this->ptrGame->videoMode) - (this->resolutionText.getGlobalBounds().width / 2.f), p2pY(16.0f, this->ptrGame->videoMode));

	this->fullScreenText.setFont(font);
	this->fullScreenText.setFillColor(sf::Color::White);
	this->fullScreenText.setCharacterSize(calcCharSize(this->ptrGame->videoMode));
	this->fullScreenText.setString("No");
	this->fullScreenText.setPosition(p2pX(65.0f, this->ptrGame->videoMode) - (this->fullScreenText.getGlobalBounds().width / 2.f), p2pY(33.0f, this->ptrGame->videoMode));


	this->musicText.setFont(font);
	this->musicText.setFillColor(sf::Color::White);
	this->musicText.setCharacterSize(calcCharSize(this->ptrGame->videoMode));
	this->musicText.setString("Yes");
	this->musicText.setPosition(p2pX(65.0f, this->ptrGame->videoMode) - (this->musicText.getGlobalBounds().width / 2.f), p2pY(48.0f, this->ptrGame->videoMode));


	this->volumeText.setFont(font);
	this->volumeText.setFillColor(sf::Color::White);
	this->volumeText.setCharacterSize(calcCharSize(this->ptrGame->videoMode));
	this->volume_iterator = this->ptrGame->audioManagement->GetVelume();
	this->volumeText.setString(std::to_string(volume_iterator));
	this->volumeText.setPosition(p2pX(65.0f, this->ptrGame->videoMode) - (this->volumeText.getGlobalBounds().width / 2.f), p2pY(63.0f, this->ptrGame->videoMode));


	this->shadersText.setFont(font);
	this->shadersText.setFillColor(sf::Color::White);
	this->shadersText.setCharacterSize(calcCharSize(this->ptrGame->videoMode));
	this->shadersText.setString("No");
	this->shadersText.setPosition(p2pX(65.0f, this->ptrGame->videoMode) - (this->shadersText.getGlobalBounds().width / 2.f), p2pY(78.0f, this->ptrGame->videoMode));

}

void Options::HoldInput()
{
	sf::Event sfmlEvent;

	while (this->ptrGame->window->pollEvent(sfmlEvent))
	{
		switch (sfmlEvent.type)
		{
		case sf::Event::Closed:
			this->ptrGame->window->close();
			break;
		case sf::Event::KeyPressed:
			if (sfmlEvent.key.code == sf::Keyboard::Escape)
			{
				this->ptrGame->window->close();
			}
			break;
		}
	}
}

void Options::CorrectPosition()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->ptrGame->window->getSize().x),
		static_cast<float>(this->ptrGame->window->getSize().y)));

	this->resolutionText.setCharacterSize(calcCharSize(this->ptrGame->videoMode, 70));
	this->fullScreenText.setCharacterSize(calcCharSize(this->ptrGame->videoMode));
	this->musicText.setCharacterSize(calcCharSize(this->ptrGame->videoMode));
	this->volumeText.setCharacterSize(calcCharSize(this->ptrGame->videoMode));
	this->shadersText.setCharacterSize(calcCharSize(this->ptrGame->videoMode));

	this->resolutionText.setPosition(p2pX(65.0f, this->ptrGame->videoMode) - (this->resolutionText.getGlobalBounds().width / 2.f), p2pY(16.0f, this->ptrGame->videoMode));
	this->fullScreenText.setPosition(p2pX(65.0f, this->ptrGame->videoMode) - (this->fullScreenText.getGlobalBounds().width / 2.f), p2pY(33.0f, this->ptrGame->videoMode));
	this->musicText.setPosition(p2pX(65.0f, this->ptrGame->videoMode) - (this->musicText.getGlobalBounds().width / 2.f), p2pY(48.0f, this->ptrGame->videoMode));
	this->volumeText.setPosition(p2pX(65.0f, this->ptrGame->videoMode) - (this->volumeText.getGlobalBounds().width / 2.f), p2pY(63.0f, this->ptrGame->videoMode));
	this->volumeText.setPosition(p2pX(65.0f, this->ptrGame->videoMode) - (this->volumeText.getGlobalBounds().width / 2.f), p2pY(63.0f, this->ptrGame->videoMode));
	this->shadersText.setPosition(p2pX(65.0f, this->ptrGame->videoMode) - (this->shadersText.getGlobalBounds().width / 2.f), p2pY(78.0f, this->ptrGame->videoMode));

	this->mapButtons["APPLY"]->ChangePositionAndSize(p2pX(20.0f, this->ptrGame->videoMode), p2pY(86.0f, this->ptrGame->videoMode),
		p2pX(10.0f, this->ptrGame->videoMode), p2pY(10.0f, this->ptrGame->videoMode), calcCharSize(this->ptrGame->videoMode));

	this->mapButtons["RETURN"]->ChangePositionAndSize(p2pX(40.0f, this->ptrGame->videoMode), p2pY(86.0f, this->ptrGame->videoMode),
		p2pX(10.0f, this->ptrGame->videoMode), p2pY(10.0f, this->ptrGame->videoMode), calcCharSize(this->ptrGame->videoMode));
	
	this->mapButtons["NEXT_RESOLUTION"]->ChangePositionAndSize(p2pX(70.0f, this->ptrGame->videoMode), p2pY(16.0f, this->ptrGame->videoMode),
		p2pX(10.0f, this->ptrGame->videoMode), p2pY(10.0f, this->ptrGame->videoMode), calcCharSize(this->ptrGame->videoMode));
	
	this->mapButtons["BACK_RESOLUTION"]->ChangePositionAndSize(p2pX(50.0f, this->ptrGame->videoMode), p2pY(16.0f, this->ptrGame->videoMode),
		p2pX(10.0f, this->ptrGame->videoMode), p2pY(10.0f, this->ptrGame->videoMode), calcCharSize(this->ptrGame->videoMode));

	this->mapButtons["NEXT_FULLSCREEN"]->ChangePositionAndSize(p2pX(70.0f, this->ptrGame->videoMode), p2pY(33.0f, this->ptrGame->videoMode),
		p2pX(10.0f, this->ptrGame->videoMode), p2pY(10.0f, this->ptrGame->videoMode), calcCharSize(this->ptrGame->videoMode));

	this->mapButtons["BACK_FULLSCREEN"]->ChangePositionAndSize(p2pX(50.0f, this->ptrGame->videoMode), p2pY(33.0f, this->ptrGame->videoMode),
		p2pX(10.0f, this->ptrGame->videoMode), p2pY(10.0f, this->ptrGame->videoMode), calcCharSize(this->ptrGame->videoMode));

	this->mapButtons["NEXT_MUSIC"]->ChangePositionAndSize(p2pX(70.0f, this->ptrGame->videoMode), p2pY(48.0f, this->ptrGame->videoMode),
		p2pX(10.0f, this->ptrGame->videoMode), p2pY(10.0f, this->ptrGame->videoMode), calcCharSize(this->ptrGame->videoMode));

	this->mapButtons["BACK_MUSIC"]->ChangePositionAndSize(p2pX(50.0f, this->ptrGame->videoMode), p2pY(48.0f, this->ptrGame->videoMode),
		p2pX(10.0f, this->ptrGame->videoMode), p2pY(10.0f, this->ptrGame->videoMode), calcCharSize(this->ptrGame->videoMode));

	this->mapButtons["NEXT_VOLUME"]->ChangePositionAndSize(p2pX(70.0f, this->ptrGame->videoMode), p2pY(63.0f, this->ptrGame->videoMode),
		p2pX(10.0f, this->ptrGame->videoMode), p2pY(10.0f, this->ptrGame->videoMode), calcCharSize(this->ptrGame->videoMode));

	this->mapButtons["BACK_VOLUME"]->ChangePositionAndSize(p2pX(50.0f, this->ptrGame->videoMode), p2pY(63.0f, this->ptrGame->videoMode),
		p2pX(10.0f, this->ptrGame->videoMode), p2pY(10.0f, this->ptrGame->videoMode), calcCharSize(this->ptrGame->videoMode));

	this->mapButtons["NEXT_SHADERS"]->ChangePositionAndSize(p2pX(70.0f, this->ptrGame->videoMode), p2pY(78.0f, this->ptrGame->videoMode),
		p2pX(10.0f, this->ptrGame->videoMode), p2pY(10.0f, this->ptrGame->videoMode), calcCharSize(this->ptrGame->videoMode));

	this->mapButtons["BACK_SHADERS"]->ChangePositionAndSize(p2pX(50.0f, this->ptrGame->videoMode), p2pY(78.0f, this->ptrGame->videoMode),
		p2pX(10.0f, this->ptrGame->videoMode), p2pY(10.0f, this->ptrGame->videoMode), calcCharSize(this->ptrGame->videoMode));
}

#pragma endregion