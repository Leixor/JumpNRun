#pragma once
#include "SubAnimation.h"

class AniMove : public SubAnimation
{
public:
	AniMove(unsigned int duration, Vector2f direction , BezierHandles handles = BezierHandles(0.1f, 0.1f, 0.9f, 0.9f));
	~AniMove();

	void update(BaseResource* object, eAniUpdateState updateState);
private: 
	Vector2f subDirection;
	Vector2f direction;

	void setupStepSize();
};

