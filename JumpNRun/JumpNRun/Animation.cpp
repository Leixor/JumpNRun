#include "Animation.h"

Animation::Animation(unsigned int updateRate)
{
	this->updateRateCount = 1;
	this->updateRate = updateRate;
}

void Animation::update()
{
	if (updateRateCount >= updateRate / MS_PER_UPDATE)
	{
		bool behindLastKeyFrame = true;

		for (unsigned int i = 0; i < this->keyFrames.size(); i++)
		{
			if (this->keyFrames.at(i)->getTimeStamp() == this->getTime())
			{
				this->keyFrames.at(i)->activateKeyFrame();
			}
			if (this->keyFrames.at(i)->getTimeStamp() >= this->getTime())
				behindLastKeyFrame = false;
		}

		bool noAnimationRunning = true;
		for (unsigned int i = 0; i < this->subAnimations.size(); i++)
		{
			if (this->subAnimations.get(i)->isRunning())
			{
				for (unsigned int j = 0; j < this->objects.size(); j++)
				{
					this->subAnimations.get(i)->update(this->objects.get(j), this->objects.getIterator(j));
				}

				this->subAnimations.get(i)->increaseTimeAnimation();
				noAnimationRunning = false;
			}
		}

		if (behindLastKeyFrame && noAnimationRunning)
			if (this->loop)
			{
				this->timeCount = 0;
				this->update();
			}	
			else
				this->running = false;
		else
			this->timeCount++;
		updateRateCount = 1;
	}
	else
	{
		updateRateCount++;
	}
}

void Animation::addSubAnimation(string name, SubAnimation* animation, unsigned int time)
{
	animation->setUpdateRate(this->updateRate);
	this->subAnimations.push(name, animation);
	this->addKeyFrame(name, ANISTART, time);
}

void Animation::addKeyFrame(string name, eKeyFrameAction action, unsigned int time)
{
	KeyFrame* frame = nullptr;
	for (unsigned int i = 0; i < this->keyFrames.size(); i++)
	{
		if (time == this->keyFrames.at(i)->getTimeStamp())
			frame = this->keyFrames.at(i);
	}

	if (frame == nullptr)
	{
		frame = new KeyFrame(time);
		this->keyFrames.push_back(frame);
	}

	switch (action)
	{
	case ANISTART:
		frame->addAction([&, name](){ this->subAnimations.get(name)->start(); });
		break;
	case ANIPAUSE:
		frame->addAction([&, name]() {this->subAnimations.get(name)->pause(); });
		break;
	case ANIRESTART:
		frame->addAction([&, name]() {this->subAnimations.get(name)->restart(); });
		break; 
	case ANIRESUME:
		frame->addAction([&, name]() {this->subAnimations.get(name)->resume(); });
		break;
	}

}

void Animation::removeKeyFrame(unsigned int time)
{
	for (unsigned int i = 0; i < this->keyFrames.size(); i++)
	{
		if (time == this->keyFrames.at(i)->getTimeStamp())
		{
			this->keyFrames.erase(this->keyFrames.begin() + i);
			return;
		}
	}
}

void Animation::addObject(BaseResource* object, eAniUpdateState updateState)
{
	this->objects.push(updateState, object);
}

void Animation::removeObject(BaseResource* object)
{
	for (unsigned int i = 0; i < this->objects.size(); i++)
	{
		if (this->objects.get(i) == object)
		{
			this->objects.remove(i);
			return;
		}
	}
}
