#pragma once
class AnimationHandler;
class Animation
{
public:
	Animation(AnimationHandler* sceneHandler, string name);
	~Animation();

	void run(bool loop = false);
	void stop();
	void update();
	void reset();

	bool isRunning()
	{
		return this->running;
	}

	
	void addAniToObject(DrawableObject* object);
	bool running;
private:
	AnimationHandler* handler;
	
};
