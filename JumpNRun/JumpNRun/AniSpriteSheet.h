#pragma once
#include "SubAnimation.h"
class AniSpriteSheet : public SubAnimation
{
public:
	AniSpriteSheet(unsigned int duration, unsigned int frames, Texture& texture);
	~AniSpriteSheet();
	void addFrame(IntRect* frame);
	void update(ObjectBase* object, eAniUpdateState updateState);
private:
	vector<IntRect*> spriteFrames;
	unsigned int frameDuration;
	Texture* spriteTexture;
	unsigned int frames;

	void setupStepSize();
};

