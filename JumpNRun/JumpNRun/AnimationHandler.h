#pragma once

class AnimationHandler
{
public:
	AnimationHandler();
	~AnimationHandler();

	void update();
	void run(string name, bool loop = false);
	void restart(string name);
	void resume(string name);
	void pause(string name);

	Animation* addAnimation(string name, Animation* animation);
	void removeAnimation(string name);
private:
	UnorderdMap<string, Animation*> animations;
};

