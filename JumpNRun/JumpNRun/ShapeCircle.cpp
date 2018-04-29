#include "ShapeCircle.h"

ShapeCircle::ShapeCircle(float radius, Color fillColor, float outlineThickness, Color outlineColor)
{
	this->setRadius(radius);
	this->setFillColor(fillColor);
	this->setOutlineThickness(outlineThickness);
	this->setOutlineColor(outlineColor);
}

ShapeCircle::ShapeCircle(float radius, int pointCount, Color fillColor, float outlineThickness, Color outlineColor)
{
	this->setRadius(radius);
	this->setPointCount(pointCount);
	this->setFillColor(fillColor);
	this->setOutlineThickness(outlineThickness);
	this->setOutlineColor(outlineColor);
}

ShapeCircle::~ShapeCircle()
{
}

Color ShapeCircle::getFillColor()
{
	return this->shape->getFillColor();
}

float ShapeCircle::getOutlineThickness()
{
	return this->shape->getOutlineThickness();
}

float ShapeCircle::getRadius() 
{
	return this->shape->getRadius();
}

size_t ShapeCircle::getPointCount()
{
	return this->shape->getPointCount();
}

Vector2f ShapeCircle::getSize()
{
	float radius = this->shape->getRadius();

	return Vector2f(radius, radius);
}

void ShapeCircle::setOutlineColor(Color  color)
{
	this->shape->setOutlineColor(color);
}

void ShapeCircle::setOutlineThickness(float thickness)
{
	this->shape->setOutlineThickness(thickness);
}

void ShapeCircle::setFillColor(Color color)
{
	this->shape->setFillColor(color);
}

void ShapeCircle::setPointCount(size_t count)
{
	this->shape->setPointCount(count);
}

void ShapeCircle::setRadius(float radius)
{
	this->shape->setRadius(radius);
}

