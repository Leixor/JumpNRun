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
	addResource<ObjectBase*>("Background", new ObjectBase(CircleShape()));
	this->objects.get("Background")->shape->setPosition(Vector2f(0, 0));
	this->objects.get("Background")->shape->setSize(Vector2f(1600, 900));
	this->objects.get("Background")->shape->setFillColor(Color::Cyan);
	colorCheckbox = addResource<CheckBox*>("CheckBox", new CheckBox([&](bool checked, ObjectBase* sender) { this->checkAction(checked, sender); },RectangleShape()));
	this->objects.get("CheckBox")->shape->setFillColor(Color::Blue);
	this->objects.get("CheckBox")->shape->setOutlineColor(Color::Cyan);
	this->objects.get("CheckBox")->shape->setOutlineThickness(10);
	this->objects.get("CheckBox")->shape->setPosition(Vector2f(100, 100));
	this->objects.get("CheckBox")->shape->setSize(Vector2f(500, 500));

	otherCheckbox = addResource<CheckBox*>("otherBox", new CheckBox([&](bool checked, ObjectBase* sender) { this->otherAction(); },RectangleShape()));
	this->objects.get("otherBox")->shape->setFillColor(Color::Red);
	this->objects.get("otherBox")->shape->setOutlineColor(Color::Green);
	this->objects.get("otherBox")->shape->setOutlineThickness(10);
	this->objects.get("otherBox")->shape->setPosition(Vector2f(700, 100));
	this->objects.get("otherBox")->shape->setSize(Vector2f(500, 500));

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
	if (colorCheckbox->getState()) {
		this->getSceneHandler()->getSceneByName("Menu")->visible = ALL;
		this->getSceneHandler()->deleteScene(this->sceneName);
	}
	else
		otherCheckbox->shape->setVisibility(NONE);
}
