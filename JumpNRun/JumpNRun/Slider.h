#pragma once

class Slider : public Button
{
public:
	Slider(function<void(float)> sliderAction, DrawableObject* sliderShape);
	~Slider();

	bool handleEvents(RenderWindow& window, Event& windowEvent);
	void handleInputs(RenderWindow& window);
private:
	bool active;
	function<void(float)> sliderAction;
};
