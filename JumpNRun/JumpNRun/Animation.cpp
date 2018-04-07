#include "StandardInclude.h"

Animation::Animation(function<void(void)> aniFunction)
	: aniFunction(aniFunction)
{
}

Animation::~Animation()
{
}

void Animation::run(bool loop)
{
	if (!this->isRunning())
	{
		this->loop = loop;
		this->running = true;
	}
}

void Animation::stop()
{
	if (this->isRunning())
	{
		this->running = false;
	}
}

void Animation::update()
{
	if (this->timeCount < this->aniDuration / MS_PER_UPDATE)
	{
		aniFunction();
		this->timeCount++;
	}
	else
	{
		if (this->loop)
		{
			this->timeCount = 0;
		}
		else
		{
			this->running = false;
		}
	}
}

void Animation::reset()
{
	this->timeCount = 0;
}
