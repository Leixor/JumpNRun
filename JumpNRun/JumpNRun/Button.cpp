#include "standardInclude.h"

Button::Button(function<void(void)> buttonAction, DrawableObject * buttonShape)
	:ObjectBase(buttonShape), buttonAction(buttonAction)
{
}

Button::~Button()
{
}

void Button::handleInput(RenderWindow & window, Event windowEvent)
{
	switch (windowEvent.type)
	{
	case Event::MouseButtonPressed:
		this->checkMouseButtonCollision(window);
		break;
	}
}

void Button::checkMouseButtonCollision(RenderWindow & window)
{
	auto mouse = Mouse::getPosition(window);
	if (this->shape->getGlobalBounds().contains(float(mouse.x), float(mouse.y)))
		this->buttonAction();
}

