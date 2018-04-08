#pragma once

class AnimationHandler
{
public:
	AnimationHandler();
	~AnimationHandler();

	void update();

	void rotate(DrawableObject* object, string name, float angle, int millisec);

private:
	UnorderdMap<string, Animation*> animations;
};

