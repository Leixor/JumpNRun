#include "StandardInclude.h"

aniRotate::aniRotate(unsigned int duration, float angle, Vector2f origin, BezierHandles handles) 
	: subAnimation(duration, handles), origin(origin)
{
	this->subAngle = (angle / this->updateCount) / this->median;
}

aniRotate::~aniRotate()
{
}

void aniRotate::update(ObjectBase* object)
{
	if (this->getTime() <= this->duration)
	{
		object->shape->rotate(this->subAngle * this->factors.at(this->timeCount), this->origin);
		this->timeCount++;
	}
	else if (loop)
		this->timeCount = 0;
}
