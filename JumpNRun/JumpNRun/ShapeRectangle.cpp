#include "standardInclude.h"



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
