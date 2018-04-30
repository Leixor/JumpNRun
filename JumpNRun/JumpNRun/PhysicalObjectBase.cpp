#include "PhysicalObjectBase.h"

PhysicalObjectBase::PhysicalObjectBase()
	: bodyVisible(NONE)
{
}

PhysicalObjectBase::PhysicalObjectBase(ShapeBase * shape)
	:BaseResource(shape), bodyVisible(NONE)
{
}

PhysicalObjectBase::PhysicalObjectBase(FloatRect& shape, BodyShapeBase* bodyShape, Box2DWorld* sceneWorld, Vector2f velocity)
	: bodyVisible(UPDATABLE)
{
	b2BodyDef bodyDef;
	if(velocity == Vector2f(0,0))
		bodyDef.type = b2_staticBody;
	else
		bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(shape.left + shape.width / 2, shape.top + shape.height / 2);

	this->objectBody = sceneWorld->CreateBody(&bodyDef);

	this->objectBodyShape = bodyShape;
	this->objectBody->CreateFixture(this->objectBodyShape->updateSize(Vector2f(shape.width, shape.height)), 0.0f);

	this->objectBody->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
}

PhysicalObjectBase::PhysicalObjectBase(ShapeBase * shape, BodyShapeBase* bodyShape, Box2DWorld* sceneWorld, Vector2f velocity)
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
		bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(pos.x + scsi.x / 2, pos.y + scsi.y / 2);

	this->objectBody = sceneWorld->CreateBody(&bodyDef);

	this->objectBodyShape = bodyShape;
	this->objectBody->CreateFixture(this->objectBodyShape->updateSize(scsi), 0.0f);

	this->objectBody->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
}

PhysicalObjectBase::~PhysicalObjectBase()
{
}

void PhysicalObjectBase::update(b2World* sceneWorld)
{
	if (this->bodyVisible & UPDATABLE)
	{
		this->updateBody(sceneWorld);
		this->updateShape();

		//Resetten der Werte
		this->objectShape->hasPosUpdated();
	}
}

void PhysicalObjectBase::setStaticBody(BodyShapeBase* shape, Box2DWorld* sceneWorld)
{
	Vector2f pos = this->objectShape->getPosition();
	Vector2f size = this->objectShape->getSize();
	Vector2f scale = this->objectShape->getScale();
	Vector2f scsi = Vector2f(size.x * scale.x, size.y * scale.y);

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(pos.x + scsi.x / 2, pos.y + scsi.y / 2);
	this->objectBody = sceneWorld->CreateBody(&bodyDef);

	this->objectBodyShape = shape;
	this->objectBody->CreateFixture(this->objectBodyShape->updateSize(scsi), 0.0f);

	this->bodyVisible = UPDATABLE;
}

void PhysicalObjectBase::setDynamicBody(BodyShapeBase* shape, b2FixtureDef& fixture, Box2DWorld* sceneWorld)
{
	Vector2f pos = this->objectShape->getPosition();
	Vector2f size = this->objectShape->getSize();
	Vector2f scale = this->objectShape->getScale();
	Vector2f scsi = Vector2f(size.x * scale.x, size.y * scale.y);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.x + scsi.x / 2, pos.y + scsi.y / 2);

	this->objectBody = sceneWorld->CreateBody(&bodyDef);

	this->objectBodyShape = shape;
	fixture.shape = this->objectBodyShape->updateSize(scsi);
	this->objectBody->CreateFixture(&fixture);

	this->bodyVisible = UPDATABLE;
}

void PhysicalObjectBase::setKinematicBody(BodyShapeBase* shape, Box2DWorld* sceneWorld, Vector2f velocity)
{
	Vector2f pos = this->objectShape->getPosition();
	Vector2f size = this->objectShape->getSize();
	Vector2f scale = this->objectShape->getScale();
	Vector2f scsi = Vector2f(size.x * scale.x, size.y * scale.y);

	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(pos.x + scsi.x / 2, pos.y + scsi.y / 2);
	this->objectBody = sceneWorld->CreateBody(&bodyDef);

	this->objectBodyShape = shape;
	this->objectBody->CreateFixture(this->objectBodyShape->updateSize(scsi), 0.0f);

	this->objectBody->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));

	this->bodyVisible = UPDATABLE;
}

void PhysicalObjectBase::updateBody(b2World * sceneWorld)
{
	Vector2f pos = this->objectShape->getPosition();
	Vector2f size = this->objectShape->getSize();
	Vector2f scale = this->objectShape->getScale();
	Vector2f scsi = Vector2f(size.x * scale.x, size.y * scale.y);

	if (this->objectShape->hasPosUpdated())
	{
		b2Vec2 newPos = b2Vec2(pos.x + scsi.x / 2, pos.y + scsi.y / 2);
		this->objectBody->SetTransform(newPos, this->objectShape->getRotation());
	}

	if (this->objectShape->hasSizeUpdated())
	{
		b2Fixture* oldFixture = this->objectBody->GetFixtureList();
		b2FixtureDef fixture;

		fixture.shape = this->objectBodyShape->updateSize(scsi);

		fixture.density = oldFixture->GetDensity();
		fixture.filter = oldFixture->GetFilterData();
		fixture.friction = oldFixture->GetFriction();
		fixture.isSensor = oldFixture->IsSensor();
		fixture.restitution = oldFixture->GetRestitution();
		
		this->objectBody->CreateFixture(&fixture);
	}
}

void PhysicalObjectBase::updateShape()
{
	b2Vec2 pos = this->objectBody->GetPosition();
	Vector2f size = this->objectShape->getSize();
	Vector2f scale = this->objectShape->getScale();
	Vector2f scsi = Vector2f(size.x * scale.x, size.y * scale.y);
	this->objectShape->setPosition(Vector2f(pos.x - scsi.x / 2, pos.y - scsi.y / 2));
}
