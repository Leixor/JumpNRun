#pragma once
#include "DrawableObject.h"
#include "ObjectText.h"
#include "AlignHelper.h"

using namespace AlignHelper;

enum eVisibilityFlags {
	NONE = 0,
	VISIBLE = 1,
	UPDATABLE = 2,
	INPUTABLE = 4,
	ALL = 7
};

class ObjectBase
{
public:
	
	ObjectBase(DrawableObject* buttonShape) :shapeVisible(ALL), textVisible(NONE)
	{
		objectShape = buttonShape;
	}
	~ObjectBase()
	{}

	virtual void handleInputs(RenderWindow& window)
	{}
	virtual bool handleEvents(RenderWindow& window, Event& windowEvent)
	{
		return false;
	}
	virtual void update()
	{}
	virtual void draw(RenderWindow& window, RenderStates& shades)
	{
		if(shapeVisible & VISIBLE)
			objectShape->draw(window, shades);
		if(textVisible & VISIBLE)
			window.draw(*objectText, shades);
	}
	
	virtual void addText(ObjectText* objectText) {
		this->objectText = objectText;
		textVisible = VISIBLE;
		alignTo(*this->objectText, *this->objectShape);
	}

	DrawableObject* getShape()
	{
		return this->objectShape;
	}
	ObjectText* getText()
	{
		return this->objectText;
	}

	// NEW VARIABLES
	int shapeVisible;
	int textVisible;

protected:
	DrawableObject* objectShape;
	ObjectText* objectText;
};

