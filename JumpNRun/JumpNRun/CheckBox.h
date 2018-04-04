#pragma once

class CheckBox: public ObjectBase
{
public:
	CheckBox(function<void(bool checked, ObjectBase* type)> buttonAction, DrawableObject* buttonShape, bool checked = false);
	~CheckBox();

	bool handleEvents(RenderWindow& window, Event windowEvent);

	// Test zum veranschaulichen
	bool getState();
private:
	bool checked;
	function<void(bool checked, ObjectBase* type)>  buttonAction;
	bool checkMouseButtonCollision(RenderWindow & window);
};

