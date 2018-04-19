#include "AniRotate.h"

AniRotate::AniRotate(unsigned int duration, float angle, Vector2f origin, BezierHandles handles)
	: SubAnimation(duration, handles), origin(origin), angle(angle)
{
	
}

AniRotate::~AniRotate()
{
}

void AniRotate::update(ObjectBase* object, eAniUpdateState updateState)
{
	
	switch (updateState)
	{
	case ObjectOnly:
		object->getShape()->rotate(this->subAngle * this->factors.at(this->timeCount), this->origin);
		break;
	case TextOnly:
		object->getText()->rotate(this->subAngle * this->factors.at(this->timeCount), Vector2f(this->origin.x - object->getText()->getLocalBounds().left, this->origin.y - object->getText()->getLocalBounds().top));
		break;
	case ObjectAndText:
		object->getShape()->rotate(this->subAngle * this->factors.at(this->timeCount), this->origin);
		object->getText()->rotate(this->subAngle * this->factors.at(this->timeCount), Vector2f(this->origin.x - object->getText()->getLocalBounds().left, this->origin.y - object->getText()->getLocalBounds().top));
		break;
	}
	
	if (this->getTime() >= (this->duration - this->updateRate))
	{
		if (loop)
			this->timeCount = 0;
		else
			this->running = false;
	}	
}


void AniRotate::setupStepSize()
{
	this->subAngle = (angle / this->updateCount) / this->median;
}
