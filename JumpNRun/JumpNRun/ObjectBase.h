#pragma once
#include "standardInclude.h"

class ObjectBase
{
public:
	ObjectBase(Drawable& buttonShape)
	{
		if(typeid(buttonShape).operator==(typeid(RectangleShape)))
			shape = new DrawableShape<RectangleShape>();
		else if(typeid(buttonShape).operator==(typeid(CircleShape)))
			shape = new DrawableShape<CircleShape>();
		else
			shape = new DrawableShape<Sprite>();
	}
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

