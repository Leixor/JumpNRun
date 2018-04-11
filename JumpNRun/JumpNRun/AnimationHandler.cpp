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

void AnimationHandler::run(string name)
{
		animations.get(name)->run();
}

void AnimationHandler::addRotate(DrawableObject* object, string name, float angle, unsigned int millisec)
{
	float updateCount = float(millisec / MS_PER_UPDATE);
	float subAngle = float(angle / updateCount);

	/*this->animations.push(name, new Animation([&]() {
		object->rotate(subAngle, Vector2f(0,0));
	}, millisec));*/
}


