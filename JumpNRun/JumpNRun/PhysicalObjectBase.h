#pragma once
#include "BaseResource.h"

class PhysicalObjectBase : public BaseResource
{
public:
	PhysicalObjectBase();
	~PhysicalObjectBase();

	virtual void setBox2DBody(b2Shape& shape, b2FixtureDef& fixture, b2World& sceneWorld)
	{}
protected:
	b2Body* b2body;
};

