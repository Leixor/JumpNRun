#pragma once
#include "StandardInclude.h"

class DrawableObject
{
public:
	DrawableObject()
	{
		this->changedPosition = true;
		this->changedSize = true;
	}
	~DrawableObject()
	{

	}

	virtual void draw(RenderWindow& window, RenderStates& shader) = 0;

	virtual void setPosition(Vector2f position) = 0;
	virtual void setRotation(float angle, Vector2f origin) = 0;
	virtual void setScale(Vector2f scale, Vector2f origin) = 0;
	virtual void setOrigin(Vector2f origin) = 0;

	virtual void setSize(Vector2f size)
	{
		throw;
	}
	virtual void setRadius(float radius)
	{
		throw;
	}
	virtual void setPointCount(size_t count)
	{
		throw;
	}
	virtual void setFillColor(Color color)
	{
		throw;
	}
	virtual void setTexture(string texturePath, bool resetRect = false)
	{
		throw;
	}
	virtual void setTexture(const Texture* texture, bool resetRect = false)
	{
		throw;
	}
	virtual void setTextureRect(IntRect rect)
	{
		throw;
	}
	virtual void setOutlineColor(Color color)
	{
		throw;
	}
	virtual void setOutlineThickness(float thickness)
	{
		throw;
	}

	virtual void rotate(float offsetAngle, Vector2f origin) = 0;
	virtual void move(Vector2f offset) = 0;
	virtual void scale(Vector2f scale, Vector2f origin) = 0;

	virtual Vector2f getPosition() = 0;
	virtual Vector2f getOrigin() = 0;
	virtual FloatRect getGlobalBounds() = 0;
	virtual Vector2f getScale() = 0;
	virtual float getRotation() = 0;

	virtual Vector2f getSize()
	{
		throw;
	}
	virtual float getRadius()
	{
		throw;
	}
	virtual size_t getPointCount()
	{
		throw;
	}
	virtual IntRect getTextureRect() 
	{
		throw;
	}
	virtual float getOutlineThickness()
	{
		return 0.0f;
	}
	virtual Color getFillColor()
	{
		throw;
	}

	virtual void updatePhysicalBody()
	{
		throw;
	}
	virtual void updateShape()
	{
		throw;
	}
protected:
	b2Body* b2body;
	bool changedPosition;
	bool changedSize;
};

