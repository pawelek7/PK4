#ifndef TextButton_hpp
#define TextButton_hpp

#include "ButtonBase.h"

class TextButton : public ButtonBase
{
	bool drawHitbox = false;

	sf::Font *font = nullptr;
	sf::Text text;

	sf::Color textIdling, textHover, textActive;
	sf::Color buttonIdling, buttonHover, buttonActive;
	sf::Color outlineIdleColor, outlineHoverColor, outlineActiveColor;

public:
	TextButton() = default;
	TextButton(float x, float y, float width, float height, std::string text,
		unsigned short int characterSize, sf::Color textIdliing, sf::Color textHover, sf::Color textActive,
		sf::Color buttonIdling, sf::Color buttonHover, sf::Color buttonActive, std::shared_ptr<AssetsOfGame> ptrGame,
		bool drawHitbox = false, unsigned short int buttonID = 0,
		sf::Color outlineIdleColor = sf::Color::Transparent, sf::Color outlineHoverColor=sf::Color::Transparent,
		sf::Color outlineActiveColor = sf::Color::Transparent);
	virtual ~TextButton() = default;

	virtual void ChangeElementPosition(float x, float y) override;
	virtual void UpdateLook() override;
	virtual void DrawButton(sf::RenderTarget *renderTarget) override;

	void SetString(const std::string & text);
	void SetID(unsigned int id);
	void ChangePositionAndSize(float x, float y, float width, float height, int characterSize);

	std::string GetString() const;
	sf::Text GetText() const;
};

#endif // !TextButton_hpp