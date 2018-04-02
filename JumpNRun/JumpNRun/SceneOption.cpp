#include "standardInclude.h"

SceneOption::SceneOption(string name, SceneHandler * sceneHandler)
	:Scene(name, sceneHandler)
{
	setupResources();
}

SceneOption::~SceneOption()
{
}

bool SceneOption::setupResources()
{
	this->objects.push("CheckBox", new CheckBox([&](bool checked, ObjectBase* sender){ this->checkAction(checked, sender); }, new DrawableShape<RectangleShape>()));
	this->objects.get("CheckBox")->buttonShape->setFillColor(Color::Blue);
	this->objects.get("CheckBox")->buttonShape->setOutlineColor(Color::Cyan);
	this->objects.get("CheckBox")->buttonShape->setOutlineThickness(10);
	this->objects.get("CheckBox")->buttonShape->setPosition(Vector2f(100, 100));
	this->objects.get("CheckBox")->buttonShape->setSize(Vector2f(500, 500));

	return true;
}

void SceneOption::checkAction(bool checked, ObjectBase * sender)
{
	if(checked)
		sender->buttonShape->setFillColor(Color::White);
	else
		sender->buttonShape->setFillColor(Color::Blue);
}
