#pragma once
class AnimationHandler;
class Animation
{
public:
	Animation(DrawableObject* object, AnimationHandler* sceneHandler, unsigned int millisec, string name);
	~Animation();

	void run(bool loop = false);
	void stop();
	void update();
	void reset();

	bool isRunning()
	{
		return this->running;
	}

	void addRotation(float angle, Vector2f origin = Vector2f(0.f,0.f));
	void addScale(Vector2f scale, Vector2f origin = Vector2f(0.f,0.f));
	void addMovement(Vector2f move);
	void setRotation(float angle, Vector2f origin = Vector2f(0.f, 0.f));
	void setScale(Vector2f scale, Vector2f origin = Vector2f(0.f, 0.f));
	void setMovement(Vector2f move);
	unsigned int getTime();

	function<void(void)> rotate(float angle, Vector2f origin, bool set = false);

	function<void(void)> scale(Vector2f scale, Vector2f origin, bool set = false);

	function<void(void)> move(Vector2f move, bool set = false);

	
	DrawableObject* object;
	bool running;
private:
	UnorderdMap<function<void(void)>, float> aniFunctions;
	unsigned int aniDuration;
	unsigned int timeCount;
	float updateCount;
	bool loop;
	float subAngle;
	Vector2f rotateOrigin;
	Vector2f subScale;
	Vector2f scaleOrigin;
	Vector2f subMove;
	AnimationHandler* handler;
};
