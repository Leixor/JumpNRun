#pragma once
#include "standardInclude.h"

class DrawableObject
{
public:
	DrawableObject()
	{
	}
	~DrawableObject()
	{

	}

	virtual void draw(RenderWindow& window, RenderStates shader) = 0;

	virtual void setSize(Vector2f size) = 0;
	virtual void setPosition(Vector2f pos) = 0;
	virtual void setRotation(float angle) = 0;
	virtual void setOrigin(Vector2f origin) = 0;
	
	virtual void setFillColor(Color color) = 0;
	virtual void setTexture(String texturePath) = 0;
	virtual void setTextureRect(IntRect textureRect) = 0;
	virtual void setOutlineColor(Color color) = 0;
	virtual void setOutlineThickness(float thickness) = 0; 
	virtual void setScale(Vector2f scale) = 0;

	virtual void rotate(float offsetAngle, Vector2f origin) = 0;
	virtual void move(Vector2f offset) = 0;
	virtual void scale(Vector2f offset) = 0;

	virtual Vector2f getSize() = 0;
	virtual Vector2f getPosition() = 0;
	virtual Vector2f getOrigin() = 0;
	virtual IntRect getTextureRect() = 0;
	virtual FloatRect getGlobalBounds() = 0;
	virtual Vector2f getScale() = 0;
	virtual float getRotation() = 0;
	virtual float getOutlineThickness() = 0;
};

