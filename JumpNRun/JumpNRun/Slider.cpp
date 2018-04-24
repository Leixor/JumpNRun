#include "Slider.h"

Slider::Slider(function<void(float)> sliderAction, DrawableObject* sliderShape)
	: sliderAction(sliderAction), Button([&] { active = true;}, sliderShape)
{
	this->active = false;
}

Slider::~Slider()
{
}

void Slider::handleEvents(RenderWindow & window, Event & windowEvent)
{
	Button::handleEvents(window, windowEvent);
	if (windowEvent.type == Event::MouseButtonReleased)
		this->active = false;
}

void Slider::handleInputs(RenderWindow & window)
{
	if (this->active)
	{
		auto mouse = Mouse::getPosition(window);
		float tmp = (mouse.x - this->objectShape->getPosition().x) / this->objectShape->getSize().x;
		if (tmp > 1.0f)
			tmp = 1.0f;
		else if (tmp < 0.0f)
			tmp = 0.0f;
		this->sliderAction(tmp);
	}
}
  