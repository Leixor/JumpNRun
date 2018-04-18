#include "AniScale.h"

AniScale::AniScale(unsigned int duration, Vector2f scale, Vector2f origin, BezierHandles handles)
	: SubAnimation(duration, handles), origin(origin)
{
	//not working
	this->subScale = Vector2f(((scale.x / this->updateCount) / this->median), ((scale.y / this->updateCount) / this->median));
}

AniScale::~AniScale()
{
}

void AniScale::update(ObjectBase * object, eAniUpdateState updateState)
{
	//not working
	if (this->getTime() < this->duration)
	{
		switch (updateState)
		{
		case ObjectOnly:
			object->getShape()->scale(this->subScale * this->factors.at(this->timeCount), this->origin);
			break;
		case TextOnly:
			object->getText()->scale(this->subScale * this->factors.at(this->timeCount), this->origin);
			break;
		case ObjectAndText:
			object->getShape()->scale(this->subScale * this->factors.at(this->timeCount), this->origin);
			object->getText()->scale(this->subScale * this->factors.at(this->timeCount), this->origin);
			break;
		}
	}
}
