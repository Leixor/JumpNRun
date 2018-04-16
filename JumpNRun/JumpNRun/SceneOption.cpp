#include "SceneOption.h"

SceneOption::SceneOption(string name, SceneHandler& sceneHandler)
	:Scene(name, sceneHandler)
{
	fonts = new Font();
	setupResources();
}

SceneOption::~SceneOption()
{
}

bool SceneOption::setupResources()
{
	this->updateRate = 50;
	this->configHelper = new ConfigHelper("test.txt");
	ConfigHelper tmpHelper = *this->configHelper;
	this->colorOrigin = "";

	fonts->loadFromFile("Textures/cool.ttf");

	addObject("Background", new ShapeRectangle(windowDef::get().windowSizeX, windowDef::get().windowSizeY, Color(0,200,220,255)));

	this->snakeOption = addResource("SnakeOption", new DropdownList(new ShapeRectangle(FloatRect(100, 100, 300, 70), Color(100, 100, 100)), 230.0f));
	this->snakeOption->addText("SnakeOptions", *fonts);
	this->snakeOption->setTextSize(40);
	alignTo(*snakeOption->objectText, *snakeOption->shape);
	
	this->snakeOption->addContent("HeadColor", new ObjectBase(new ShapeRectangle()), new Button([&] {this->colorOrigin = "HeadColor"; }, new ShapeRectangle()));
	this->snakeOption->getSecondObject("HeadColor")->shape->setFillColor(Color(stoul(configHelper->get("Snake", "HeadColor"), nullptr, 16)));
	this->snakeOption->getFirstObject("HeadColor")->addText("HeadColor", *fonts);
	this->snakeOption->getFirstObject("HeadColor")->shape->setFillColor(Color::Black);
	alignTo(*this->snakeOption->getFirstObject("HeadColor")->objectText, *this->snakeOption->getFirstObject("HeadColor")->shape);

	this->snakeOption->addContent("HeadOColor", new ObjectBase(new ShapeRectangle()), new Button([&] {this->colorOrigin = "HeadOColor"; }, new ShapeRectangle()));
	this->snakeOption->getSecondObject("HeadOColor")->shape->setFillColor(Color(stoul(configHelper->get("Snake", "HeadOColor"), nullptr, 16)));
	this->snakeOption->getFirstObject("HeadOColor")->addText("HeadOColor", *fonts);
	this->snakeOption->getFirstObject("HeadOColor")->shape->setFillColor(Color::Black);
	alignTo(*this->snakeOption->getFirstObject("HeadOColor")->objectText, *this->snakeOption->getFirstObject("HeadOColor")->shape);

	this->snakeOption->addContent("FoodColor", new ObjectBase(new ShapeRectangle()), new Button([&] {this->colorOrigin = "FoodColor"; }, new ShapeRectangle()));
	this->snakeOption->getSecondObject("FoodColor")->shape->setFillColor(Color(stoul(configHelper->get("Snake", "FoodColor"), nullptr, 16)));
	this->snakeOption->getFirstObject("FoodColor")->addText("FoodColor", *fonts);
	this->snakeOption->getFirstObject("FoodColor")->shape->setFillColor(Color::Black);
	alignTo(*this->snakeOption->getFirstObject("FoodColor")->objectText, *this->snakeOption->getFirstObject("FoodColor")->shape);

	this->snakeOption->addContent("FoodOColor", new ObjectBase(new ShapeRectangle()), new Button([&] {this->colorOrigin = "FoodOColor"; }, new ShapeRectangle()));
	this->snakeOption->getSecondObject("FoodOColor")->shape->setFillColor(Color(stoul(configHelper->get("Snake", "FoodOColor"), nullptr, 16)));
	this->snakeOption->getFirstObject("FoodOColor")->addText("FoodOColor", *fonts);
	this->snakeOption->getFirstObject("FoodOColor")->shape->setFillColor(Color::Black);
	alignTo(*this->snakeOption->getFirstObject("FoodOColor")->objectText, *this->snakeOption->getFirstObject("FoodOColor")->shape);

	this->snakeOption->addContent("BodyColor", new ObjectBase(new ShapeRectangle()), new Button([&] {this->colorOrigin = "BodyColor"; }, new ShapeRectangle()));
	this->snakeOption->getSecondObject("BodyColor")->shape->setFillColor(Color(stoul(configHelper->get("Snake", "BodyColor"), nullptr, 16)));
	this->snakeOption->getFirstObject("BodyColor")->addText("BodyColor", *fonts);
	this->snakeOption->getFirstObject("BodyColor")->shape->setFillColor(Color::Black);
	alignTo(*this->snakeOption->getFirstObject("BodyColor")->objectText, *this->snakeOption->getFirstObject("BodyColor")->shape);

	this->snakeOption->addContent("BodyOColor", new ObjectBase(new ShapeRectangle()), new Button([&] {this->colorOrigin = "BodyOColor"; }, new ShapeRectangle()));
	this->snakeOption->getSecondObject("BodyOColor")->shape->setFillColor(Color(stoul(configHelper->get("Snake", "BodyOColor"), nullptr, 16)));
	this->snakeOption->getFirstObject("BodyOColor")->addText("BodyOColor", *fonts);
	this->snakeOption->getFirstObject("BodyOColor")->shape->setFillColor(Color::Black);
	alignTo(*this->snakeOption->getFirstObject("BodyOColor")->objectText, *this->snakeOption->getFirstObject("BodyOColor")->shape);
	
	addResource("ColorShow", new Button([&]
	{
		if (colorOrigin != "")
		{
			Uint32 tmp = this->snakeOption->getSecondObject(colorOrigin)->shape->getFillColor().toInteger();
			stringstream stream;
			stream << hex << tmp;
			string result(stream.str());
			stream.clear();
			this->configHelper->write("Snake", colorOrigin, result);
			colorOrigin = "";
		}
	}, new ShapeRectangle(FloatRect(550, 100, 500, 500), Color(200, 200, 200))));

	addResource("Red", new Slider([&](float red) 
	{ 
		if(colorOrigin != "") 
			this->snakeOption->getSecondObject(colorOrigin)->shape->setFillColor(Color(
				Uint8(red * 255), 
				this->snakeOption->getSecondObject(colorOrigin)->shape->getFillColor().g,
				this->snakeOption->getSecondObject(colorOrigin)->shape->getFillColor().b));
	}, new ShapeRectangle(170, 60, Color(100, 0, 0))));
	addResource("Green", new Slider([&](float green) { 
		if (colorOrigin != "") 
			this->snakeOption->getSecondObject(colorOrigin)->shape->setFillColor(Color(
				this->snakeOption->getSecondObject(colorOrigin)->shape->getFillColor().r,
				Uint8(green * 255), 
				this->snakeOption->getSecondObject(colorOrigin)->shape->getFillColor().b));
	}, new ShapeRectangle(170, 60, Color(0, 100, 0))));
	addResource("Blue", new Slider([&](float blue) 
	{ 
		if (colorOrigin != "") 
			this->snakeOption->getSecondObject(colorOrigin)->shape->setFillColor(Color(
				this->snakeOption->getSecondObject(colorOrigin)->shape->getFillColor().r,
				this->snakeOption->getSecondObject(colorOrigin)->shape->getFillColor().g,
				Uint8(blue * 255))); 
	}, new ShapeRectangle(170, 60, Color(0, 0, 100))));

	alignTo(*this->objects.get("Red")->shape, *this->objects.get("ColorShow")->shape, BOTTOM | LEFT, -110);
	alignTo(*this->objects.get("Green")->shape, *this->objects.get("ColorShow")->shape, BOTTOM, -110);
	alignTo(*this->objects.get("Blue")->shape, *this->objects.get("ColorShow")->shape, BOTTOM | RIGHT, -110);

	return true;
}

void SceneOption::update()
{
	Scene::update();
	if (this->getUpdateSync() && this->colorOrigin != "")
	{
		this->objects.get("Red")->shape->setFillColor(Color(this->snakeOption->getSecondObject(colorOrigin)->shape->getFillColor().r, 0, 0));
		this->objects.get("Green")->shape->setFillColor(Color(0, this->snakeOption->getSecondObject(colorOrigin)->shape->getFillColor().g, 0));
		this->objects.get("Blue")->shape->setFillColor(Color(0, 0, this->snakeOption->getSecondObject(colorOrigin)->shape->getFillColor().b));
		this->objects.get("ColorShow")->shape->setFillColor(this->snakeOption->getSecondObject(colorOrigin)->shape->getFillColor());
	}
}
