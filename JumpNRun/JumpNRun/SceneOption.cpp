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
	this->snakeOption->getText()->setCharacterSize(40);
	alignTo(*snakeOption->getText(), *snakeOption->getShape());
	
	this->snakeOption->addContent("HeadColor", new ObjectBase(new ShapeRectangle()), new Button([&] {this->colorOrigin = "HeadColor"; }, new ShapeRectangle()));
	this->snakeOption->getSecondObject("HeadColor")->getShape()->setFillColor(Color(stoul(configHelper->get("Snake", "HeadColor"), nullptr, 16)));
	this->snakeOption->getFirstObject("HeadColor")->addText(new ObjectText("HeadColor", *fonts));
	this->snakeOption->getFirstObject("HeadColor")->getShape()->setFillColor(Color::Black);
	alignTo(*this->snakeOption->getFirstObject("HeadColor")->getText(), *this->snakeOption->getFirstObject("HeadColor")->getShape());

	this->snakeOption->addContent("HeadOColor", new ObjectBase(new ShapeRectangle()), new Button([&] {this->colorOrigin = "HeadOColor"; }, new ShapeRectangle()));
	this->snakeOption->getSecondObject("HeadOColor")->getShape()->setFillColor(Color(stoul(configHelper->get("Snake", "HeadOColor"), nullptr, 16)));
	this->snakeOption->getFirstObject("HeadOColor")->addText(new ObjectText("HeadOColor", *fonts));
	this->snakeOption->getFirstObject("HeadOColor")->getShape()->setFillColor(Color::Black);
	alignTo(*this->snakeOption->getFirstObject("HeadOColor")->getText(), *this->snakeOption->getFirstObject("HeadOColor")->getShape());

	this->snakeOption->addContent("FoodColor", new ObjectBase(new ShapeRectangle()), new Button([&] {this->colorOrigin = "FoodColor"; }, new ShapeRectangle()));
	this->snakeOption->getSecondObject("FoodColor")->getShape()->setFillColor(Color(stoul(configHelper->get("Snake", "FoodColor"), nullptr, 16)));
	this->snakeOption->getFirstObject("FoodColor")->addText(new ObjectText("FoodColor", *fonts));
	this->snakeOption->getFirstObject("FoodColor")->getShape()->setFillColor(Color::Black);
	alignTo(*this->snakeOption->getFirstObject("FoodColor")->getText(), *this->snakeOption->getFirstObject("FoodColor")->getShape());

	this->snakeOption->addContent("FoodOColor", new ObjectBase(new ShapeRectangle()), new Button([&] {this->colorOrigin = "FoodOColor"; }, new ShapeRectangle()));
	this->snakeOption->getSecondObject("FoodOColor")->getShape()->setFillColor(Color(stoul(configHelper->get("Snake", "FoodOColor"), nullptr, 16)));
	this->snakeOption->getFirstObject("FoodOColor")->addText(new ObjectText("FoodOColor", *fonts));
	this->snakeOption->getFirstObject("FoodOColor")->getShape()->setFillColor(Color::Black);
	alignTo(*this->snakeOption->getFirstObject("FoodOColor")->getText(), *this->snakeOption->getFirstObject("FoodOColor")->getShape());

	this->snakeOption->addContent("BodyColor", new ObjectBase(new ShapeRectangle()), new Button([&] {this->colorOrigin = "BodyColor"; }, new ShapeRectangle()));
	this->snakeOption->getSecondObject("BodyColor")->getShape()->setFillColor(Color(stoul(configHelper->get("Snake", "BodyColor"), nullptr, 16)));
	this->snakeOption->getFirstObject("BodyColor")->addText(new ObjectText("BodyColor", *fonts));
	this->snakeOption->getFirstObject("BodyColor")->getShape()->setFillColor(Color::Black);
	alignTo(*this->snakeOption->getFirstObject("BodyColor")->getText(), *this->snakeOption->getFirstObject("BodyColor")->getShape());

	this->snakeOption->addContent("BodyOColor", new ObjectBase(new ShapeRectangle()), new Button([&] {this->colorOrigin = "BodyOColor"; }, new ShapeRectangle()));
	this->snakeOption->getSecondObject("BodyOColor")->getShape()->setFillColor(Color(stoul(configHelper->get("Snake", "BodyOColor"), nullptr, 16)));
	this->snakeOption->getFirstObject("BodyOColor")->addText(new ObjectText("BodyOColor", *fonts));
	this->snakeOption->getFirstObject("BodyOColor")->getShape()->setFillColor(Color::Black);
	alignTo(*this->snakeOption->getFirstObject("BodyOColor")->getText(), *this->snakeOption->getFirstObject("BodyOColor")->getShape());
	
	addResource("ColorShow", new Button([&]
	{
		if (colorOrigin != "")
		{
			Uint32 tmp = this->snakeOption->getSecondObject(colorOrigin)->getShape()->getFillColor().toInteger();
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
			this->snakeOption->getSecondObject(colorOrigin)->getShape()->setFillColor(Color(
				Uint8(red * 255), 
				this->snakeOption->getSecondObject(colorOrigin)->getShape()->getFillColor().g,
				this->snakeOption->getSecondObject(colorOrigin)->getShape()->getFillColor().b));
	}, new ShapeRectangle(170, 60, Color(100, 0, 0))));
	addResource("Green", new Slider([&](float green) { 
		if (colorOrigin != "") 
			this->snakeOption->getSecondObject(colorOrigin)->getShape()->setFillColor(Color(
				this->snakeOption->getSecondObject(colorOrigin)->getShape()->getFillColor().r,
				Uint8(green * 255), 
				this->snakeOption->getSecondObject(colorOrigin)->getShape()->getFillColor().b));
	}, new ShapeRectangle(170, 60, Color(0, 100, 0))));
	addResource("Blue", new Slider([&](float blue) 
	{ 
		if (colorOrigin != "") 
			this->snakeOption->getSecondObject(colorOrigin)->getShape()->setFillColor(Color(
				this->snakeOption->getSecondObject(colorOrigin)->getShape()->getFillColor().r,
				this->snakeOption->getSecondObject(colorOrigin)->getShape()->getFillColor().g,
				Uint8(blue * 255))); 
	}, new ShapeRectangle(170, 60, Color(0, 0, 100))));

	alignTo(*this->objects.get("Red")->getShape(), *this->objects.get("ColorShow")->getShape(), BOTTOM | LEFT, -110);
	alignTo(*this->objects.get("Green")->getShape(), *this->objects.get("ColorShow")->getShape(), BOTTOM, -110);
	alignTo(*this->objects.get("Blue")->getShape(), *this->objects.get("ColorShow")->getShape(), BOTTOM | RIGHT, -110);

	return true;
}

void SceneOption::update()
{
	Scene::update();
	if (this->getUpdateSync() && this->colorOrigin != "")
	{
		this->objects.get("Red")->getShape()->setFillColor(Color(this->snakeOption->getSecondObject(colorOrigin)->getShape()->getFillColor().r, 0, 0));
		this->objects.get("Green")->getShape()->setFillColor(Color(0, this->snakeOption->getSecondObject(colorOrigin)->getShape()->getFillColor().g, 0));
		this->objects.get("Blue")->getShape()->setFillColor(Color(0, 0, this->snakeOption->getSecondObject(colorOrigin)->getShape()->getFillColor().b));
		this->objects.get("ColorShow")->getShape()->setFillColor(this->snakeOption->getSecondObject(colorOrigin)->getShape()->getFillColor());
	}
}
