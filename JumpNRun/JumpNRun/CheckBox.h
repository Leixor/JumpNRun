#pragma once
#include "BaseResource.h"

class CheckBox: public BaseResource
{
public:
	CheckBox(function<void(bool checked, BaseResource* type)> buttonAction, ShapeBase* buttonShape, bool checked = false);
	~CheckBox();

	void handleEvents(RenderWindow& window, Event& windowEvent);

	// Test zum veranschaulichen
	bool getState();
private:
	bool checked;
	function<void(bool checked, BaseResource* type)>  buttonAction;
	bool checkMouseButtonCollision(RenderWindow & window);
};

