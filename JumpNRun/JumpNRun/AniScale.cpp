#include "AniScale.h"

AniScale::AniScale(unsigned int duration, Vector2f scale, Vector2f origin, BezierHandles handles)
	: SubAnimation(duration, handles), origin(origin), scale(scale)
{
	
}

AniScale::~AniScale()
{
}

void AniScale::update(ObjectBase * object, eAniUpdateState updateState)
{
	
	switch (updateState)
	{
	case ObjectOnly:
		object->getShape()->setScale(object->getShape()->getScale() + this->subScale * this->factors.at(this->timeCount), this->origin);
		break;
	case TextOnly:
		break;
	case ObjectAndText:
		object->getShape()->setScale(object->getShape()->getScale() + this->subScale * this->factors.at(this->timeCount), this->origin);
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

void AniScale::setupStepSize()
{
	this->subScale = Vector2f(((scale.x / this->updateCount) / this->median), ((scale.y / this->updateCount) / this->median));;
}
