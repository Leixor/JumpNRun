#include "StandardInclude.h"

SubAnimation::SubAnimation()
{
	this->timeCount = 0;
}

SubAnimation::SubAnimation(unsigned int duration, BezierHandles handles) 
	: duration(duration)
{
	this->updateCount = float(duration) / MS_PER_UPDATE;
	this->factors = getBezierFactors(handles.handleOne, handles.handleTwo, unsigned int(updateCount));
	this->median = getMedian(factors);
	this->timeCount = 0;
}

SubAnimation::~SubAnimation()
{
}

void SubAnimation::start(bool loop)
{
	if (!this->running)
	{
		this->running = true;
		this->loop = loop;
		this->timeCount = 0;
	}
}

void SubAnimation::restart()
{
	this->timeCount = 0;
	this->running = true;
}

void SubAnimation::pause()
{
	if (this->running)
		this->running = false;
}

void SubAnimation::resume()
{
	if (!this->running)
		this->running = true;
}

bool SubAnimation::isRunning()
{
	return this->running;
}

unsigned int SubAnimation::getTime()
{
	return timeCount * MS_PER_UPDATE;
}
