#pragma once
#include "standardInclude.h"

class ObjectBase
{
public:
	
	ObjectBase(DrawableObject* buttonShape) :shapeVisible(ALL), textVisible(NONE)
	{
		shape = buttonShape;
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
			shape->draw(window, shades);
		if(textVisible & VISIBLE)
			window.draw(*objectText, shades);
	}
	
		
	// NEW FUNCTIONS
	virtual void addText(string text, Font& font) {
		objectText = new Text();
		this->objectText->setFont(font);
		this->objectText->setString(text);
		textVisible = VISIBLE;
	}
	virtual void setText(string text) {
		this->objectText->setString(text);
	}
	virtual void setTextSize(int size) {
		this->objectText->setCharacterSize(size);
	}

	DrawableObject* shape;

	// NEW VARIABLES
	int shapeVisible;
	int textVisible;
	Text* objectText;
};

