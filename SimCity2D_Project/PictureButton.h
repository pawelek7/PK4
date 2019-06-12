#ifndef PictureButton_hpp
#define PictureButton_hpp

#include <SFML/Graphics.hpp>

#include <map>

#include "AssetsOfGame.h"
#include "ButtonBase.h"

class PictureButton : public ButtonBase
{
	sf::Texture textIDLE, textACTIVE;
	sf::RectangleShape pictureOfButton;

public:
	PictureButton() = default;
	PictureButton(float x, float y, float width, float height, unsigned short int size,
		const sf::Texture* pictureOfButtonIDLING, const sf::Texture* pictureOfButtonACTIVE,
		std::shared_ptr<AssetsOfGame> ptrGame, unsigned short int buttonID = 0);
	virtual ~PictureButton() = default;

	virtual void ChangeElementPosition(float x, float y) override;
	virtual void UpdateLook() override;
	virtual void DrawButton(sf::RenderTarget *renderTarget) override;
};

#endif