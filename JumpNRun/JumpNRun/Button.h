#pragma once

 class Button : public ObjectBase
{
public:
	Button(function<void(void)> buttonAction, DrawableObject* buttonShape);
	~Button();

	void handleInput(RenderWindow& window, Event windowEvent);
	void update();

	void draufClicken();
private:
	function<void(void)> buttonAction;
	Timer* t;

	void checkMouseButtonCollision(RenderWindow & window);
};