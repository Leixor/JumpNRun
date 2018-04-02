#pragma once

class CheckBox: public ObjectBase
{
public:
	CheckBox(function<void(bool checked, ObjectBase* type)> buttonAction, DrawableObject* buttonShape, bool checked = false);
	~CheckBox();

	void handleInput(RenderWindow& window, Event windowEvent);

	// Test zum veranschaulichen
	bool getState();
private:
	bool checked;
	function<void(bool checked, ObjectBase* type)>  buttonAction;
	void checkMouseButtonCollision(RenderWindow & window);
};

