#include "AniSpriteSheet.h"



AniSpriteSheet::AniSpriteSheet(unsigned int duration, unsigned int frames, Texture& texture) : SubAnimation(duration), spriteTexture(&texture)
{
	this->frameDuration = this->updateCount / frames;
}


AniSpriteSheet::~AniSpriteSheet()
{
}

void AniSpriteSheet::addFrame(IntRect* frame)
{
	this->spriteFrames.push_back(frame);
}

void AniSpriteSheet::update(ObjectBase * object)
{
	if (timeCount == 0  || timeCount == 1)
	{
		object->getShape()->setTexture(*spriteTexture);
	}
	int currentFrame = timeCount / frameDuration;
	if (currentFrame == spriteFrames.size())
		currentFrame = spriteFrames.size()-1;
	if (this->getTime() < this->duration)
	{
		object->getShape()->setTextureRect(*spriteFrames.at(currentFrame));
	}
	else if (loop)
		this->timeCount = 0;
	else
	{
		this->running = false;
	}
		
}
