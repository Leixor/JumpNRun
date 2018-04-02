#pragma once

class CheckBox: public ObjectBase
{
public:
	CheckBox(function<void(bool checked, ObjectBase* type)> buttonAction, DrawableObject* buttonShape, bool checked = false);
	~CheckBox();

	void handleInput(RenderWindow& window, Event windowEvent);
private:
	bool checked;
	function<void(bool checked, ObjectBase* type)>  buttonAction;

	void checkMouseButtonCollision(RenderWindow & window);
};

