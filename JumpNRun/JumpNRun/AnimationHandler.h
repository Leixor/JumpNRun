#pragma once
#include "StandardInclude.h"

class AnimationHandler
{
public:
	AnimationHandler() {}
	~AnimationHandler() {}

	void update()
	{
		for (unsigned int i = 0; i < this->animations.size(); i++)
		{
			if (this->animations.get(i)->isRunning())
				this->animations.get(i)->update();
		}
	}
	void run(string name)
	{
		this->animations.get(name)->start();
	}
	void restart(string name)
	{
		this->animations.get(name)->restart();
	}
	void resume(string name)
	{
		this->animations.get(name)->resume();
	}
	void pause(string name)
	{
		this->animations.get(name)->pause();
	}

	Animation* addAnimation(string name, Animation* animation)
	{
		this->animations.push(name, animation);
		return this->animations.get(name);
	}
	void removeAnimation(string name)
	{
		this->animations.remove(name);
	}
private:
	UnorderdMap<string, Animation*> animations;
};

