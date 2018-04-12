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
	this->configHelper = new ConfigHelper("test.txt");
	this->color = Color(100, 100, 100);

	addObject("Background", new ShapeRectangle(windowDef::get().windowSizeX, windowDef::get().windowSizeY, Color(0,200,220,255)));

	addObject("ColorShow", new ShapeRectangle(FloatRect(550,100,500,500), color));

	addResource("Red", new Slider([&](float red) {this->color.r = Uint8(red * 255); }, new ShapeRectangle(170, 60, Color(color.r, 0, 0))));
	addResource("Green", new Slider([&](float green) {this->color.g = Uint8(green * 255); }, new ShapeRectangle(170, 60, Color(0, color.g, 0))));
	addResource("Blue", new Slider([&](float blue) {this->color.b = Uint8(blue * 255); }, new ShapeRectangle(170, 60, Color(0, 0, color.b))));

	alignTo(*this->objects.get("Red")->shape, *this->objects.get("ColorShow")->shape, BOTTOM | LEFT, -110);
	alignTo(*this->objects.get("Green")->shape, *this->objects.get("ColorShow")->shape, BOTTOM, -110);
	alignTo(*this->objects.get("Blue")->shape, *this->objects.get("ColorShow")->shape, BOTTOM | RIGHT, -110);

	return true;
}

void SceneOption::update()
{
	Scene::update();
	if (this->getUpdateSync())
	{
		this->objects.get("Red")->shape->setFillColor(Color(color.r, 0, 0));
		this->objects.get("Green")->shape->setFillColor(Color(0, color.g, 0));
		this->objects.get("Blue")->shape->setFillColor(Color(0, 0, color.b));
		addObject("ColorShow", new ShapeRectangle(FloatRect(550, 100, 500, 500), color));
	}
}
