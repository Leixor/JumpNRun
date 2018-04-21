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

void ShapeRectangle::setOutlineColor(Color  color)
{
	this->shape->setOutlineColor(color);
}

void ShapeRectangle::setOutlineThickness(float thickness)
{
	this->shape->setOutlineThickness(thickness);
}

void ShapeRectangle::setFillColor(Color  color)
{
	this->shape->setFillColor(color);
}

void ShapeRectangle::setSize(Vector2f  size)
{
	this->shape->setSize(size);
}


