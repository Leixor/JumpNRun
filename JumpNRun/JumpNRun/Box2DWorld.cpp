#include "Box2DWorld.h"

Box2DWorld::Box2DWorld(const b2Vec2& gravity)
	:b2World(gravity), velocityAccuracy(8), positionAccuracy(3)
{
}

Box2DWorld::~Box2DWorld()
{
}

void Box2DWorld::setPositionAccuracy(int accuracy)
{
	this->positionAccuracy = accuracy;
}

void Box2DWorld::setVelocityAccuracy(int accuracy)
{
	this->velocityAccuracy = accuracy;
}

void Box2DWorld::update(float frequency)
{
	this->Step(frequency, this->velocityAccuracy, this->positionAccuracy);
}
