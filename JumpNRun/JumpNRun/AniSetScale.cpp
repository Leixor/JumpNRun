#include "AniSetScale.h"

AniSetScale::AniSetScale(unsigned int duration, Vector2f scale, Vector2f origin, BezierHandles handles)
	:SubAnimation(duration, handles), origin(origin), scale(scale)
{
}

AniSetScale::~AniSetScale()
{
}

void AniSetScale::update(ObjectBase * object, eAniUpdateState updateState)
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

	Vector2f distanceScale;
	Vector2f holeScale;
	Vector2f scaleStep;

	switch (updateState)
	{
	case ObjectOnly:
		distanceScale = this->scale - object->getShape()->getScale();
		holeScale = distanceScale / (1.0f - (actualTotal / total));
		scaleStep = Vector2f(((holeScale.x / this->updateCount) / this->median), ((holeScale.y / this->updateCount) / this->median));
		object->getShape()->setScale(object->getShape()->getScale() + scaleStep * this->factors.at(this->timeCount), this->origin);
		break;
	case TextOnly:
		distanceScale = this->scale - object->getText()->getScale();
		holeScale = distanceScale / (1.0f - (actualTotal / total));
		scaleStep = Vector2f(((holeScale.x / this->updateCount) / this->median), ((holeScale.y / this->updateCount) / this->median));
		object->getText()->setScale(object->getText()->getScale() + scaleStep * this->factors.at(this->timeCount), this->origin);
		break;
	case ObjectAndText:
		distanceScale = this->scale - object->getShape()->getScale();
		holeScale = distanceScale / (1.0f - (actualTotal / total));
		scaleStep = Vector2f(((holeScale.x / this->updateCount) / this->median), ((holeScale.y / this->updateCount) / this->median));
		object->getShape()->setScale(object->getShape()->getScale() + scaleStep * this->factors.at(this->timeCount), this->origin);

		distanceScale = this->scale - object->getText()->getScale();
		holeScale = distanceScale / (1.0f - (actualTotal / total));
		scaleStep = Vector2f(((holeScale.x / this->updateCount) / this->median), ((holeScale.y / this->updateCount) / this->median));
		object->getText()->setScale(object->getText()->getScale() + scaleStep * this->factors.at(this->timeCount), this->origin);
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
