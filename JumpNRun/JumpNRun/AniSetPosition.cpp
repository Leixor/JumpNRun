#include "AniSetPosition.h"

AniSetPosition::AniSetPosition(unsigned int duration, Vector2f point, BezierHandles handles)
	:SubAnimation(duration, handles), point(point)
{
}

AniSetPosition::~AniSetPosition()
{
}

void AniSetPosition::update(ObjectBase * object, eAniUpdateState updateState)
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

	Vector2f distance;
	Vector2f holeDistance;
	Vector2f distanceStep;

	switch (updateState)
	{
	case ObjectOnly:
		distance = this->point - object->getShape()->getPosition();
		holeDistance = distance / (1.0f - (actualTotal / total));
		distanceStep = Vector2f(((holeDistance.x / this->updateCount) / this->median), ((holeDistance.y / this->updateCount) / this->median));
		object->getShape()->move(distanceStep * this->factors.at(this->timeCount));
		break;
	case TextOnly:
		distance = this->point - object->getText()->getPosition();
		holeDistance = distance / (1.0f - (actualTotal / total));
		distanceStep = Vector2f(((holeDistance.x / this->updateCount) / this->median), ((holeDistance.y / this->updateCount) / this->median));
		object->getText()->move(distanceStep * this->factors.at(this->timeCount));
		break;
	case ObjectAndText:
		distance = this->point - object->getShape()->getPosition();
		holeDistance = distance / (1.0f - (actualTotal / total));
		distanceStep = Vector2f(((holeDistance.x / this->updateCount) / this->median), ((holeDistance.y / this->updateCount) / this->median));
		object->getShape()->move(distanceStep * this->factors.at(this->timeCount));

		distance = this->point - object->getText()->getPosition();
		holeDistance = distance / (1.0f - (actualTotal / total));
		distanceStep = Vector2f(((holeDistance.x / this->updateCount) / this->median), ((holeDistance.y / this->updateCount) / this->median));
		object->getText()->move(distanceStep * this->factors.at(this->timeCount));
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
