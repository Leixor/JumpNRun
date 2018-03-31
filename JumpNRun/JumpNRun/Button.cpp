#include "standardInclude.h"

Button::Button(function<void(void)> buttonAction, DrawableShape<Drawable>* buttonShape)
	: buttonShape(buttonShape), buttonAction(buttonAction)
{
}

Button::~Button()
{
}

void Button::checkMouseButtonCollision(RenderWindow & window)
{
	auto mousePosition = Mouse::getPosition(window);

	if (NewType* v = dynamic_cast<NewType*>(old)) {
		// old was safely casted to NewType
		v->doSomething();
	}
	if (this->buttonShape<RectangleShape>->getGlobalBounds().contains(float(mousePosition.x), float(mousePosition.y)))
		this->buttonAction();
}
