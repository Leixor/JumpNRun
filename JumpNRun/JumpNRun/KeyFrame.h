#pragma once
#include "StandardInclude.h"


class KeyFrame
{
public:
	KeyFrame(unsigned int timeStamp)
	{
		this->timeStamp = timeStamp;
	}
	~KeyFrame();

	void addAction(function<void(void)> action)
	{
		this->actions.push_back(action);
	}
	void activateKeyFrame()
	{
		for (unsigned int i = 0; i < this->actions.size(); i++)
			this->actions.at(i)();
	}
	unsigned int getTimeStamp()
	{
		return this->timeStamp;
	}

private:
	vector<function<void(void)>> actions;
	unsigned int timeStamp;
};

