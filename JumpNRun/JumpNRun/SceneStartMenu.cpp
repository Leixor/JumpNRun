#include "SceneStartMenu.h"

SceneStartMenu::SceneStartMenu(SceneHandler& sceneHandler, RenderWindow* window)
	: Scene(sceneHandler, window)
{
	this->setupResources();
}

SceneStartMenu::~SceneStartMenu()
{
}

void SceneStartMenu::handleEvents(RenderWindow & window, Event& windowEvent)
{
	Scene::handleEvents(window, windowEvent);
	if (windowEvent.type == Event::MouseButtonReleased && this->getSceneHandler().sceneExists("GameSelection"))
	{
		this->setSceneVisibility(UPDATABLE);
		this->getSceneHandler().setSceneVisibility("GameSelection", ALL);
	}
}

bool SceneStartMenu::setupResources()
{
	configHelper = new ConfigHelper("test.txt");
	font = new Font();
	this->font->loadFromFile("Textures/cool.ttf");
	
	string bgColor = configHelper->get("Menu","BackgroundColor");
	addObject("Background", new ShapeRectangle(float(windowDef::get().windowSizeX), float(windowDef::get().windowSizeY), Color::Color(stoul(bgColor, nullptr, 16))));

	startButton = addResource<Button*>("Button_Start", new Button([&] {buttonStartAction();}, new ShapeSprite("Textures/blueButton.png", 1.5f)));
	this->objects.get("Button_Start")->addText(new ObjectText("Start", *this->font));
	this->objects.get("Button_Start")->objectText->setCharacterSize(50);
	
	optionButton = addResource<Button*>("Button_Option", new Button([&] {buttonOptionAction(); }, new ShapeSprite("Textures/blueButton.png", 1.5f)));
	this->objects.get("Button_Option")->addText(new ObjectText("Optionen", *this->font));
	this->objects.get("Button_Option")->objectText->setCharacterSize(50);

	endButton = addResource<Button*>("Button_End", new Button([&] {buttonEndAction(); }, new ShapeSprite("Textures/blueButton.png", 1.5f)));
	this->objects.get("Button_End")->addText(new ObjectText("Beenden", *this->font));
	this->objects.get("Button_End")->objectText->setCharacterSize(50);
	
	alignTo(*optionButton->objectShape, *this->objects.get("Background")->objectShape);
	optionButton->objectShape->move(Vector2f(0, 100));
	alignNextTo(*startButton->objectShape, *optionButton->objectShape, LEFT, 50);
	alignNextTo(*endButton->objectShape, *optionButton->objectShape, RIGHT, 50);
	alignTo(*this->objects.get("Button_Start")->objectText, *this->objects.get("Button_Start")->objectShape);
	alignTo(*this->objects.get("Button_Option")->objectText, *this->objects.get("Button_Option")->objectShape);
	alignTo(*this->objects.get("Button_End")->objectText, *this->objects.get("Button_End")->objectShape);

	addResource("SnakeCover", new BaseResource(new ShapeSprite("Textures/Cover_Snake.png")));
	this->objects.get("SnakeCover")->objectShape->setPosition(Vector2f(300, 100));
	this->objects.get("SnakeCover")->objectShape->setSize(Vector2f(1000, 600));

	alignTo(*this->objects.get("SnakeCover")->objectShape, *this->objects.get("Background")->objectShape, TOP, -50);

	return true;
}

void SceneStartMenu::buttonStartAction()
{
	this->setSceneVisibility(INPUTABLE);
	this->getSceneHandler().addScene("GameSelection", new SceneGameSelection(this->getSceneHandler(), window), VISIBLE);
}

void SceneStartMenu::buttonOptionAction()
{
	this->getSceneHandler().addScene("Option", new SceneOption(this->getSceneHandler()), ALL);
	this->setSceneVisibility(UPDATABLE);
}

void SceneStartMenu::buttonEndAction()
{
	/*this->window->close();*/
	/*myAni->run();*/
}
