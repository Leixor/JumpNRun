#include "standardInclude.h"

SceneStartMenu::SceneStartMenu(string name, SceneHandler * sceneHandler, RenderWindow* window)
	: Scene(name, sceneHandler, window)
{
	this->setupResources();
}

SceneStartMenu::~SceneStartMenu()
{
}

void SceneStartMenu::handleEvents(RenderWindow & window, Event& windowEvent)
{
	Scene::handleEvents(window, windowEvent);
	if (windowEvent.type == Event::MouseButtonReleased && this->getSceneHandler()->sceneExists("GameSelection"))
	{
		this->setVisibility(UPDATABLE);
		this->getSceneHandler()->getSceneByName("GameSelection")->setVisibility(ALL);
	}
}

bool SceneStartMenu::setupResources()
{
	conf = new ConfigHelper("test.txt");
	font = new Font();
	this->font->loadFromFile("Textures/cool.ttf");
	
	string bgColor = conf->get("Menu","BackgroundColor");
	addObject("Background", new ShapeRectangle(float(windowDef::get().windowSizeX), float(windowDef::get().windowSizeY), Color::Color(stoul(bgColor, nullptr, 16))));

	startButton = addResource<Button*>("Button_Start", new Button([&] {buttonStartAction();}, new ShapeSprite("Textures/blueButton.png", 1.5f)));
	this->objects.get("Button_Start")->addText("Start", *this->font);
	this->objects.get("Button_Start")->setTextSize(50);
	
	optionButton = addResource<Button*>("Button_Option", new Button([&] {buttonOptionAction(); }, new ShapeSprite("Textures/blueButton.png", 1.5f)));
	this->objects.get("Button_Option")->addText("Optionen", *this->font);
	this->objects.get("Button_Option")->setTextSize(50);

	endButton = addResource<Button*>("Button_End", new Button([&] {buttonEndAction(); }, new ShapeSprite("Textures/blueButton.png", 1.5f)));
	this->objects.get("Button_End")->addText("Beenden", *this->font);
	this->objects.get("Button_End")->setTextSize(50);
	
	alignTo(*optionButton->shape, *this->objects.get("Background")->shape);
	optionButton->shape->move(Vector2f(0, 100));
	alignNextTo(*startButton->shape, *optionButton->shape, LEFT, 50);
	alignNextTo(*endButton->shape, *optionButton->shape, RIGHT, 50);
	alignTo(*this->objects.get("Button_Start")->objectText, *this->objects.get("Button_Start")->shape);
	alignTo(*this->objects.get("Button_Option")->objectText, *this->objects.get("Button_Option")->shape);
	alignTo(*this->objects.get("Button_End")->objectText, *this->objects.get("Button_End")->shape);

	addResource("SnakeCover", new ObjectBase(new DrawableShape<Sprite>()));
	this->objects.get("SnakeCover")->shape->setTexture("Textures/Cover_Snake.png");
	this->objects.get("SnakeCover")->shape->setPosition(Vector2f(300, 100));
	this->objects.get("SnakeCover")->shape->setSize(Vector2f(1000, 600));

	alignTo(*this->objects.get("SnakeCover")->shape, *this->objects.get("Background")->shape, TOP, -50);

	return true;
}

void SceneStartMenu::buttonStartAction()
{
	this->setVisibility(INPUTABLE);
	this->getSceneHandler()->addScene(new SceneGameSelection("GameSelection", this->getSceneHandler(), window), VISIBLE);
}

void SceneStartMenu::buttonOptionAction()
{
	this->getSceneHandler()->addScene(new SceneOption("Option", this->getSceneHandler()), ALL);
	this->setVisibility(UPDATABLE);
}

void SceneStartMenu::buttonEndAction()
{
	this->window->close();
}
