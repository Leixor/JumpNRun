#pragma once

class Animation
{
public:
	Animation(function<void(void)> aniFunction);
	~Animation();

	void run(bool loop = false);
	void stop();
	void update();
	void reset();

	bool isRunning()
	{
		return this->running;
	}
private:
	function<void(void)> aniFunction;
	unsigned int aniDuration;
	unsigned int timeCount;
	bool loop;
	bool running;
};
