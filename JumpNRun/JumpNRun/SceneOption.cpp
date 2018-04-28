#include "SceneOption.h"

SceneOption::SceneOption(SceneHandler& sceneHandler)
	:Scene(sceneHandler)
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
	this->snakeOption->objectText->setCharacterSize(40);
	alignTo(*snakeOption->objectText, *snakeOption->objectShape);
	
	this->snakeOption->addContent("HeadColor", new BaseResource(new ShapeRectangle()), new Button([&] {this->colorOrigin = "HeadColor"; }, new ShapeRectangle()));
	this->snakeOption->getSecondObject("HeadColor")->objectShape->setFillColor(Color(stoul(configHelper->get("Snake", "HeadColor"), nullptr, 16)));
	this->snakeOption->getFirstObject("HeadColor")->addText(new ObjectText("HeadColor", *fonts));
	this->snakeOption->getFirstObject("HeadColor")->objectShape->setFillColor(Color::Black);
	alignTo(*this->snakeOption->getFirstObject("HeadColor")->objectText, *this->snakeOption->getFirstObject("HeadColor")->objectShape);

	this->snakeOption->addContent("HeadOColor", new BaseResource(new ShapeRectangle()), new Button([&] {this->colorOrigin = "HeadOColor"; }, new ShapeRectangle()));
	this->snakeOption->getSecondObject("HeadOColor")->objectShape->setFillColor(Color(stoul(configHelper->get("Snake", "HeadOColor"), nullptr, 16)));
	this->snakeOption->getFirstObject("HeadOColor")->addText(new ObjectText("HeadOColor", *fonts));
	this->snakeOption->getFirstObject("HeadOColor")->objectShape->setFillColor(Color::Black);
	alignTo(*this->snakeOption->getFirstObject("HeadOColor")->objectText, *this->snakeOption->getFirstObject("HeadOColor")->objectShape);

	this->snakeOption->addContent("FoodColor", new BaseResource(new ShapeRectangle()), new Button([&] {this->colorOrigin = "FoodColor"; }, new ShapeRectangle()));
	this->snakeOption->getSecondObject("FoodColor")->objectShape->setFillColor(Color(stoul(configHelper->get("Snake", "FoodColor"), nullptr, 16)));
	this->snakeOption->getFirstObject("FoodColor")->addText(new ObjectText("FoodColor", *fonts));
	this->snakeOption->getFirstObject("FoodColor")->objectShape->setFillColor(Color::Black);
	alignTo(*this->snakeOption->getFirstObject("FoodColor")->objectText, *this->snakeOption->getFirstObject("FoodColor")->objectShape);

	this->snakeOption->addContent("FoodOColor", new BaseResource(new ShapeRectangle()), new Button([&] {this->colorOrigin = "FoodOColor"; }, new ShapeRectangle()));
	this->snakeOption->getSecondObject("FoodOColor")->objectShape->setFillColor(Color(stoul(configHelper->get("Snake", "FoodOColor"), nullptr, 16)));
	this->snakeOption->getFirstObject("FoodOColor")->addText(new ObjectText("FoodOColor", *fonts));
	this->snakeOption->getFirstObject("FoodOColor")->objectShape->setFillColor(Color::Black);
	alignTo(*this->snakeOption->getFirstObject("FoodOColor")->objectText, *this->snakeOption->getFirstObject("FoodOColor")->objectShape);

	this->snakeOption->addContent("BodyColor", new BaseResource(new ShapeRectangle()), new Button([&] {this->colorOrigin = "BodyColor"; }, new ShapeRectangle()));
	this->snakeOption->getSecondObject("BodyColor")->objectShape->setFillColor(Color(stoul(configHelper->get("Snake", "BodyColor"), nullptr, 16)));
	this->snakeOption->getFirstObject("BodyColor")->addText(new ObjectText("BodyColor", *fonts));
	this->snakeOption->getFirstObject("BodyColor")->objectShape->setFillColor(Color::Black);
	alignTo(*this->snakeOption->getFirstObject("BodyColor")->objectText, *this->snakeOption->getFirstObject("BodyColor")->objectShape);

	this->snakeOption->addContent("BodyOColor", new BaseResource(new ShapeRectangle()), new Button([&] {this->colorOrigin = "BodyOColor"; }, new ShapeRectangle()));
	this->snakeOption->getSecondObject("BodyOColor")->objectShape->setFillColor(Color(stoul(configHelper->get("Snake", "BodyOColor"), nullptr, 16)));
	this->snakeOption->getFirstObject("BodyOColor")->addText(new ObjectText("BodyOColor", *fonts));
	this->snakeOption->getFirstObject("BodyOColor")->objectShape->setFillColor(Color::Black);
	alignTo(*this->snakeOption->getFirstObject("BodyOColor")->objectText, *this->snakeOption->getFirstObject("BodyOColor")->objectShape);
	
	addResource("ColorShow", new Button([&]
	{
		if (colorOrigin != "")
		{
			Uint32 tmp = this->snakeOption->getSecondObject(colorOrigin)->objectShape->getFillColor().toInteger();
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
			this->snakeOption->getSecondObject(colorOrigin)->objectShape->setFillColor(Color(
				Uint8(red * 255), 
				this->snakeOption->getSecondObject(colorOrigin)->objectShape->getFillColor().g,
				this->snakeOption->getSecondObject(colorOrigin)->objectShape->getFillColor().b));
	}, new ShapeRectangle(170, 60, Color(100, 0, 0))));
	addResource("Green", new Slider([&](float green) { 
		if (colorOrigin != "") 
			this->snakeOption->getSecondObject(colorOrigin)->objectShape->setFillColor(Color(
				this->snakeOption->getSecondObject(colorOrigin)->objectShape->getFillColor().r,
				Uint8(green * 255), 
				this->snakeOption->getSecondObject(colorOrigin)->objectShape->getFillColor().b));
	}, new ShapeRectangle(170, 60, Color(0, 100, 0))));
	addResource("Blue", new Slider([&](float blue) 
	{ 
		if (colorOrigin != "") 
			this->snakeOption->getSecondObject(colorOrigin)->objectShape->setFillColor(Color(
				this->snakeOption->getSecondObject(colorOrigin)->objectShape->getFillColor().r,
				this->snakeOption->getSecondObject(colorOrigin)->objectShape->getFillColor().g,
				Uint8(blue * 255))); 
	}, new ShapeRectangle(170, 60, Color(0, 0, 100))));

	alignTo(*this->objects.get("Red")->objectShape, *this->objects.get("ColorShow")->objectShape, BOTTOM | LEFT, -110);
	alignTo(*this->objects.get("Green")->objectShape, *this->objects.get("ColorShow")->objectShape, BOTTOM, -110);
	alignTo(*this->objects.get("Blue")->objectShape, *this->objects.get("ColorShow")->objectShape, BOTTOM | RIGHT, -110);

	return true;
}

void SceneOption::update()
{
	Scene::update();
	if (this->colorOrigin != "")
	{
		this->objects.get("Red")->objectShape->setFillColor(Color(this->snakeOption->getSecondObject(colorOrigin)->objectShape->getFillColor().r, 0, 0));
		this->objects.get("Green")->objectShape->setFillColor(Color(0, this->snakeOption->getSecondObject(colorOrigin)->objectShape->getFillColor().g, 0));
		this->objects.get("Blue")->objectShape->setFillColor(Color(0, 0, this->snakeOption->getSecondObject(colorOrigin)->objectShape->getFillColor().b));
		this->objects.get("ColorShow")->objectShape->setFillColor(this->snakeOption->getSecondObject(colorOrigin)->objectShape->getFillColor());
	}
}
