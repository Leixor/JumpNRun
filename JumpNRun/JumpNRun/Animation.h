#pragma once
class AnimationHandler;
class ObjectBase;

class Animation : public SubAnimation
{
public:
	Animation() {}
	~Animation() {}

	void update();
	void update(ObjectBase* object)
	{
		this->update();
	}
	
	void addSubAnimation(string name, SubAnimation* animation, unsigned int time = 0);
	void addKeyFrame(string name, eKeyFrameAction action, unsigned int time);
	void removeKeyFrame(unsigned int time);
	void addObject(ObjectBase* object);
	void removeObject(ObjectBase* object);
private:
	vector<KeyFrame*> keyFrames;
	vector<ObjectBase*> objects;
	UnorderdMap<string, SubAnimation*> subAnimations;
};
