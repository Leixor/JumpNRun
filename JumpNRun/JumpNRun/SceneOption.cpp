#include "standardInclude.h"

SceneOption::SceneOption(string name, SceneHandler& sceneHandler)
	:Scene(name, sceneHandler)
{
	setupResources();
}

SceneOption::~SceneOption()
{
}

bool SceneOption::setupResources()
{
	addResource<ObjectBase*>("Background", new ObjectBase(new DrawableShape<RectangleShape>()));
	this->objects.get("Background")->shape->setPosition(Vector2f(0, 0));
	this->objects.get("Background")->shape->setSize(Vector2f(1600, 900));
	this->objects.get("Background")->shape->setFillColor(Color::Black);

	otherCheckbox = addResource<CheckBox*>("OtheBox", new CheckBox([&](bool checked, ObjectBase* type) {otherAction(); }, new DrawableShape<RectangleShape>()));
	otherCheckbox->shape->setSize(Vector2f(100, 100));
	otherCheckbox->shape->setFillColor(Color::Red);
	otherCheckbox->shape->setOutlineThickness(5);
	otherCheckbox->shape->setOutlineColor(Color::Green);
	
	colorCheckbox = addResource<CheckBox*>("ColorBox", new CheckBox([&](bool checked, ObjectBase* sender) {checkAction(checked, sender); }, new DrawableShape<RectangleShape>()));
	colorCheckbox->shape->setSize(Vector2f(10, 10));
	colorCheckbox->shape->setFillColor(Color::Red);
	colorCheckbox->shape->setOutlineThickness(5);
	colorCheckbox->shape->setOutlineColor(Color::Green);

	alignTo(*colorCheckbox->shape, *otherCheckbox->shape, BOTTOM);

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
