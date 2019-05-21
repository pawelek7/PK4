#ifndef AnimationSprite_hpp
#define AnimationSprite_hpp

#include <SFML/Graphics.hpp>

#include <vector>

class Frames
{
	friend class AnimationSprite;

	unsigned short startFrame = 0;
	unsigned short endFrame = 0;
	float duration = 1.0f;

public:
	Frames(unsigned short startFrame, unsigned short endFrame, float duration)
		:startFrame(startFrame), endFrame(endFrame), duration(duration) {}

	inline unsigned short GetLenght()
	{
		return this->endFrame - this->startFrame + 1;
	}
};

class AnimationSprite
{
protected:
	std::vector<Frames> frames;

	float time = 0.0f;
	int actualFrame = -1;

	sf::IntRect currentSection;
	sf::IntRect frameSize;
	sf::Sprite sprite;

public:
	AnimationSprite() = default;
	AnimationSprite(const sf::IntRect & frameSize);
	AnimationSprite(const std::vector<Frames> & frames);
	AnimationSprite(const std::vector<Frames> & frames, sf::Sprite & sprite);
	virtual ~AnimationSprite() = default;

	virtual void Draw(sf::RenderWindow& window, float elapsedTime, 
		sf::Shader *shader = nullptr, const sf::Vector2f & camera_position = sf::Vector2f(0, 0)) = 0;
	void UpdateAnimation(const float elapsedTime);

	void AddAnimation(Frames & frames);
	void ChangeFrame(unsigned short IDframe);

	void SetSpritePosition(sf::Vector2f spritePosition);
};

#endif // !AnimationSprite_hpp