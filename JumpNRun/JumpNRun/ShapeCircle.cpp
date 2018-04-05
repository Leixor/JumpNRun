#include "standardInclude.h"



ShapeCircle::ShapeCircle(float radius, Color fillColor, float outlineThickness, Color outlineColor)
{
	this->setSize(Vector2f(radius, 30));
	this->setFillColor(fillColor);
	this->setOutlineThickness(outlineThickness);
	this->setOutlineColor(outlineColor);
}

ShapeCircle::ShapeCircle(float radius, int pointCount, Color fillColor, float outlineThickness, Color outlineColor)
{
	this->setSize(Vector2f(radius, pointCount));
	this->setFillColor(fillColor);
	this->setOutlineThickness(outlineThickness);
	this->setOutlineColor(outlineColor);
}

ShapeCircle::~ShapeCircle()
{
}
