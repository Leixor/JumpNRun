#include "standardInclude.h"

Button::Button(IntRect buttonRect, function<void(void)> buttonAction)
	: buttonShape(), buttonAction(buttonAction)
{
	this->buttonShape.setPosition(buttonRect.left, buttonRect.top);
	this->buttonShape.setSize(Vector2f(buttonRect.width, buttonRect.height));

}

Button::~Button()
{
}

void Button::checkMouseButtonCollision(float mouseX, float mouseY)
{
	if (this->buttonShape.getGlobalBounds().contains(Vector2f(mouseX, mouseY)))
		this->buttonAction();
	
}
