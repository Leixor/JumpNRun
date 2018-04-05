#pragma once
class ShapeRectangle : public DrawableShape<RectangleShape>
{
public:
	ShapeRectangle(float  width, float height,  Color fillColor = Color::Transparent, float outlineThickness = 0, Color outlineColor = Color::Transparent);
	ShapeRectangle(Vector2f size, Color fillColor = Color::Transparent, float outlineThickness = 0, Color outlineColor = Color::Transparent);
	ShapeRectangle(FloatRect rect, Color fillColor = Color::Transparent, float outlineThickness = 0, Color outlineColor = Color::Transparent);
	~ShapeRectangle();
};
