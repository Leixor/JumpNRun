#include "ShapeRectangle.h"

ShapeRectangle::ShapeRectangle(float width, float height, Color fillColor, float outlineThickness, Color outlineColor)
{
	this->setSize(Vector2f(width, height));
	this->setFillColor(fillColor);
	this->setOutlineThickness(outlineThickness);
	this->setOutlineColor(outlineColor);
}

ShapeRectangle::ShapeRectangle(Vector2f size, Color fillColor, float outlineThickness, Color outlineColor)
{
	this->setSize(size);
	this->setFillColor(fillColor);
	this->setOutlineThickness(outlineThickness);
	this->setOutlineColor(outlineColor);
}

ShapeRectangle::ShapeRectangle(FloatRect rect, Color fillColor, float outlineThickness, Color outlineColor)
{
	this->setSize(Vector2f(rect.width, rect.height));
	this->setPosition(Vector2f(rect.left, rect.top));
	this->setFillColor(fillColor);
	this->setOutlineThickness(outlineThickness);
	this->setOutlineColor(outlineColor);
}

ShapeRectangle::~ShapeRectangle()
{

}

Color ShapeRectangle::getFillColor()
{
	return this->shape->getFillColor();
}

float ShapeRectangle::getOutlineThickness()
{
	return this->shape->getOutlineThickness();
}

Vector2f  ShapeRectangle::getSize()
{
	return this->shape->getSize();
}

void ShapeRectangle::updatePhysicalBody()
{
	if (this->changedPosition)
	{
		Vector2f pos = this->shape->getPosition();
		this->b2body->SetTransform(b2Vec2(pos.x,pos.y), this->shape->getRotation());
	}
	if (this->changedSize)
	{
		//Position
		Vector2f pos = this->shape->getPosition();
		Vector2f size = this->shape->getSize();
		Vector2f scale = this->shape->getScale();
		Vector2f sizeWithScale = Vector2f(scale.x * size.x, scale.y * size.y);
		Vector2f newPos = Vector2f(pos.x + (sizeWithScale.x / 2), pos.y + (sizeWithScale.y / 2));
		this->b2body->SetTransform(b2Vec2(newPos.x, newPos.y), this->shape->getRotation());

		//Größe
		b2PolygonShape box;
		box.SetAsBox(sizeWithScale.x, sizeWithScale.y);

		//Aktuallisierung der Fixture
		b2Fixture* oldFixture = this->b2body->GetFixtureList();

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &box;
		fixtureDef.density = oldFixture->GetDensity();
		fixtureDef.friction = oldFixture->GetFriction();
		fixtureDef.restitution = oldFixture->GetRestitution();
		fixtureDef.isSensor = oldFixture->IsSensor();
		fixtureDef.filter = oldFixture->GetFilterData();

		//cast fixture to body
		this->b2body->CreateFixture(&fixtureDef);
	}

	this->changedPosition = false;
	this->changedSize = false;
}

void ShapeRectangle::setOutlineColor(Color  color)
{
	this->shape->setOutlineColor(color);
}

void ShapeRectangle::setOutlineThickness(float thickness)
{
	this->shape->setOutlineThickness(thickness);
}

void ShapeRectangle::setFillColor(Color color)
{
	this->shape->setFillColor(color);
}

void ShapeRectangle::setSize(Vector2f size)
{
	this->shape->setSize(size);
	this->changedSize = true;
}


