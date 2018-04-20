#include "AniSetRotation.h"

AniSetRotation::AniSetRotation(unsigned int duration, float angle, Vector2f origin, BezierHandles handles)
	:SubAnimation(duration, handles), angle(angle), origin(origin)
{
}

AniSetRotation::~AniSetRotation()
{
}

void AniSetRotation::update(ObjectBase * object, eAniUpdateState updateState)
{
	float total = 0.0f;
	float actualTotal = 0.0f;
	for (unsigned int i = 0; i < this->factors.size(); i++)
	{
		total += factors[i];
	}
	for (unsigned int i = 0; i < this->timeCount; i++)
	{
		actualTotal += factors[i];
	}

	float distanceAngle;
	float holeAngle;
	float distanceStep;

	switch (updateState)
	{
	case ObjectOnly:
		distanceAngle = this->angle - object->getShape()->getRotation();
		holeAngle = distanceAngle / (1.0f - (actualTotal / total));
		distanceStep = (holeAngle / this->updateCount) / this->median;
		object->getShape()->rotate(distanceStep * this->factors.at(this->timeCount), this->origin);
		break;
	case TextOnly:
		distanceAngle = this->angle - object->getText()->getRotation();
		holeAngle = distanceAngle / (1.0f - (actualTotal / total));
		distanceStep = (holeAngle / this->updateCount) / this->median;
		object->getText()->rotate(distanceStep * this->factors.at(this->timeCount), origin);
		break;
	case ObjectAndText:
		distanceAngle = this->angle - object->getShape()->getRotation();
		holeAngle = distanceAngle / (1.0f - (actualTotal / total));
		distanceStep = (holeAngle / this->updateCount) / this->median;
		object->getShape()->rotate(distanceStep * this->factors.at(this->timeCount), this->origin);

		distanceAngle = this->angle - object->getText()->getRotation();
		holeAngle = distanceAngle / (1.0f - (actualTotal / total));
		distanceStep = (holeAngle / this->updateCount) / this->median;
		object->getText()->rotate(distanceStep * this->factors.at(this->timeCount), origin);
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
