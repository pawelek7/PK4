#ifndef Disaster_hpp
#define Disaster_hpp

#include "AnimationSprite.h"
#include "defines.h"
#include "RandomEngine.h"
#include "NoCopyNoMove.h"

/*
Disaster Class inherits from the AnimationSprite class and NoCopyNoMove class.
It is the base class for disasters occurring in the game. 
Contains the basic variables that are used by descendants, as well as methods.

@author
Pawel Salicki
*/

class Disaster : public AnimationSprite, public NoCopyNoMove
{
public:
	enum class DisasterType //stores the type of disaster
	{
		VOID = 0, TORNADO = 1, FIRE = 2
	};

protected:
	int sizeMap = 0; //size of map in game
	int mapX = 0, mapY = 0; //map coordinates
	int counterLife = 0; //length of disaster
	int disasterLifetime = 1000; //length of disaster
	int movementCounter = 0; //length of movement in one direction

	bool disasterActive = false; //if disaster is active
	bool disasterEnd = false; //if disaster is inactive

	RandomEngine randomEngine; //randomise event
	DisasterType disasterType = DisasterType::VOID; //type of disaster

public:
	Disaster() = default;
	Disaster(const sf::Texture & texture, const std::vector<Frames> & frames, 
		DisasterType disasterType = DisasterType::VOID); //multi-parameter constructor
	virtual ~Disaster() = default; //destructor

	virtual void Draw(sf::RenderWindow & window, const float elapsedTime, //function that supports drawing disaster
		sf::Shader *shader = nullptr, const sf::Vector2f & camera_position = sf::Vector2f(0, 0)) override;

	//accessors
	void SetSizeMapInformation(int sizeMap = 0);

	//getters
	bool GetIsDisasterActive() const;
	bool GetIsDisasterEnd() const;
};

#endif // !Disaster_hpp