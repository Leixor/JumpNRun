#pragma once
#include "DrawableShape.h"

class ShapeSprite : public DrawableShape<Sprite>
{
public:
	ShapeSprite(string textureName, float scale, Vector2f pos = Vector2f(0,0));
	ShapeSprite(Texture* texture, float scale, Vector2f pos = Vector2f(0, 0));
	ShapeSprite(string textureName, Vector2f size, Vector2f pos = Vector2f(0, 0));
	ShapeSprite(string textureName);
	ShapeSprite(string textureName, FloatRect rect);
	~ShapeSprite();

	void setTexture(string texturePath, bool resetRect = false);
	void setTexture(const Texture* texture, bool resetRect = false);
	void setTextureRect(IntRect rect);
	void setSize(Vector2f size);
	
	IntRect getTextureRect();
	Vector2f getSize();
};

