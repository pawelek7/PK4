#pragma once

#include <SFML/Graphics.hpp>

#include "StateOfProgram.h"

#include <vector>

struct Animation;

class AnimatedTexture : public StateOfProgram
{
	std::vector<Animation> animated_texture;
	sf::IntRect sizeOfAnimation, displayBox;
	float looped = 0.0f;
	int frame = 0;

	//tmp variables
	sf::IntRect rect_tmp;
	int tmp_frame = 0;
	float tmp_length = 0.0f;

public:
	AnimatedTexture() = default;
	AnimatedTexture(const sf::IntRect & sizeOfAnimation);

	void SetNextFrame(int frame);


	void UpdateObject(float elapsedTime) override;
	void DrawObject() override;
	void InitializeObject() override;

	struct Animation
	{
		short start, end;
		float fps;
		Animation(short start, short end, float length)
			: start(start), end(end), fps(fps) {}

	};

	//getters
};