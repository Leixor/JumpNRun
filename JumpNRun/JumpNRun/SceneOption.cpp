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
	this->snakeOption->addText(new ObjectText("SnakeOptions", *fonts));
	this->snakeOption->getObjectText()->setCharacterSize(40);
	alignTo(*snakeOption->getObjectText(), *snakeOption->getObjectShape());
	
	this->snakeOption->addContent("HeadColor", new ObjectBase(new ShapeRectangle()), new Button([&] {this->colorOrigin = "HeadColor"; }, new ShapeRectangle()));
	this->snakeOption->getSecondObject("HeadColor")->getObjectShape()->setFillColor(Color(stoul(configHelper->get("Snake", "HeadColor"), nullptr, 16)));
	this->snakeOption->getFirstObject("HeadColor")->addText(new ObjectText("HeadColor", *fonts));
	this->snakeOption->getFirstObject("HeadColor")->getObjectShape()->setFillColor(Color::Black);
	alignTo(*this->snakeOption->getFirstObject("HeadColor")->getObjectText(), *this->snakeOption->getFirstObject("HeadColor")->getObjectShape());

	this->snakeOption->addContent("HeadOColor", new ObjectBase(new ShapeRectangle()), new Button([&] {this->colorOrigin = "HeadOColor"; }, new ShapeRectangle()));
	this->snakeOption->getSecondObject("HeadOColor")->getObjectShape()->setFillColor(Color(stoul(configHelper->get("Snake", "HeadOColor"), nullptr, 16)));
	this->snakeOption->getFirstObject("HeadOColor")->addText(new ObjectText("HeadOColor", *fonts));
	this->snakeOption->getFirstObject("HeadOColor")->getObjectShape()->setFillColor(Color::Black);
	alignTo(*this->snakeOption->getFirstObject("HeadOColor")->getObjectText(), *this->snakeOption->getFirstObject("HeadOColor")->getObjectShape());

	this->snakeOption->addContent("FoodColor", new ObjectBase(new ShapeRectangle()), new Button([&] {this->colorOrigin = "FoodColor"; }, new ShapeRectangle()));
	this->snakeOption->getSecondObject("FoodColor")->getObjectShape()->setFillColor(Color(stoul(configHelper->get("Snake", "FoodColor"), nullptr, 16)));
	this->snakeOption->getFirstObject("FoodColor")->addText(new ObjectText("FoodColor", *fonts));
	this->snakeOption->getFirstObject("FoodColor")->getObjectShape()->setFillColor(Color::Black);
	alignTo(*this->snakeOption->getFirstObject("FoodColor")->getObjectText(), *this->snakeOption->getFirstObject("FoodColor")->getObjectShape());

	this->snakeOption->addContent("FoodOColor", new ObjectBase(new ShapeRectangle()), new Button([&] {this->colorOrigin = "FoodOColor"; }, new ShapeRectangle()));
	this->snakeOption->getSecondObject("FoodOColor")->getObjectShape()->setFillColor(Color(stoul(configHelper->get("Snake", "FoodOColor"), nullptr, 16)));
	this->snakeOption->getFirstObject("FoodOColor")->addText(new ObjectText("FoodOColor", *fonts));
	this->snakeOption->getFirstObject("FoodOColor")->getObjectShape()->setFillColor(Color::Black);
	alignTo(*this->snakeOption->getFirstObject("FoodOColor")->getObjectText(), *this->snakeOption->getFirstObject("FoodOColor")->getObjectShape());

	this->snakeOption->addContent("BodyColor", new ObjectBase(new ShapeRectangle()), new Button([&] {this->colorOrigin = "BodyColor"; }, new ShapeRectangle()));
	this->snakeOption->getSecondObject("BodyColor")->getObjectShape()->setFillColor(Color(stoul(configHelper->get("Snake", "BodyColor"), nullptr, 16)));
	this->snakeOption->getFirstObject("BodyColor")->addText(new ObjectText("BodyColor", *fonts));
	this->snakeOption->getFirstObject("BodyColor")->getObjectShape()->setFillColor(Color::Black);
	alignTo(*this->snakeOption->getFirstObject("BodyColor")->getObjectText(), *this->snakeOption->getFirstObject("BodyColor")->getObjectShape());

	this->snakeOption->addContent("BodyOColor", new ObjectBase(new ShapeRectangle()), new Button([&] {this->colorOrigin = "BodyOColor"; }, new ShapeRectangle()));
	this->snakeOption->getSecondObject("BodyOColor")->getObjectShape()->setFillColor(Color(stoul(configHelper->get("Snake", "BodyOColor"), nullptr, 16)));
	this->snakeOption->getFirstObject("BodyOColor")->addText(new ObjectText("BodyOColor", *fonts));
	this->snakeOption->getFirstObject("BodyOColor")->getObjectShape()->setFillColor(Color::Black);
	alignTo(*this->snakeOption->getFirstObject("BodyOColor")->getObjectText(), *this->snakeOption->getFirstObject("BodyOColor")->getObjectShape());
	
	addResource("ColorShow", new Button([&]
	{
		if (colorOrigin != "")
		{
			Uint32 tmp = this->snakeOption->getSecondObject(colorOrigin)->getObjectShape()->getFillColor().toInteger();
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
			this->snakeOption->getSecondObject(colorOrigin)->getObjectShape()->setFillColor(Color(
				Uint8(red * 255), 
				this->snakeOption->getSecondObject(colorOrigin)->getObjectShape()->getFillColor().g,
				this->snakeOption->getSecondObject(colorOrigin)->getObjectShape()->getFillColor().b));
	}, new ShapeRectangle(170, 60, Color(100, 0, 0))));
	addResource("Green", new Slider([&](float green) { 
		if (colorOrigin != "") 
			this->snakeOption->getSecondObject(colorOrigin)->getObjectShape()->setFillColor(Color(
				this->snakeOption->getSecondObject(colorOrigin)->getObjectShape()->getFillColor().r,
				Uint8(green * 255), 
				this->snakeOption->getSecondObject(colorOrigin)->getObjectShape()->getFillColor().b));
	}, new ShapeRectangle(170, 60, Color(0, 100, 0))));
	addResource("Blue", new Slider([&](float blue) 
	{ 
		if (colorOrigin != "") 
			this->snakeOption->getSecondObject(colorOrigin)->getObjectShape()->setFillColor(Color(
				this->snakeOption->getSecondObject(colorOrigin)->getObjectShape()->getFillColor().r,
				this->snakeOption->getSecondObject(colorOrigin)->getObjectShape()->getFillColor().g,
				Uint8(blue * 255))); 
	}, new ShapeRectangle(170, 60, Color(0, 0, 100))));

	alignTo(*this->objects.get("Red")->getObjectShape(), *this->objects.get("ColorShow")->getObjectShape(), BOTTOM | LEFT, -110);
	alignTo(*this->objects.get("Green")->getObjectShape(), *this->objects.get("ColorShow")->getObjectShape(), BOTTOM, -110);
	alignTo(*this->objects.get("Blue")->getObjectShape(), *this->objects.get("ColorShow")->getObjectShape(), BOTTOM | RIGHT, -110);

	return true;
}

void SceneOption::update()
{
	Scene::update();
	if (this->getUpdateSync() && this->colorOrigin != "")
	{
		this->objects.get("Red")->getObjectShape()->setFillColor(Color(this->snakeOption->getSecondObject(colorOrigin)->getObjectShape()->getFillColor().r, 0, 0));
		this->objects.get("Green")->getObjectShape()->setFillColor(Color(0, this->snakeOption->getSecondObject(colorOrigin)->getObjectShape()->getFillColor().g, 0));
		this->objects.get("Blue")->getObjectShape()->setFillColor(Color(0, 0, this->snakeOption->getSecondObject(colorOrigin)->getObjectShape()->getFillColor().b));
		this->objects.get("ColorShow")->getObjectShape()->setFillColor(this->snakeOption->getSecondObject(colorOrigin)->getObjectShape()->getFillColor());
	}
}
