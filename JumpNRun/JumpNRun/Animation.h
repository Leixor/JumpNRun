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
	Animation() {}
	~Animation() {}

	void update();
	void update(ObjectBase* object, eAniUpdateState updateState)
	{
		this->update();
	}

	template <typename returnType>
	returnType addSubAnimation(string name, returnType animation, unsigned int time = 0)
	{
		this->subAnimations.push(name, animation);
		this->addKeyFrame(name, ANISTART, time);
		return animation;
	}
	void addSubAnimation(string name, SubAnimation* animation, unsigned int time = 0);
	void addKeyFrame(string name, eKeyFrameAction action, unsigned int time);
	void removeKeyFrame(unsigned int time);
	void addObject(ObjectBase* object, eAniUpdateState updateState = ObjectAndText);
	void removeObject(ObjectBase* object);
private:
	vector<KeyFrame*> keyFrames;
	UnorderdMap<eAniUpdateState, ObjectBase*> objects;
	UnorderdMap<string, SubAnimation*> subAnimations;
};
