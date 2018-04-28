#pragma once
#include "StandardInclude.h"

class Box2DWorld : public b2World
{
public:
	Box2DWorld(const b2Vec2& gravity);
	~Box2DWorld();

	void setPositionAccuracy(int accuracy);
	void setVelocityAccuracy(int accuracy);

	void update(float frequency);

private:
	int positionAccuracy;
	int velocityAccuracy;
};

