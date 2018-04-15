#include "StandardInclude.h"

aniRotate::aniRotate(unsigned int duration, float angle, Vector2f origin, BezierHandles handles) : subAnimation(duration, handles)
{
	this->subAngle = (angle / this->updateCount) / this->median;
}

aniRotate::~aniRotate()
{
}

void aniRotate::update() 
{

}
