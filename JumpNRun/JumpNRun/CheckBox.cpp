#include "CheckBox.h"

CheckBox::CheckBox(function<void(bool checked, BaseResource* type)> buttonAction, DrawableObject* buttonShape, bool checked)
	:BaseResource(buttonShape), buttonAction(buttonAction)
{
}

CheckBox::~CheckBox()
{
}

void CheckBox::handleEvents(RenderWindow & window, Event& windowEvent)
{
	switch (windowEvent.type)
	{
	case Event::MouseButtonPressed:
		this->checkMouseButtonCollision(window);
		break;
	}
}
bool CheckBox::getState()
{
	return this->checked;
}

bool CheckBox::checkMouseButtonCollision(RenderWindow & window)
{
	auto mouse = Mouse::getPosition(window);
	if (this->objectShape->getGlobalBounds().contains(float(mouse.x), float(mouse.y)))
	{
		this->checked = !this->checked;
		this->buttonAction(this->checked, this);
		return true;
	}
	return false;
}