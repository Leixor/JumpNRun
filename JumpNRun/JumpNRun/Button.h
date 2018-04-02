#pragma once

 class Button : public ObjectBase
{
public:
	Button(function<void(void)> buttonAction, Drawable& buttonShape);
	~Button();

	virtual void handleInput(RenderWindow& window, Event windowEvent);

protected:
	function<void(void)> buttonAction;
	void checkMouseButtonCollision(RenderWindow & window);
};