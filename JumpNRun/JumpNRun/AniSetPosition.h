#pragma once
#include "subAnimation.h"

class AniSetPosition : public SubAnimation
{
public:
	AniSetPosition(unsigned int duration, Vector2f point, BezierHandles handles = BezierHandles(0.1f, 0.1f, 0.9f, 0.9f));
	~AniSetPosition();

	void update(ObjectBase* object, eAniUpdateState updateState);
private:
	Vector2f point;
};

