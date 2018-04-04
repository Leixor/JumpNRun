#include "standardInclude.h"

CheckBox::CheckBox(function<void(bool checked, ObjectBase* type)> buttonAction, Drawable& buttonShape, bool checked)
	:ObjectBase(buttonShape), buttonAction(buttonAction)
{
}

CheckBox::~CheckBox()
{
}

bool CheckBox::handleEvents(RenderWindow & window, Event windowEvent)
{
	switch (windowEvent.type)
	{
	case Event::MouseButtonPressed:
		this->checkMouseButtonCollision(window);
	}
	return false;
}
bool CheckBox::getState()
{
	return this->checked;
}

bool CheckBox::checkMouseButtonCollision(RenderWindow & window)
{
	auto mouse = Mouse::getPosition(window);
	if (this->shape->getGlobalBounds().contains(float(mouse.x), float(mouse.y)))
	{
		this->checked = !this->checked;
		this->buttonAction(this->checked, this);
		return true;
	}
	return false;
}