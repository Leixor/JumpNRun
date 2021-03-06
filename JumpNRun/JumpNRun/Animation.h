#pragma once
#include "SubAnimation.h"
#include "KeyFrame.h"

enum aniType {
	ROTATE = 1,
	SCALE = 2,
	MOVE = 4
};

enum eKeyFrameAction
{
	ANISTART = 1,
	ANIRESUME = 2,
	ANIPAUSE = 4,
	ANIRESTART = 8
};

class Animation : public SubAnimation
{
public:
	Animation(unsigned int updateRate = 20);
	~Animation() {}

	void update();
	void update(BaseResource* object, eAniUpdateState updateState)
	{
		this->update();
	}

	template <typename returnType>
	returnType addSubAnimation(string name, returnType animation, unsigned int time = 0)
	{
		animation->setUpdateRate(this->updateRate);
		this->subAnimations.push(name, animation);
		this->addKeyFrame(name, ANISTART, time);
		return animation;
	}
	void addSubAnimation(string name, SubAnimation* animation, unsigned int time = 0);
	void addKeyFrame(string name, eKeyFrameAction action, unsigned int time);
	void removeKeyFrame(unsigned int time);
	void addObject(BaseResource* object, eAniUpdateState updateState = ObjectAndText);
	void removeObject(BaseResource* object);
private:
	vector<KeyFrame*> keyFrames;
	UnorderdMap<eAniUpdateState, BaseResource*> objects;
	UnorderdMap<string, SubAnimation*> subAnimations;
	unsigned int updateRateCount;
};
