#pragma once
#include "StandardInclude.h"

class SubAnimation;
class KeyFrame
{
public:
	KeyFrame(unsigned int timeStamp)
	{
		this->timeStamp = timeStamp;
	}
	~KeyFrame();

	void addAction(string name, function<void(string)> action)
	{
		this->actions.push_back(action);
		this->names.push_back(name);
	}
	void activateKeyFrame()
	{
		for (unsigned int i = 0; i < this->actions.size(); i++)
			this->actions.at(i)(this->names.at(i));
	}
	unsigned int getTimeStamp()
	{
		return this->timeStamp;
	}

private:
	vector<function<void(string)>> actions;
	vector<string> names;
	unsigned int timeStamp;
};

