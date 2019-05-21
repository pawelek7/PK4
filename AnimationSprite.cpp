#include "AnimationSprite.h"

#pragma region Constructors

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

void AnimationSprite::UpdateAnimation(const float elapsedTime)
{
	if (this->actualFrame >= this->frames.size() || this->actualFrame < 0)
	{
		return;
	}

	float duration = this->frames[actualFrame].duration;

	if (static_cast<int>((this->time + elapsedTime) / duration) > static_cast<int>(this->time / duration))
	{
		int frame = static_cast<int>((time + elapsedTime) / duration);
		frame %= this->frames[actualFrame].GetLenght();

		sf::IntRect rect = this->frameSize;
		rect.left = rect.width * frame;
		rect.top = rect.height * this->actualFrame;
		this->currentSection = rect;
	}

	this->time += elapsedTime;

	if (this->time > duration * this->frames[actualFrame].GetLenght())
	{
		this->time = 0.0f;
	}
}

void AnimationSprite::ChangeFrame(unsigned short IDframe)
{
	if (this->actualFrame == IDframe || IDframe >= this->frames.size() || IDframe < 0)
	{
		return;
	}

	this->actualFrame = IDframe;

	sf::IntRect rect = this->frameSize;
	rect.top = rect.height * IDframe;

	this->currentSection = rect;
	this->time = 0.0f;
}

void AnimationSprite::AddAnimation(Frames & frame)
{
	this->frames.push_back(frame);
}

#pragma endregion

#pragma region Setters

void AnimationSprite::SetSpritePosition(sf::Vector2f spritePosition)
{
	this->sprite.setPosition(spritePosition);
}

#pragma endregion