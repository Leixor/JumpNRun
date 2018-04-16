#include "StandardInclude.h"

AniRotate::AniRotate(unsigned int duration, float angle, Vector2f origin, BezierHandles handles)
	: SubAnimation(duration, handles), origin(origin)
{
	this->subAngle = (angle / this->updateCount) / this->median;
}

AniRotate::~AniRotate()
{
}

void AniRotate::update(ObjectBase* object)
{
	if (this->getTime() < this->duration)
	{
		object->shape->rotate(this->subAngle * this->factors.at(this->timeCount), this->origin);
		this->timeCount++;
	}
	else if (loop)
		this->timeCount = 0;
	else
		this->running = false;
}
