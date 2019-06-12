#ifndef TextBox_hpp
#define TextBox_hpp

#include <SFML/Graphics.hpp>

#include <string>
#include <iostream>

class TextBoxInput
{
	int maxChars = 100;
	int rightTextBound = 0;

	bool shouldEnter = false;
	bool focus = false;
	bool onlyNumbers = false;

	std::string sendBuffer = "";
	std::string tempBuffer = "";
	std::size_t cursor = 0;

	sf::Font font;
	sf::Text currentTextDisplayT;
	sf::RectangleShape cursorShape;
	sf::Rect<float> bounds;

	mutable sf::Int32 elapsedTime = 0.0f;
	mutable sf::Clock clock;

	void LoadFont(const std::string & filePath);
	void HandleLocalTextInput(sf::Event & events, const sf::Vector2f & mousePosition);

public:
	TextBoxInput();
	TextBoxInput(float x, float y, int boxWidth, float fontSize, const std::string & fontPath,
		bool onlyNumbers = false, int maxChars = 10, sf::Color color = sf::Color(0, 0, 0));
	virtual ~TextBoxInput() = default;

	void Update(sf::Event &events, const sf::Vector2f & mousePosition);
	void Draw(sf::RenderWindow *renderWindow);

	void EraseButtons();
	void ResetClock() const;

	//setters
	void SetCursor(std::size_t cursor);
	void SetPosition(float x, float y);
	void SetString(const std::string & text);

	//getters
	std::string GetString() const;
	sf::Vector2f GetPosition();
};

#endif // !TextBox_hpp