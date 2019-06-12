#ifndef GameEventInfo_hpp
#define GameEventInfo_hpp

#include <SFML/Graphics.hpp>

#include <queue>

#include "defines.h"
#include "AssetsOfGame.h"
#include "ButtonBase.h"

class GameEventInfo
{
public:
	enum class InfoType
	{
		BUTTON = 0, BAD_INFO = 1, GOOD_INFO = 2
	};

private:
	struct Information
	{
		sf::Text information;
		int counterLife;
	};

	int counterInformation = 0;
	int lifeTimeInformation = 200;

	std::queue<Information> informationQueue;
	std::shared_ptr<AssetsOfGame> ptrGame = nullptr;

	sf::Text informationText;
	sf::Text counterText;

	sf::Vector2f centre;
	sf::RectangleShape envelope;

	void InitializeTextParameters();

public:
	GameEventInfo() = default;
	GameEventInfo(std::shared_ptr<AssetsOfGame> ptrGame , int windowPosCorrection = 0);
	virtual ~GameEventInfo() = default;

	void DrawInformation();
	void PushInformationToQueue(const std::string & information, InfoType infoType);
	void UpdateInformationText();
};

#endif // !GameEventInfo_hpp
