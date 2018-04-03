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
	font = new Font();
	this->font->loadFromFile("Textures/cool.ttf");
	
	addResource<ObjectBase*>("Background", new ObjectBase(RectangleShape()));
	this->objects.get("Background")->shape->setPosition(Vector2f(0, 0));
	this->objects.get("Background")->shape->setSize(Vector2f(1600, 900));
	this->objects.get("Background")->shape->setFillColor(Color::Black);

	startButton = addResource<Button*>("Button_Start", new Button([&] {buttonStartAction();}, Sprite()));
	this->objects.get("Button_Start")->shape->setTexture("Textures/blueButton.png");
	this->objects.get("Button_Start")->addText("Start", *this->font);
	this->objects.get("Button_Start")->setTextSize(50);
	
	optionButton = addResource<Button*>("Button_Option", new Button([&] {buttonOptionAction(); }, Sprite()));
	this->objects.get("Button_Option")->shape->setTexture("Textures/blueButton.png");
	this->objects.get("Button_Option")->addText("Optionen", *this->font);
	this->objects.get("Button_Option")->setTextSize(50);

	endButton = addResource<Button*>("Button_End", new Button([&] {buttonEndAction(); }, Sprite()));
	this->objects.get("Button_End")->shape->setTexture("Textures/blueButton.png");
	this->objects.get("Button_End")->addText("Beenden", *this->font);
	this->objects.get("Button_End")->setTextSize(50);
	
	this->objects.get(1)->shape->scale(Vector2f(1.5f, 1.5f));
	this->objects.get(2)->shape->scale(Vector2f(1.5f, 1.5f));
	this->objects.get(3)->shape->scale(Vector2f(1.5f, 1.5f));


	alignTo(*startButton->shape, *this->objects.get("Background")->shape, LEFT, 300);
	startButton->shape->move(Vector2f(0, 100));
	alignNextTo(*optionButton->shape, *startButton->shape, RIGHT, 50);
	alignNextTo(*endButton->shape, *optionButton->shape, RIGHT, 50);
	alignTo(*this->objects.get("Button_Start")->objectText, *this->objects.get("Button_Start")->shape);
	alignTo(*this->objects.get("Button_Option")->objectText, *this->objects.get("Button_Option")->shape);
	alignTo(*this->objects.get("Button_End")->objectText, *this->objects.get("Button_End")->shape);


	this->objects.push("SnakeCover", new ObjectBase(Sprite()));
	this->objects.get("SnakeCover")->shape->setTexture("Textures/Cover_Snake.png");
	this->objects.get("SnakeCover")->shape->setPosition(Vector2f(300, 100));
	this->objects.get("SnakeCover")->shape->setSize(Vector2f(1000, 600));

	alignTo(*this->objects.get("SnakeCover")->shape, *this->objects.get("Background")->shape, TOP, 100);

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
