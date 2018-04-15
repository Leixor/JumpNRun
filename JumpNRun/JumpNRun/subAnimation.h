#pragma once
#include "StandardInclude.h"
class ObjectBase;
class subAnimation
{
public:
	// Time duration in millisec
	subAnimation()
	{
		this->timeCount = 0;
	}
	subAnimation(unsigned int duration, BezierHandles handles = BezierHandles(0.1f,0.1f,0.9f,0.9f)) : duration(duration) 
	{
		this->updateCount = float(duration) / MS_PER_UPDATE;
		this->factors = getBezierFactors(handles.handleOne, handles.handleTwo, unsigned int(updateCount));
		this->median = getMedian(factors);
		this->timeCount = 0;
	}
	~subAnimation() {}

	virtual void update(ObjectBase* object) = 0;

	void start(bool loop = false)
	{
		if (!this->running)
		{
			this->running = true;
			this->loop = loop;
			this->timeCount = 0;
		}
	}
	void restart()
	{
		this->timeCount = 0;
		this->running = true;
	}
	void pause()
	{
		if (this->running)
			this->running = false;
	}
	void resume()
	{
		if (!this->running)
			this->running = true;
	}

	bool isRunning()
	{
		return this->running;
	}
	unsigned int getTime()
	{
		return timeCount * MS_PER_UPDATE;
	}
protected: 
	//Anzahl der Updates die eine Animation braucht, bis sie fertig ist
	float updateCount;
	//Der aktuelle Schritt der Animation
	unsigned int timeCount;
	//Die Länge der kompletten Animation in MS
	unsigned int duration;

	bool running;
	bool loop;

	vector<float> factors;
	float median;


	virtual void setupAnimation() {}

	// Private Helferfunktionen
	vector<float> getBezierFactors(Vector2f P1, Vector2f P2, unsigned int steps)
	{
		vector<float> factors;

		Vector2f P0 = Vector2f(0.0f, 0.0f);
		Vector2f P3 = Vector2f(1.f, 1.f);

		Vector2f Q0 = 3.f*(P1 - P0);
		Vector2f Q1 = 3.f*(P2 - P1);
		Vector2f Q2 = 3.f*(P3 - P2);

		for (float i = 0; i < steps; i++)
		{
			Vector2f notNormalized = 3.f* pow((1.f - i / steps), 2.f)*Q0 + (6 * (1.f - i / steps))*i / steps * Q1 + 3.f*pow(i / steps, 2)*Q2;
			float d = sqrt(pow(notNormalized.x, 2) + pow(notNormalized.y, 2));
			Vector2f normalized = Vector2f(notNormalized.x / d, notNormalized.y / d);
			factors.push_back(float(normalized.y / normalized.x));
		}
		return factors;
	}
	float getMedian(vector<float> scores)
	{
		size_t size = scores.size();
		float total = 0;
		if (size == 0)
		{
			return 0;  // Undefined, really.
		}
		else if (size == 1)
		{
			return scores[0];
		}
		else
		{
			for (size_t i = 0; i < size; i++)
			{
				total += scores[i];
			}
			float median = total / (float)size;
			return median;
		}
	}
};

