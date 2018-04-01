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
	if (windowEvent.type == Event::KeyPressed)
	{
		if (windowEvent.key.code == Keyboard::A)
		{
			draufClicken();
		}
	}
	this->checkMouseButtonCollision(window);

}

void Button::update()
{
}

void Button::checkMouseButtonCollision(RenderWindow & window)
{
	auto mouse = Mouse::getPosition(window);
	if (this->buttonShape->getGlobalBounds().contains(float(mouse.x), float(mouse.y)))
		this->buttonAction();
}

void Button::draufClicken()
{
	t = new Timer([&] {
		if (t->intervallCount < 250)
			this->buttonShape->scale(Vector2f(1.001f, 1.001f));
		else
		{
			t->intervallCount = 0;
		}
		t->intervallCount++;

	}, chrono::milliseconds(1), false);
	t->start(true);
}
