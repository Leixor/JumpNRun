#include "StandardInclude.h"

Slider::Slider(function<void(float)> sliderAction, DrawableObject* sliderShape)
	: sliderAction(sliderAction), Button([&] { active = true;}, sliderShape)
{
	this->active = false;
}

Slider::~Slider()
{
}

bool Slider::handleEvents(RenderWindow & window, Event & windowEvent)
{
	Button::handleEvents(window, windowEvent);
	if (windowEvent.type == Event::MouseButtonReleased)
		this->active = false;
	return false;
}

void Slider::handleInputs(RenderWindow & window)
{
	if (this->active)
	{
		auto mouse = Mouse::getPosition(window);
		float tmp = (mouse.x - this->shape->getPosition().x) / this->shape->getSize().x;
		if (tmp > 1.0f)
			tmp = 1.0f;
		else if (tmp < 0.0f)
			tmp = 0.0f;
		this->sliderAction(tmp);
	}
}
  