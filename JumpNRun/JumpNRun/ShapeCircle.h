#pragma once
#include "DrawableShape.h"

class ShapeCircle : public DrawableShape<CircleShape>
{
public:
	ShapeCircle() {}
	ShapeCircle(float  radius, Color fillColor = Color::Transparent, float outlineThickness = 0, Color outlineColor = Color::Transparent);
	ShapeCircle(float radius, int pointCount,  Color fillColor = Color::Transparent, float outlineThickness = 0, Color outlineColor = Color::Transparent);
	~ShapeCircle();

	void setOutlineColor(Color color);
	void setOutlineThickness(float thickness);
	void setFillColor(Color color);
	void setPointCount(size_t count);
	void setRadius(float radius);

	Color getFillColor();
	float getOutlineThickness();
	float getRadius();
	size_t getPointCount();
};

