#pragma once
#include "standardInclude.h"

class ObjectBase
{
public:
	ObjectBase(DrawableObject* buttonShape)
		: shape(buttonShape)
	{}
	~ObjectBase()
	{}

	virtual void handleInput(RenderWindow& window, Event windowEvent)
	{}
	virtual void update()
	{}
	virtual void draw(RenderWindow& window, RenderStates shades)
	{
		shape->draw(window, shades);
	}

	DrawableObject* shape;
};

