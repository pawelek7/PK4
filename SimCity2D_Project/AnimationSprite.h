#ifndef AnimationSprite_hpp
#define AnimationSprite_hpp

#include <SFML/Graphics.hpp>

#include <vector>

/*
Class responsible for storing information about frame:
lenght of frame, and size of frames.

@author
Pawel Salicki
*/

class Frames
{
	friend class AnimationSprite;

	unsigned short startFrame = 0; //begin frame
	unsigned short endFrame = 0; //end frame
	float length = 1.0f; //length of frame of animation

public:
	Frames() = default;
	Frames(unsigned short startFrame, unsigned short endFrame, float length)
		:startFrame(startFrame), endFrame(endFrame), length(length)
	{
		//nothing
	}
	virtual ~Frames() = default;

	//getters
	inline unsigned short GetLenght() //get length of frame animation
	{
		return (this->endFrame - this->startFrame + 1);
	}
};

/*
Class responsible for animate picture.

@author
Pawel Salicki
*/

class AnimationSprite
{
protected:
	std::vector<Frames> frames; //vector of Frame class

	float time = 0.0f; //time od showing frame
	int actualFrame = -1; //actual frame

	sf::IntRect currentSection; //current section of picture
	sf::IntRect frameSize; //size of frame
	sf::Sprite sprite; //sprite (picture)

public:
	AnimationSprite() = default;
	AnimationSprite(const sf::IntRect & frameSize);
	AnimationSprite(const std::vector<Frames> & frames);
	AnimationSprite(const std::vector<Frames> & frames, sf::Sprite & sprite);
	virtual ~AnimationSprite() = default;

	//draw frame
	virtual void Draw(sf::RenderWindow & window, const float elapsedTime, 
		sf::Shader *shader = nullptr, const sf::Vector2f & camera_position = sf::Vector2f(0, 0)) = 0;
	void UpdateAnimation(const float elapsedTime); //update animation

	void AddAnimation(Frames & frames); //add new frame to vector
	void ChangeFrame(unsigned short IDframe); //force change frame

	//setters
	void SetSpritePosition(sf::Vector2f & spritePosition);
};

#endif // !AnimationSprite_hpp