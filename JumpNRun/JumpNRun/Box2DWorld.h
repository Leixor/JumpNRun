#pragma once
#include "StandardInclude.h"

class Box2DWorld : public b2World
{
public:
	Box2DWorld(const b2Vec2& gravity);
	~Box2DWorld();
};

