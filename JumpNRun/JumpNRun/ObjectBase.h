#pragma once
#include "standardInclude.h"

class ObjectBase
{
public:
	ObjectBase(DrawableObject* buttonShape)
		: buttonShape(buttonShape)
	{}
	~ObjectBase()
	{}

	virtual void handleInput(RenderWindow& window, Event windowEvent)
	{}
	virtual void update()
	{}
	virtual void draw(RenderWindow& window, RenderStates shades)
	{
		buttonShape->draw(window, shades);
	}

	DrawableObject* buttonShape;
};

