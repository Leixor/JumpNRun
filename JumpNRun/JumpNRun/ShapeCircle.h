#pragma once
class ShapeCircle : public DrawableShape<CircleShape>
{
public:
	ShapeCircle(float  radius, Color fillColor = Color::Transparent, float outlineThickness = 0, Color outlineColor = Color::Transparent);
	ShapeCircle(float radius, int pointCount,  Color fillColor = Color::Transparent, float outlineThickness = 0, Color outlineColor = Color::Transparent);
	~ShapeCircle();
};

