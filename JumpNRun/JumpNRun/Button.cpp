#include "standardInclude.h"

Button::Button(IntRect buttonRect, function<void(void)> buttonAction)
	:buttonAction(buttonAction)
{
	this->setPosition(buttonRect.left, buttonRect.top);
	this->setSize(Vector2f(buttonRect.width, buttonRect.height));
}

Button::~Button()
{
}

void Button::checkMouseButtonCollision(RenderWindow & window)
{
	auto mousePosition = Mouse::getPosition(window);
	if (this->getGlobalBounds().contains(mousePosition.x, mousePosition.y));
		this->buttonAction();
}
