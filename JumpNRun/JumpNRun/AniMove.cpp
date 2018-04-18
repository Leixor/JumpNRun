#include "AniMove.h"

AniMove::AniMove(unsigned int duration, Vector2f direction, BezierHandles handles)
	:SubAnimation(duration, handles), direction(direction)
{
	
}

AniMove::~AniMove()
{
}

void AniMove::update(ObjectBase* object, eAniUpdateState updateState)
{
	if (this->getTime() < this->duration)
	{
		switch (updateState)
		{
		case ObjectOnly:
			object->getShape()->move(this->subDirection * this->factors.at(this->timeCount));
			break;
		case TextOnly:
			object->getText()->move(this->subDirection * this->factors.at(this->timeCount));
			break;
		case ObjectAndText:
			object->getShape()->move(this->subDirection * this->factors.at(this->timeCount));
			object->getText()->move(this->subDirection * this->factors.at(this->timeCount));
			break;
		}
	}
}

void AniMove::setupStepSize()
{
	this->subDirection = Vector2f(((direction.x / this->updateCount) / this->median), ((direction.y / this->updateCount) / this->median));
}
	else if (loop)
		this->timeCount = 0;
	else
		this->running = false;
}