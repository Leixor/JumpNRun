#pragma once
#include "subAnimation.h"

class AniSetRotation : public SubAnimation
{
public:
	AniSetRotation(unsigned int duration, float angle, Vector2f origin, BezierHandles handles = BezierHandles(0.1f, 0.1f, 0.9f, 0.9f));
	~AniSetRotation();

	void update(ObjectBase* object, eAniUpdateState updateState);
private:
	float angle;
	Vector2f origin;
};
