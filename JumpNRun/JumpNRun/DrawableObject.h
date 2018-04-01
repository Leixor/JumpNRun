#pragma once
#include "standardInclude.h"

class DrawableObject
{
public:
	DrawableObject(bool visibility = false)
	{
		this->visibility = visibility;
	}
	~DrawableObject()
	{

	}

	virtual void draw(RenderWindow& window, RenderStates shader) = 0;

	virtual void setSize(Vector2f size) = 0;
	virtual void setPosition(Vector2f pos) = 0;
	virtual void setRotation(float angle, bool additional = false) = 0;
	
	virtual void setFillColor(Color color) = 0;
	virtual void setTexture(String texturePath) = 0;
	virtual void setTextureRect(IntRect textureRect) = 0;
	virtual void setOutlineColor(Color color) = 0;
	virtual void setOutlineThickness(float thickness) = 0;

	virtual Vector2f getSize() = 0;
	virtual Vector2f getPosition() = 0;
	virtual IntRect getTextureRect() = 0;
	virtual FloatRect getGlobalBounds() = 0;

	void setVisibility(bool visibility)
	{
		this->visibility = visibility;
	}
protected:
	bool getVisibility()
	{
		return visibility;
	}
private:
	bool visibility;
};

