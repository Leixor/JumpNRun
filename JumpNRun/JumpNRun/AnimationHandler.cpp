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

void AnimationHandler::run(string name, bool loop)
{
	this->animations.get(name)->start(loop);
}

void AnimationHandler::restart(string name)
{
	this->animations.get(name)->restart();
}

void AnimationHandler::resume(string name)
{
	this->animations.get(name)->resume();
}

void AnimationHandler::pause(string name)
{
	this->animations.get(name)->pause();
}

Animation* AnimationHandler::addAnimation(string name, Animation* animation)
{
	this->animations.push(name, animation);
	return this->animations.get(name);
}

void AnimationHandler::removeAnimation(string name)
{
	this->animations.remove(name);
}
