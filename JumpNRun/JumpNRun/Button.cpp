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
	this->checkMouseButtonCollision(window);
}

void Button::checkMouseButtonCollision(RenderWindow & window)
{
	auto mouse = Mouse::getPosition(window);
	if (this->buttonShape->getGlobalBounds().contains(float(mouse.x), float(mouse.y)))
		this->buttonAction();
}
