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
	// Alte Syntax ohne das man das Original behaltet
	/*this->objects.push("Background", new ObjectBase(new DrawableShape<RectangleShape>()));
	this->objects.get("Background")->buttonShape->setPosition(Vector2f(0, 0));
	this->objects.get("Background")->buttonShape->setSize(Vector2f(1600, 900));
	this->objects.get("Background")->buttonShape->setFillColor(Color::Cyan);
	this->objects.push("Button_Start", new Button([&] {buttonStartAction(); }, new DrawableShape<Sprite>()));
	this->objects.get("Button_Start")->buttonShape->setTexture("Textures/button_play.png");
	this->objects.push("Button_Option", new Button([&] {buttonOptionAction(); }, new DrawableShape<Sprite>()));
	this->objects.get("Button_Option")->buttonShape->setTexture("Textures/button_option.png");
	this->objects.push("Button_End", new Button([&] {buttonEndAction(); }, new DrawableShape<Sprite>()));
	this->objects.get("Button_End")->buttonShape->setTexture("Textures/button_end.png");*/

	addResource<ObjectBase*>("Background", new ObjectBase(new DrawableShape<RectangleShape>()));
	this->objects.get("Background")->shape->setPosition(Vector2f(0, 0));
	this->objects.get("Background")->shape->setSize(Vector2f(1600, 900));
	this->objects.get("Background")->shape->setFillColor(Color::Cyan);
	startButton = addResource<Button*>("Button_Start", new Button([&] {buttonStartAction();}, new DrawableShape<Sprite>()));
	this->objects.get("Button_Start")->shape->setTexture("Textures/button_play.png");
	optionButton = addResource<Button*>("Button_Option", new Button([&] {buttonOptionAction(); }, new DrawableShape<Sprite>()));
	this->objects.get("Button_Option")->shape->setTexture("Textures/button_option.png");
	endButton = addResource<Button*>("Button_End", new Button([&] {buttonEndAction(); }, new DrawableShape<Sprite>()));
	this->objects.get("Button_End")->shape->setTexture("Textures/button_end.png");

	for(unsigned int i = 1; i < this->objects.size(); i++)
	{
		this->objects.get(i)->shape->setPosition(Vector2f(float(200 +(i - 1) * 450), 400));
		this->objects.get(i)->shape->setSize(Vector2f(300, 300));
	}

	this->objects.push("SnakeCover", new ObjectBase(new DrawableShape<Sprite>()));
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
	this->getSceneHandler()->addScene(new SceneOption("Option", this->getSceneHandler()));
	this->visible = NONE;
}

void SceneStartMenu::buttonEndAction()
{
	this->window->close();
}
