#include "standardInclude.h"

Button::Button(IntRect buttonRect, String texturePath, function<void(void)> buttonAction)
	:RectShape(buttonRect, texturePath) , buttonAction(buttonAction)
{
}

Button::~Button()
{
}

void Button::checkMouseButtonCollision(RenderWindow & window)
{
	auto mousePosition = Mouse::getPosition(window);
	if (this->getGlobalBounds().contains(mousePosition.x, mousePosition.y))
		this->buttonAction();
}

