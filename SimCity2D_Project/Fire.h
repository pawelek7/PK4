#ifndef Fire_hpp
#define Fire_hpp

#include <cassert>

#include "Disaster.h"

#define MAX_FLAMES 6
#define MOVEMENT_FIRE 50
#define POSITION_FROM -2
#define POSITION_TO 2

/*
The fire class inherits from the Disaster class in public.
It supports a fire disaster.

@author
Pawel Salicki
*/

class Fire : public Disaster
{
	int fireLoops = 0; //the number of flames on the map

	std::vector<sf::Vector2i> fireCoordinates; //container of flame coordinates
	std::vector<sf::Sprite> spriteVectorFire; //container of fire spraits

	sf::Vector2i burnedArea = sf::Vector2i(-1, -1); //coordinates of the burnt area
	sf::Vector2i fireHeart = sf::Vector2i(-1, -1); //coordinates of the initial fire

	void FireIntelligence(); //fire behavior
	void ChangeFirePosition(sf::Vector2i firePosition); //change fire position on map

public:
	Fire() = default; //constructor without argument
	Fire(const sf::Texture & texture, const std::vector<Frames> & frames); //multi-parameter constructor
	virtual ~Fire() = default; //destructor

	virtual void Draw(sf::RenderWindow & window, const float elapsedTime, //drawing method
		sf::Shader *shader = nullptr, const sf::Vector2f & camera_position = sf::Vector2f(0, 0)) override;
	virtual void UpdateDisaster(const float elapsedTime); //updating method

	void InitializeFire(int positionX, int positionY); //initialize fire on special coordinates
	void FireBrigadeEvent(sf::Vector2i extinguishedArea); //the fire service extinguishes the fire

	//getters
	std::vector<sf::Vector2i> GetFireVectorCoordinates() const;
	std::vector<sf::Sprite> GetFireSpritesVector() const;

	sf::Vector2i GetReturnedBurnedArea() const;
	sf::Vector2i GetFireHearth() const;
};

#endif // !Fire_hpp