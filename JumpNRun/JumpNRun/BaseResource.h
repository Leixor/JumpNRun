#pragma once
#include "BaseObject.h"
#include "ShapeBase.h"
#include "ObjectText.h"
#include "AlignHelper.h"

using namespace AlignHelper;

class BaseResource : public BaseObject
{
public:
	BaseResource() :shapeVisible(NONE), textVisible(NONE)
	{}
	BaseResource(ShapeBase* shape) :shapeVisible(ALL), textVisible(NONE)
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

	eVisibilityFlags shapeVisible;
	eVisibilityFlags textVisible;

	ShapeBase* objectShape;
	ObjectText* objectText;
};

