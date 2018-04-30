#include "PhysicalObjectBase.h"

PhysicalObjectBase::PhysicalObjectBase()
	: bodyVisible(NONE)
{
}

PhysicalObjectBase::PhysicalObjectBase(ShapeBase * shape)
	:BaseResource(shape), bodyVisible(NONE)
{
}

PhysicalObjectBase::PhysicalObjectBase(FloatRect shape, b2Shape & bodyShape, Box2DWorld* sceneWorld, Vector2f velocity)
	: bodyVisible(UPDATABLE)
{
	b2BodyDef bodyDef;
	if(velocity == Vector2f(0,0))
		bodyDef.type = b2_staticBody;
	else
		bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(shape.left + shape.width, shape.top + shape.height);

	this->objectBody = sceneWorld->CreateBody(&bodyDef);
	this->objectBody->CreateFixture(&bodyShape, 0.0f);
	this->objectBody->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
}

PhysicalObjectBase::PhysicalObjectBase(ShapeBase * shape, b2Shape & bodyShape, Box2DWorld* sceneWorld, Vector2f velocity)
	: BaseResource(shape), bodyVisible(UPDATABLE)
{
	Vector2f pos = this->objectShape->getPosition();
	Vector2f size = this->objectShape->getSize();
	Vector2f scale = this->objectShape->getScale();
	Vector2f scsi = Vector2f(size.x * scale.x, size.y * scale.y);

	b2BodyDef bodyDef;
	if (velocity == Vector2f(0, 0))
		bodyDef.type = b2_staticBody;
	else
		bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.x + scsi.x / 2, pos.y + scsi.y / 2);

	this->objectBody = sceneWorld->CreateBody(&bodyDef);
	this->objectBody->CreateFixture(&bodyShape, 0.0f);
	this->objectBody->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
}

PhysicalObjectBase::~PhysicalObjectBase()
{
}

void PhysicalObjectBase::update()
{
	if (this->bodyVisible & UPDATABLE)
	{
		b2Vec2 pos = this->objectBody->GetPosition();
		Vector2f size = this->objectShape->getSize();
		Vector2f scale = this->objectShape->getScale();
		Vector2f scsi = Vector2f(size.x * scale.x, size.y * scale.y);
		this->objectShape->setPosition(Vector2f(pos.x - scsi.x / 2, pos.y - scsi.y / 2));
	}
}

void PhysicalObjectBase::setStaticBody(b2Shape & shape, Box2DWorld* sceneWorld)
{
	Vector2f pos = this->objectShape->getPosition();
	Vector2f size = this->objectShape->getSize();
	Vector2f scale = this->objectShape->getScale();
	Vector2f scsi = Vector2f(size.x * scale.x, size.y * scale.y);

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(pos.x + scsi.x / 2, pos.y + scsi.y / 2);
	
	this->objectBody = sceneWorld->CreateBody(&bodyDef);
	this->objectBody->CreateFixture(&shape, 0.0f);

	this->bodyVisible = UPDATABLE;
}

void PhysicalObjectBase::setDynamicBody(b2FixtureDef& fixture, Box2DWorld* sceneWorld)
{
	Vector2f pos = this->objectShape->getPosition();
	Vector2f size = this->objectShape->getSize();
	Vector2f scale = this->objectShape->getScale();
	Vector2f scsi = Vector2f(size.x * scale.x, size.y * scale.y);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.x + scsi.x / 2, pos.y + scsi.y / 2);

	this->objectBody = sceneWorld->CreateBody(&bodyDef);
	this->objectBody->CreateFixture(&fixture);

	this->bodyVisible = UPDATABLE;
}

void PhysicalObjectBase::setKinematicBody(b2Shape & shape, Box2DWorld* sceneWorld, Vector2f velocity)
{
	Vector2f pos = this->objectShape->getPosition();
	Vector2f size = this->objectShape->getSize();
	Vector2f scale = this->objectShape->getScale();
	Vector2f scsi = Vector2f(size.x * scale.x, size.y * scale.y);

	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(pos.x + scsi.x / 2, pos.y + scsi.y / 2);

	this->objectBody = sceneWorld->CreateBody(&bodyDef);
	this->objectBody->CreateFixture(&shape, 0.0f);
	this->objectBody->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));

	this->bodyVisible = UPDATABLE;
}
