#pragma once
#include "BaseObject.h"
#include "DrawableObject.h"
#include "ObjectText.h"
#include "AlignHelper.h"

using namespace AlignHelper;

class BaseResource : public BaseObject
{
public:
	BaseResource() :shapeVisible(NONE), textVisible(NONE)
	{}
	BaseResource(DrawableObject* shape) :shapeVisible(ALL), textVisible(NONE)
	{
		objectShape = shape;
	}
	~BaseResource()
	{}

	virtual void draw(RenderWindow& window, RenderStates& shades = RenderStates())
	{
		if (shapeVisible & VISIBLE)
			objectShape->draw(window, shades);
		if (textVisible & VISIBLE)
			window.draw(*objectText, shades);
	}
	virtual void addText(ObjectText* objectText) {
		this->objectText = objectText;
		textVisible = VISIBLE;
		alignTo(*this->objectText, *this->objectShape);
	}

	int shapeVisible;
	int textVisible;

	DrawableObject* objectShape;
	ObjectText* objectText;
};

