#pragma once
#include "subAnimation.h"

class AniSetScale : public SubAnimation
{
public:
	AniSetScale(unsigned int duration, Vector2f scale, Vector2f origin, BezierHandles handles = BezierHandles(0.1f, 0.1f, 0.9f, 0.9f));
	~AniSetScale();

	void update(ObjectBase* object, eAniUpdateState updateState);
private:
	Vector2f scale;
	Vector2f origin;
};
