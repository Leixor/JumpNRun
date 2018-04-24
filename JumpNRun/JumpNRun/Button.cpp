#include "Button.h"

Button::Button(function<void(void)> buttonAction, DrawableObject* buttonShape)
	:ObjectBase(buttonShape), buttonAction(buttonAction)
{
}

Button::~Button()
{
}

void Button::handleEvents(RenderWindow & window, Event& windowEvent)
{
	switch (windowEvent.type)
	{
	case Event::MouseButtonPressed:
		this->checkMouseButtonCollision(window);
		break;
	}
}

bool Button::checkMouseButtonCollision(RenderWindow & window)
{
	auto mouse = Mouse::getPosition(window);
	if (this->objectShape->getGlobalBounds().contains(float(mouse.x), float(mouse.y)))
	{
		this->buttonAction();
		return true;
	}
	return false;
}

