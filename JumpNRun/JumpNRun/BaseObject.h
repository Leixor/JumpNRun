#pragma once
#include "StandardInclude.h"

enum eVisibilityFlags {
	NONE = 0,
	VISIBLE = 1,
	UPDATABLE = 2,
	INPUTABLE = 4,
	ALL = 7
};

class BaseObject
{
public:
	
	BaseObject()
	{}
	~BaseObject()
	{}

	virtual void handleInputs(RenderWindow& window)
	{}
	virtual void handleEvents(RenderWindow& window, Event& windowEvent)
	{
	}
	virtual void update()
	{}
	virtual void draw(RenderWindow& window, RenderStates& shades)
	{
	}
	
	eVisibilityFlags visibility;
};

