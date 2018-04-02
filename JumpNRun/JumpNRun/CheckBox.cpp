#include "standardInclude.h"

CheckBox::CheckBox(function<void(bool checked, ObjectBase* type)> buttonAction, DrawableObject * buttonShape, bool checked)
	:ObjectBase(buttonShape), buttonAction(buttonAction)
{
}

CheckBox::~CheckBox()
{
}

void CheckBox::handleInput(RenderWindow & window, Event windowEvent)
{
	switch (windowEvent.type)
	{
	case Event::MouseButtonPressed:
		this->checkMouseButtonCollision(window);
		break;
	}
}

void CheckBox::checkMouseButtonCollision(RenderWindow & window)
{
	auto mouse = Mouse::getPosition(window);
	if (this->buttonShape->getGlobalBounds().contains(float(mouse.x), float(mouse.y)))
	{
		this->checked = !this->checked;
		this->buttonAction(this->checked, this);
	}
}