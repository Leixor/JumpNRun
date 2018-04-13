#pragma once

class aniRotate : public subAnimation
{
public:
	aniRotate(unsigned int duration, float angle, Vector2f origin, BezierHandles handles = BezierHandles(0.1f,0.1f,0.9f,0.9f));
	~aniRotate();

	void update();

private:
	float subAngle;
};

