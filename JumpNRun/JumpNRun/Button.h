#pragma once

 class Button : public ObjectBase
{
public:
	Button(function<void(void)> buttonAction, DrawableObject* buttonShape);
	~Button();

	void handleInput(RenderWindow& window, Event windowEvent);

private:
	function<void(void)> buttonAction;

	void checkMouseButtonCollision(RenderWindow & window);
};