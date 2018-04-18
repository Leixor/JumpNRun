#pragma once
#include "SubAnimation.h"

class AniRotate : public SubAnimation
{
public:
	AniRotate(unsigned int duration, float angle, Vector2f origin, BezierHandles handles = BezierHandles(0.1f, 0.1f, 0.9f, 0.9f));
	~AniRotate();

	void update(ObjectBase* object, eAniUpdateState updateState);
	void setupStepSize();

private:
	Vector2f origin;
	float subAngle;
	float angle;
};

