#pragma once
#include "DrawableShape.h"

class ShapeRectangle : public DrawableShape<RectangleShape>
{
public:
	ShapeRectangle() {}
	ShapeRectangle(float  width, float height,  Color fillColor = Color::Transparent, float outlineThickness = 0, Color outlineColor = Color::Transparent);
	ShapeRectangle(Vector2f size, Color fillColor = Color::Transparent, float outlineThickness = 0, Color outlineColor = Color::Transparent);
	ShapeRectangle(FloatRect rect, Color fillColor = Color::Transparent, float outlineThickness = 0, Color outlineColor = Color::Transparent);
	~ShapeRectangle();

	void setOutlineColor(Color color);
	void setOutlineThickness(float thickness);
	void setFillColor(Color color);
	void setSize(Vector2f size);

	Color getFillColor();
	float getOutlineThickness();
	Vector2f getSize();
};

