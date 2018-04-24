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
	
	ObjectBase() :shapeVisible(NONE), textVisible(NONE)
	{}
	ObjectBase(DrawableObject* shape) :shapeVisible(ALL), textVisible(NONE)
	{
		objectShape = shape;
	}
	~ObjectBase()
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

	DrawableObject* const getShape()
	{
		return this->objectShape;
	}
	ObjectText* const getText()
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

