#pragma once
#include "SubAnimation.h"

class AniScale : public SubAnimation
{
public:
	AniScale(unsigned int duration, Vector2f scale, Vector2f origin, BezierHandles handles = BezierHandles(0.1f, 0.1f, 0.9f, 0.9f));
	~AniScale();

	void update(ObjectBase* object, eAniUpdateState updateState);
private:
	Vector2f subScale;
	Vector2f origin;
};

