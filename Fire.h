#ifndef Fire_hpp
#define Fire_hpp

#include <cassert>

#include "Disaster.h"

class Fire : public Disaster
{
	int fireLoops = 0;

	std::vector<sf::Vector2i> fireCoordinates;
	std::vector<sf::Sprite> spriteVectorFire;

	sf::Vector2i burnedArea = sf::Vector2i(-1, -1);
	sf::Vector2i fireHeart = sf::Vector2i(-1, -1);

	void FireIntelligence();
	void ChangeFirePosition(sf::Vector2i firePosition);

public:
	Fire() = default;
	Fire(const sf::Texture & texture, const std::vector<Frames> & frames);
	virtual ~Fire() = default;

	virtual void Draw(sf::RenderWindow& window, float elapsedTime,
		sf::Shader *shader = nullptr, const sf::Vector2f & camera_position = sf::Vector2f(0, 0)) override;
	virtual void UpdateDisaster(float elapsedTime) override;

	void InitializeFire(int positionX, int positionY);
	void FireBrigadeEvent(sf::Vector2i extinguishedArea);

	std::vector<sf::Vector2i> GetFireVectorCoordinates() const;
	std::vector<sf::Sprite> GetFireSpritesVector() const;

	sf::Vector2i GetReturnedBurnedArea() const;
	sf::Vector2i GetFireHearth() const;
};

#endif // !Fire_hpp
