#pragma once
#include "Button.h"

class Slider : public Button
{
public:
	Slider(function<void(float)> sliderAction, ShapeBase* sliderShape);
	~Slider();

	void handleEvents(RenderWindow& window, Event& windowEvent);
	void handleInputs(RenderWindow& window);
private:
	bool active;
	function<void(float)> sliderAction;
};

