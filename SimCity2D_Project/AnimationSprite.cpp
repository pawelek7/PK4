#include "AnimationSprite.h"

#pragma region Constructors

//constructors

AnimationSprite::AnimationSprite(const sf::IntRect & frameSize)
{
	this->frameSize = frameSize;
}

AnimationSprite::AnimationSprite(const std::vector<Frames> & frames)
{
	for (auto it : frames)
	{
		this->AddAnimation(it);
	}
}

AnimationSprite::AnimationSprite(const std::vector<Frames> & frames, sf::Sprite & sprite)
{
	for (auto it : frames)
	{
		this->AddAnimation(it);
	}

	this->sprite = sprite;
}

#pragma endregion

#pragma region Class_Methods

#pragma region Description of the method
/*
A method that updates animation.

method parameters:
____________________
elapsedTime - delta time

the return value:
____________________
no return value

@author
Pawel Salicki
*/
#pragma endregion

void AnimationSprite::UpdateAnimation(const float elapsedTime)
{
	//return if there isn't animation
	if (this->actualFrame >= this->frames.size() || this->actualFrame < 0)
	{
		return;
	}

	float duration = this->frames[this->actualFrame].length; //set duration of animation

	//set frame of animation if time is elapsed
	if (static_cast<int>((this->time + elapsedTime) / duration) > static_cast<int>(this->time / duration))
	{
		int frame = static_cast<int>((this->time + elapsedTime) / duration);
		frame %= this->frames[this->actualFrame].GetLenght();

		sf::IntRect rect = this->frameSize;
		rect.left = rect.width * frame;
		rect.top = rect.height * this->actualFrame;
		this->currentSection = rect;
	}

	this->time += elapsedTime;

	//reset time 
	if (this->time > duration * this->frames[this->actualFrame].GetLenght())
	{
		this->time = 0.0f;
	}
}

#pragma region Description of the method
/*
A method that forces to change animation
depending on frame number.

method parameters:
____________________
IDframe - number of frame

the return value:
____________________
no return value

@author
Pawel Salicki
*/
#pragma endregion

void AnimationSprite::ChangeFrame(unsigned short IDframe)
{
	//return if there isn't animation
	if (this->actualFrame == IDframe || IDframe >= this->frames.size() || IDframe < 0)
	{
		return;
	}

	this->actualFrame = IDframe; //set actual frame

	sf::IntRect rect = this->frameSize; //set current section of texture
	rect.top = rect.height * IDframe;

	this->currentSection = rect;
	this->time = 0.0f;
}

//push frame to vector of frames
void AnimationSprite::AddAnimation(Frames & frame)
{
	this->frames.push_back(frame);
}

#pragma endregion

#pragma region Setters
//setters

void AnimationSprite::SetSpritePosition(sf::Vector2f & spritePosition)
{
	this->sprite.setPosition(spritePosition);
}

#pragma endregion