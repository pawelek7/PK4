#include "AnimatedTexture.h"

AnimatedTexture::AnimatedTexture(const sf::IntRect & sizeOfAnimation) : sizeOfAnimation(sizeOfAnimation)
{}

void AnimatedTexture::UpdateObject(float elapsedTime)
{
	tmp_length = this->animated_texture[frame].fps;

	if (static_cast<int>((looped + elapsedTime) / tmp_length) > static_cast<int>(looped / tmp_length))
	{
		tmp_frame = static_cast<int>((looped + elapsedTime) / tmp_length);
		tmp_frame %= (this->animated_texture[frame].end - this->animated_texture[frame].start + 1);
		rect_tmp = this->sizeOfAnimation;
		rect_tmp.left = rect_tmp.width * tmp_frame;
		rect_tmp.top = rect_tmp.height * this->frame;
		this->displayBox = rect_tmp;
	}

	this->looped += elapsedTime;

	if (this->looped > tmp_length * (this->animated_texture[frame].end - this->animated_texture[frame].start + 1))
	{
		looped = 0.0f;
	}
}

void AnimatedTexture::SetNextFrame(int frame)
{
	if (this->frame == frame || frame >= this->animated_texture.size())
		return;

	this->frame = frame;
	rect_tmp = this->displayBox;
	rect_tmp.top = rect_tmp.height * frame;
	this->displayBox = rect_tmp;
	this->looped = 0.0f;
}

void  AnimatedTexture::DrawObject()
{

}
void  AnimatedTexture::InitializeObject()
{

}