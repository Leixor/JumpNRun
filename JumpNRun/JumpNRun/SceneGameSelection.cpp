#include "StandardInclude.h"

SceneGameSelection::SceneGameSelection(string name, SceneHandler * sceneHandler, RenderWindow* window)
	:Scene(name, sceneHandler, window)
{
	this->setupResources();
}

SceneGameSelection::~SceneGameSelection()
{
}

void SceneGameSelection::snakeStart()
{
	this->getSceneHandler()->getSceneByName("GOL")->setVisibility(NONE);
	this->getSceneHandler()->getSceneByName("SnakeGame")->setVisibility(ALL);
	this->getSceneHandler()->getSceneByName("GameSelection")->setVisibility(NONE);
	this->getSceneHandler()->getSceneByName("SnakeGame")->setView(View(FloatRect(0, 0, windowDef::get().windowSizeX, windowDef::get().windowSizeY)));
}

void SceneGameSelection::golStart()
{
	this->getSceneHandler()->getSceneByName("GOL")->setVisibility(ALL);
	this->getSceneHandler()->getSceneByName("SnakeGame")->setVisibility(NONE);
	this->getSceneHandler()->getSceneByName("GameSelection")->setVisibility(NONE);
	this->getSceneHandler()->getSceneByName("GOL")->setView(View(FloatRect(0, 0, windowDef::get().windowSizeX, windowDef::get().windowSizeY)));
}

bool SceneGameSelection::setupResources()
{
	conf = new ConfigHelper("Test.txt");

	addObject("BackGround", new ShapeRectangle(FloatRect(0.0f, 0.0f, windowDef::get().windowSizeX, windowDef::get().windowSizeY), Color(200,200,200,255)));

	addResource("SnakeButton", new Button([&] {snakeStart(); }, new ShapeRectangle(FloatRect(0.0f, 0.0f, windowDef::get().windowSizeX / 2.0f, windowDef::get().windowSizeY), Color::Transparent, -10.0f, Color::White)));
	alignTo(*this->objects.get("SnakeButton")->shape, *this->objects.get("BackGround")->shape, LEFT);
	addResource("GOLButton", new Button([&] {golStart(); }, new ShapeRectangle(FloatRect(0.0f, 0.0f, windowDef::get().windowSizeX / 2.0f, windowDef::get().windowSizeY), Color::Transparent, -10.0f, Color::White)));
	alignTo(*this->objects.get("GOLButton")->shape, *this->objects.get("BackGround")->shape, RIGHT);

	this->getSceneHandler()->addScene(new SceneSnakeGame("SnakeGame", this->getSceneHandler(), Vector2u(15, 15), 6));
	this->getSceneHandler()->setTopScene("SnakeGame");
	this->getSceneHandler()->getSceneByName("SnakeGame")->setVisibility(VISIBLE);
	this->getSceneHandler()->getSceneByName("SnakeGame")->setView(View(FloatRect(50, 50, 600, 600)));
	this->getSceneHandler()->getSceneByName("SnakeGame")->setScenePosition(Vector2f(0.0f,0.0f));
	this->getSceneHandler()->getSceneByName("SnakeGame")->setSceneScaling(Vector2f(0.5f, 1.0f));

	this->getSceneHandler()->addScene(new SceneGOL("GOL", this->getSceneHandler(), window));
	this->getSceneHandler()->setTopScene("GOL");
	this->getSceneHandler()->getSceneByName("GOL")->setVisibility(VISIBLE);
	this->getSceneHandler()->getSceneByName("GOL")->setView(View(FloatRect(0, 0, windowDef::get().windowSizeX / 2, windowDef::get().windowSizeY)));
	this->getSceneHandler()->getSceneByName("GOL")->setScenePosition(Vector2f(0.5f, 0.0f));
	this->getSceneHandler()->getSceneByName("GOL")->setSceneScaling(Vector2f(0.5f, 1.0f));
	
	return false;
}
