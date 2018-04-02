#include "standardInclude.h"

SceneStartMenu::SceneStartMenu(string name, SceneHandler * sceneHandler, RenderWindow* window)
	: Scene(name, sceneHandler, window)
{
	this->setupResources();
}

SceneStartMenu::~SceneStartMenu()
{
}

bool SceneStartMenu::setupResources()
{
	startButton = addResource<Button*>("Button_Start", new Button([&] {buttonStartAction();}, Sprite()));
	this->objects.get("Button_Start")->shape->setTexture("Textures/button_play.png");
	optionButton = addResource<Button*>("Button_Option", new Button([&] {buttonOptionAction(); }, Sprite()));
	this->objects.get("Button_Option")->shape->setTexture("Textures/button_option.png");
	endButton = addResource<Button*>("Button_End", new Button([&] {buttonEndAction(); }, Sprite()));
	this->objects.get("Button_End")->shape->setTexture("Textures/button_end.png");

	for(unsigned int i = this->objects.getIndex("Button_Start"); i <= this->objects.getIndex("Button_End"); i++)
	{
		this->objects.get(i)->shape->setPosition(Vector2f(float(200 +(i) * 450), 400));
		this->objects.get(i)->shape->setSize(Vector2f(300, 300));
	}

	this->objects.push("SnakeCover", new ObjectBase(Sprite()));
	this->objects.get("SnakeCover")->shape->setTexture("Textures/Cover_Snake.png");
	this->objects.get("SnakeCover")->shape->setPosition(Vector2f(300, 100));
	this->objects.get("SnakeCover")->shape->setSize(Vector2f(1000, 600));

	return true;
}

void SceneStartMenu::buttonStartAction()
{

}

void SceneStartMenu::buttonOptionAction()
{
	this->getSceneHandler()->addScene(new SceneOption("Option", this->getSceneHandler()), true);
	this->visible = UPDATABLE;
}

void SceneStartMenu::buttonEndAction()
{
	this->window->close();
}
