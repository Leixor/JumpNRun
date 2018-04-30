#pragma once
#include "BaseResource.h"
#include "Box2DWorld.h"

class PhysicalObjectBase : public BaseResource
{
public:
	PhysicalObjectBase();
	PhysicalObjectBase(ShapeBase* shape);
	PhysicalObjectBase(FloatRect shape, b2Shape& bodyShape, Box2DWorld* sceneWorld, Vector2f velocity = Vector2f(0, 0));
	PhysicalObjectBase(ShapeBase* shape, b2Shape& bodyShape, Box2DWorld* sceneWorld, Vector2f velocity = Vector2f(0, 0));
	~PhysicalObjectBase();

	virtual void update();

	void setStaticBody(b2Shape& bodyShape, Box2DWorld* sceneWorld);
	void setDynamicBody(b2FixtureDef& bodyFixture, Box2DWorld* sceneWorld);
	void setKinematicBody(b2Shape& shape, Box2DWorld* sceneWorld, Vector2f velocity = Vector2f(0,0));

	eVisibilityFlags bodyVisible;
	b2Body* objectBody;
};

