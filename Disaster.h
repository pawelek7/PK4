#ifndef Disaster_hpp
#define Disaster_hpp

#include <chrono>
#include <random>

#include "AnimationSprite.h"
#include "defines.h"
#include "RandomEngine.h"

enum class DisasterType
{
	VOID = 0, TORNADO = 1, FIRE = 2
};

class Disaster : public AnimationSprite
{
protected:
	int sizeMap = 0;
	int mapX = 0, mapY = 0;
	int counterLife = 0;
	int disasterLifetime = 1000;
	int movementCounter = 0;

	bool disasterActive = false;
	bool disasterEnd = false;

	RandomEngine randomEngine;
	DisasterType disasterType = DisasterType::VOID;

public:
	Disaster(const sf::Texture & texture, const std::vector<Frames> & frames, 
		DisasterType disasterType = DisasterType::VOID);
	virtual ~Disaster() = default;

	virtual void UpdateDisaster(float elapsedTime) = 0;
	virtual void Draw(sf::RenderWindow& window, float elapsedTime,
		sf::Shader *shader = nullptr, const sf::Vector2f & camera_position = sf::Vector2f(0, 0)) override;

	void SetSizeMapInformation(int sizeMap);

	bool GetIsDisasterActive() const;
	bool GetIsDisasterEnd() const;
};

#endif // !Disaster_hpp
