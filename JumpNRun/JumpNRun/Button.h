#pragma once

 class Button : public ObjectBase
{
public:
	Button(function<void(void)> buttonAction, DrawableObject* buttonShape);
	~Button();

	virtual bool handleEvents(RenderWindow& window, Event windowEvent);

protected:
	function<void(void)> buttonAction;
	bool checkMouseButtonCollision(RenderWindow & window);
};