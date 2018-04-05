#pragma once
class ShapeSprite : public DrawableShape<Sprite>
{
public:
	ShapeSprite(string textureName, float scale, Vector2f pos = Vector2f(0,0));
	ShapeSprite(string textureName, Vector2f size, Vector2f pos = Vector2f(0, 0));
	ShapeSprite(string textureName);
	ShapeSprite(string textureName, FloatRect rect);
	~ShapeSprite();
};

