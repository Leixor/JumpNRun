#include "standardInclude.h"

Button::Button(function<void(void)> buttonAction, Drawable& buttonShape)
	:ObjectBase(buttonShape), buttonAction(buttonAction)
{
}

Button::~Button()
{
}

bool Button::handleInput(RenderWindow & window, Event windowEvent)
{
	switch (windowEvent.type)
	{
	case Event::MouseButtonPressed:
		return this->checkMouseButtonCollision(window);
		break;
	}
	return false;
}

bool Button::checkMouseButtonCollision(RenderWindow & window)
{
	auto mouse = Mouse::getPosition(window);
	if (this->shape->getGlobalBounds().contains(float(mouse.x), float(mouse.y)))
	{
		this->buttonAction();
		return true;
	}
	return false;
}

