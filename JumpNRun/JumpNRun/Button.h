#pragma once
#include "BaseResource.h"

 class Button : public BaseResource
{
public:
	Button(function<void(void)> buttonAction, DrawableObject* buttonShape);
	~Button();

	virtual void handleEvents(RenderWindow& window, Event& windowEvent);

protected:
	function<void(void)> buttonAction;
	bool checkMouseButtonCollision(RenderWindow & window);
};