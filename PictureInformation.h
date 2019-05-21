#ifndef PictureInformation_hpp
#define PictureInformation_hpp

#include <SFML/Graphics.hpp>

#include <map>

#include "AssetManager.h"
#include "IDvector.h"

enum class PictureType
{
	PEOPLE_UP = 0, GOODS_OUT = 1, GOODS_IN = 2, SICK = 3, MONEY = 4,
	ENERGY_OUT = 5
};

class PictureInformation
{
	int iterator = 0;
	int lifeTime = 255;
	int counterLife = 0;
	int pictureSpeed = 25;

	ID buildingID = UNDEFINED;

	bool deletePicture = false;
	bool holdInformation = false;
	bool animationType = false;

	AssetManager<sf::Texture> textureManager;
	std::map<PictureType, sf::Texture> pictureInformationMap;

	sf::RectangleShape pictureRectangle;
	sf::Sprite pictureSprite;
	
public:
	PictureInformation() = default;
	PictureInformation(ID buildingID);
	virtual ~PictureInformation() = default;

	void InitializePictureInformation(PictureType pictureType);
	void UpdatePictureInformation(float elapsedTime);
	void DrawPictureInformation(sf::RenderTarget *renderTarget);
	void ForceDelete();

	void SetPictureInformationPosition(const sf::Vector2f & position);
	void SetHoldInformation(bool holdInformation);

	ID GetPictureID() const;

	bool GetHoldInformation() const;
	bool GetIsDeleted() const;
};

#endif // !PictureInformation_hpp
