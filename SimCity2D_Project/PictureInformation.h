#ifndef PictureInformation_hpp
#define PictureInformation_hpp

#include <SFML/Graphics.hpp>

#include <map>

#include "AssetManager.h"
#include "IDvector.h"

class PictureInformation 
{
public:
	enum class PictureType
	{
		VOID = 0, PEOPLE_UP = 1, GOODS_OUT = 2, GOODS_IN = 3, SICK = 4, MONEY = 5,
		ENERGY_OUT = 6, THIEF = 7, HAPPY = 8, ANGRY = 9, PROTEST = 10
	};

private:
	int iterator = 0;
	int lifeTime = 255;
	int counterLife = 0;
	int pictureSpeed = 25;

	bool deletePicture = false;
	bool holdInformation = false;
	bool animationType = false;

	ID buildingID = UNDEFINED;
	PictureType pictureType = PictureType::VOID;

	sf::Vector2f picturePosition;
	AssetManager<sf::Texture> textureManager;
	std::map<PictureType, sf::Texture> pictureInformationMap;

	sf::RectangleShape pictureRectangle;
	sf::Sprite pictureSprite;
	
public:
	PictureInformation();
	PictureInformation(ID buildingID);
	virtual ~PictureInformation() = default;

	void InitializeTextures();

	void InitializePictureInformation(PictureType pictureType);
	void UpdatePictureInformation(float elapsedTime);
	void DrawPictureInformation(sf::RenderTarget *renderTarget);
	void ForceDelete();
	void InitializePictureParameters(
		int iterator, int lifeTime, int counterLife, int pictureSpeed,
		ID buildingID, PictureType pictureType, bool deletePicture,
		bool holdInformation, bool animationType);

	//setters
	void SetPictureInformationPosition(const sf::Vector2f & position);
	void SetHoldInformation(bool holdInformation);

	//getters
	ID GetPictureID() const;
	PictureType GetPictureInformation() const;
	sf::Vector2f GetPictureInformationPosition();
	ID GetBuildingID() const;
	PictureType GetPictureType() const;

	bool GetHoldInformation() const;
	bool GetIsDeleted() const;
	bool GetAnimationType() const;

	int GetIterator() const;
	int GetLifeTime() const;
	int GetCounterLife() const;
	int GetPictureSpeed() const;
};

#endif // !PictureInformation_hpp
