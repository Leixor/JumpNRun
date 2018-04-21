#include "Box2DWorld.h"

Box2DWorld::Box2DWorld(const b2Vec2& gravity)
	:b2World(gravity)
{
}

Box2DWorld::~Box2DWorld()
{
}
