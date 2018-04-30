#pragma once
#include "BaseResource.h"
#include "Box2DWorld.h"
#include "BodyShapeBase.h"

class PhysicalObjectBase : public BaseResource
{
public:
	PhysicalObjectBase();
	PhysicalObjectBase(ShapeBase* shape);
	PhysicalObjectBase(FloatRect& shape, BodyShapeBase* bodyShape, Box2DWorld* sceneWorld, Vector2f velocity = Vector2f(0, 0));
	PhysicalObjectBase(ShapeBase* shape, BodyShapeBase* bodyShape, Box2DWorld* sceneWorld, Vector2f velocity = Vector2f(0, 0));
	~PhysicalObjectBase();

	virtual void update(b2World* sceneWorld);

	void setStaticBody(BodyShapeBase* shape, Box2DWorld* sceneWorld);
	void setDynamicBody(BodyShapeBase*shape , b2FixtureDef& bodyFixture, Box2DWorld* sceneWorld);
	void setKinematicBody(BodyShapeBase* shape, Box2DWorld* sceneWorld, Vector2f velocity = Vector2f(0,0));

	eVisibilityFlags bodyVisible;
	b2Body* objectBody;
	BodyShapeBase* objectBodyShape;
protected:
	void updateBody(b2World* sceneWorld);
	void updateShape();
};

