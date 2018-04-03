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
	addResource<ObjectBase*>("Background", new ObjectBase(RectangleShape()));
	this->objects.get("Background")->shape->setPosition(Vector2f(0, 0));
	this->objects.get("Background")->shape->setSize(Vector2f(1600, 900));
	this->objects.get("Background")->shape->setFillColor(Color::Yellow);
	startButton = addResource<Button*>("Button_Start", new Button([&] {buttonStartAction();}, Sprite()));
	this->objects.get("Button_Start")->shape->setTexture("Textures/button_play.png");
	optionButton = addResource<Button*>("Button_Option", new Button([&] {buttonOptionAction(); }, Sprite()));
	this->objects.get("Button_Option")->shape->setTexture("Textures/button_option.png");
	endButton = addResource<Button*>("Button_End", new Button([&] {buttonEndAction(); }, Sprite()));
	this->objects.get("Button_End")->shape->setTexture("Textures/button_end.png");

	
	this->objects.get(1)->shape->setSize(Vector2f(300, 300));
	this->objects.get(2)->shape->setSize(Vector2f(300, 300));
	this->objects.get(3)->shape->setSize(Vector2f(300, 300));
	alignTo(*startButton->shape, *this->objects.get("Background")->shape, LEFT, 300);
	startButton->shape->move(Vector2f(0, 100));
	alignNextTo(*optionButton->shape, *startButton->shape, RIGHT, 50);
	alignNextTo(*endButton->shape, *optionButton->shape, RIGHT, 50);



	this->objects.push("SnakeCover", new ObjectBase(Sprite()));
	this->objects.get("SnakeCover")->shape->setTexture("Textures/Cover_Snake.png");
	this->objects.get("SnakeCover")->shape->setPosition(Vector2f(300, 100));
	this->objects.get("SnakeCover")->shape->setSize(Vector2f(1000, 600));

	alignTo(*this->objects.get("SnakeCover")->shape, *this->objects.get("Background")->shape, TOP, 100);

	
	cout << this->objects.get("Background")->shape->getOrigin().x;

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
