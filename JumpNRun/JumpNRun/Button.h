#pragma once

 class Button : public ObjectBase
{
public:
	Button(function<void(void)> buttonAction, DrawableObject* buttonShape);
	~Button();

	virtual bool handleInput(RenderWindow& window, vector<Event>& windowEvent);

protected:
	function<void(void)> buttonAction;
	bool checkMouseButtonCollision(RenderWindow & window);
};