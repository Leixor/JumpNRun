#include "AniRotate.h"

AniRotate::AniRotate(unsigned int duration, float angle, Vector2f origin, BezierHandles handles)
	: SubAnimation(duration, handles), origin(origin), angle(angle)
{
	
}

AniRotate::~AniRotate()
{
}

void AniRotate::update(BaseResource* object, eAniUpdateState updateState)
{
	
	switch (updateState)
	{
	case ObjectOnly:
		object->objectShape->rotate(this->subAngle * this->factors.at(this->timeCount), this->origin);
		break;
	case TextOnly:
		object->objectText->rotate(this->subAngle * this->factors.at(this->timeCount), Vector2f(this->origin.x - object->objectText->getLocalBounds().left, this->origin.y - object->objectText->getLocalBounds().top));
		break;
	case ObjectAndText:
		object->objectShape->rotate(this->subAngle * this->factors.at(this->timeCount), this->origin);
		object->objectText->rotate(this->subAngle * this->factors.at(this->timeCount), Vector2f(this->origin.x - object->objectText->getLocalBounds().left, this->origin.y - object->objectText->getLocalBounds().top));
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
