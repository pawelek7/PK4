#ifndef ButtonBase_hpp
#define ButtonBase_hpp

#include <SFML/Graphics.hpp>

#include "AssetsOfGame.h"

const float p2pX(const float perc, const sf::VideoMode& vm);
const float p2pY(const float perc, const sf::VideoMode& vm);
const unsigned calcCharSize(const sf::VideoMode& vm, const unsigned modifier = 60);

class ButtonBase 
{
public:
	enum class ButtonState
	{
		IDLING = 0, HOVER = 1, ACTIVE = 2
	};

private:
	ButtonState buttonState = ButtonState::IDLING;

	float keyTime = 0.0f;
	float keyTimeMax = 1.0f;

protected:
	std::shared_ptr<AssetsOfGame> ptrGame = nullptr;

	float windowSizeX = 0.0f, windowSizeY = 0.0f;
	short unsigned int buttonID = 0;
	bool mouseOnButton = false;

	sf::RectangleShape buttonHitbox;

public:
	ButtonBase(float x, float y, float width, float height, short unsigned int buttonID,
		std::shared_ptr<AssetsOfGame> ptrGame);

	virtual void ChangeElementPosition(float x, float y) = 0;
	virtual void UpdateLook() = 0;
	virtual void DrawButton(sf::RenderTarget *renderTarget) = 0;

	void UpdateButtonParameters(float x, float y, float width, float height);
	void UpdateButton(const sf::Vector2f & mousePosition, const float & elapsedTime);
	void UpdateKeyTime(const float & elapsedTime);
	void ChangeButtonPosition(float x, float y);

	//getters
	ButtonState GetButtonState() const;
	const short unsigned int & GetID() const;
	const bool GetPressed();
	bool GetKeyTime();
	bool GetMouseOnButton();
};

#endif // !ButtonBase_hpp