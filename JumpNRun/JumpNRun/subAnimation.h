#pragma once
#include "StandardInclude.h"
class subAnimation
{
public:
	// Time duration in millisec
	subAnimation(unsigned int duration, BezierHandles handles = BezierHandles(0.1f,0.1f,0.9f,0.9f)) : duration(duration) 
	{
		updateCount = duration / MS_PER_UPDATE;
		factors = getBezierFactors(handles.handleOne, handles.handleTwo, updateCount);
		median = getMedian(factors);
	}
	~subAnimation() {}

	virtual unsigned int getTime()
	{
		return timeCount * MS_PER_UPDATE;
	}

	virtual void update() = 0;
	


protected: 

	float updateCount;
	unsigned int timeCount;
	unsigned int duration;
	vector<float> factors;
	float median;
	bool loop;


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
			for (int i = 0; i < size; i++)
			{
				total += scores[i];
			}
			float median = total / (float)size;
			return median;
		}
	}
};

