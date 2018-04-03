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
	

	addResource<ObjectBase*>("Background", new ObjectBase(RectangleShape()));
	this->objects.get("Background")->shape->setPosition(Vector2f(0, 0));
	this->objects.get("Background")->shape->setSize(Vector2f(1600, 900));
	this->objects.get("Background")->shape->setFillColor(Color::Black);
	


	

	return true;
}

void SceneOption::checkAction(bool checked, ObjectBase * sender)
{
	if(colorCheckbox->getState())
		sender->shape->setFillColor(Color::White);
	else
		sender->shape->setFillColor(Color::Blue);
}

void SceneOption::otherAction()
{
	if (otherCheckbox->getState())
		otherCheckbox->shape->setFillColor(Color::White);
	else
		otherCheckbox->shape->setFillColor(Color::Blue);
}
