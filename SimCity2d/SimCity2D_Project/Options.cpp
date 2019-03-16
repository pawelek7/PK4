#include "Options.h"

Options::Options(std::shared_ptr<GameAssets> ptrGame) :ptrGame(ptrGame)
{
	this->modes = sf::VideoMode::getFullscreenModes();
	this->ptrGame->fontManager.LoadAsset("Delimax", "Resources/Font/Delimax.ttf");
	this->ptrGame->textureManager.LoadAsset("SimCity_background", "Resources/Textures/SimCity_background.jpg");
}

void Options::HoldInput()
{
	if (this->buttons["BACK"]->isPressed())
	{
		ptrGame->stateMachine.NewState(std::unique_ptr<StateOfProgram>(new MainMenu(ptrGame)), "Main Menu", true);
	}

	//Apply selected settings
	if (this->buttons["APPLY"]->isPressed())
	{
		this->ptrGame->graphic.resolution = this->modes[this->dropDownList["RESOLUTION"]->getActiveElementId()];
		this->ptrGame->window.create(this->ptrGame->graphic.resolution, this->ptrGame->graphic.title, sf::Style::Default);
		this->background.setSize(
			sf::Vector2f
			(
				static_cast<float>(ptrGame->window.getSize().x),
				static_cast<float>(ptrGame->window.getSize().y)
			)
		);
	}
}

void Options::InitializeObject()
{
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(ptrGame->window.getSize().x),
			static_cast<float>(ptrGame->window.getSize().y)
		)
	);

	this->background.setTexture(&this->ptrGame->textureManager.GetAsset("SimCity_background"));
	this->font.loadFromFile("Resources/Font/Delimax.ttf"); //temporary solution!!!
	this->buttons["BACK"] = new Gui::Button(
		0.f, this->ptrGame->window.getSize().y - 60, 250.f, 50.f,
		&this->font, "Back", 50,
		sf::Color(70, 255, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["APPLY"] = new Gui::Button(
		this->ptrGame->window.getSize().x-300, this->ptrGame->window.getSize().y - 60, 250.f, 50.f,
		&this->font, "Apply", 50,
		sf::Color(70, 255, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	std::vector<std::string> modes_str;
	for (auto &i : this->modes)
	{
		modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
	}

	this->dropDownList["RESOLUTION"] = new Gui::DropDownList(80, 45, 200, 50, font, modes_str.data(), modes_str.size());
}

Options::~Options()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	auto it2 = this->dropDownList.begin();
	for (it2 = this->dropDownList.begin(); it2 != this->dropDownList.end(); ++it2)
	{
		delete it2->second;
	}

}

void Options::UpdateObject(float deltaTime)
{
	//Updates all the gui elements in the state and handle their functionlaity.* /
		//Buttons
		for (auto &it : this->buttons)
		{
			it.second->update(this->ptrGame->mousePosView);
		}

	//Button functionality
	//Quit the game

	

	//Dropdown lists
	for (auto &it : this->dropDownList)
	{
		it.second->Update(this->ptrGame->mousePosView, deltaTime);
	}

	//Dropdown lists functionality
}

void Options::DrawObject(float elapsedTime)
{
	this->ptrGame->window.draw(background);
	for (auto &it : this->buttons)
	{
		it.second->render(this->ptrGame->window);
	}

	for (auto &it : this->dropDownList)
	{
		it.second->Draw(this->ptrGame->window);
	}
}