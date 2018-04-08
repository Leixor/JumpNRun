#include "StandardInclude.h"

AnimationHandler::AnimationHandler()
{
}

AnimationHandler::~AnimationHandler()
{
}

void AnimationHandler::update()
{
	for (unsigned int i = 0; i < this->animations.size(); i++)
	{
		if (this->animations.get(i)->isRunning())
			this->animations.get(i)->update();
	}
}

void AnimationHandler::rotate(DrawableObject* object, string name, float angle, int millisec)
{
	float updateCount = float(millisec / MS_PER_UPDATE);

	/*this->animations.push(name, new Animation([&]() {
		object->rotate()
	}));*/
}
