#include "SceneSnakeGame.h"

#define PITCH 600
#define POSX 50
#define POSY 50
#define THICKNESS float(PITCH) / float(300)

SceneSnakeGame::SceneSnakeGame(SceneHandler& sceneHandler, Vector2u size, int partCount)
	:Scene(sceneHandler), cellCount(size), partCount(partCount)
{
	font = new Font();
	this->font->loadFromFile("Textures/cool.ttf");
	this->setupResources();
	this->confVarUpdate();
}

SceneSnakeGame::~SceneSnakeGame()
{
}

void SceneSnakeGame::handleInputs(RenderWindow & window)
{
	if (Keyboard::isKeyPressed(moveLeft) && this->snakeDirection != RIGHT)
		this->snakeDirectionNew = LEFT;
	else if (Keyboard::isKeyPressed(moveRight) && this->snakeDirection != LEFT)
		this->snakeDirectionNew = RIGHT;
	else if (Keyboard::isKeyPressed(moveUp) && this->snakeDirection != BOTTOM)
		this->snakeDirectionNew = TOP;
	else if (Keyboard::isKeyPressed(moveDown) && this->snakeDirection != TOP)
		this->snakeDirectionNew = BOTTOM;

	if (Keyboard::isKeyPressed(Keyboard::P))
	{
		if (this->gameState == SNAKERUNNING)
			this->gameState = SNAKEPAUSED;
		else if (this->gameState == SNAKEPAUSED)
			this->gameState = SNAKERUNNING;
	}

	if (Keyboard::isKeyPressed(Keyboard::R) && this->gameState != SNAKEFINISHED)
	{
		this->gameState = eSnakeState::SNAKESETUP;
	}

	if (Keyboard::isKeyPressed(Keyboard::I))
	{
		this->visible = NONE;
		this->getSceneHandler().setTopScene("GOL");
		this->getSceneHandler().getSceneByName("GOL")->visible =  ALL;
	}
}

void SceneSnakeGame::render(RenderWindow & window, RenderStates& shades, float timeTillUpdate)
{
	Scene::render(window, shades, timeTillUpdate);
}

void SceneSnakeGame::confVarUpdate()
{
	configHelper->readComplete();
	// Setup Keys
	moveUp = keyDef::get().keyCode.get(configHelper->get("Snake", "MOVE-UP"));
	moveDown = keyDef::get().keyCode.get(configHelper->get("Snake", "MOVE-DOWN"));
	moveRight = keyDef::get().keyCode.get(configHelper->get("Snake", "MOVE-RIGHT"));
	moveLeft = keyDef::get().keyCode.get(configHelper->get("Snake", "MOVE-LEFT"));
}

bool SceneSnakeGame::setupResources()
{
	this->configHelper = new ConfigHelper("test.txt");
	this->createScene();

	return false;
}

void SceneSnakeGame::update()
{
	Scene::update();

	switch (this->gameState)
	{
	case eSnakeState::SNAKEPAUSED:
		break;
	case eSnakeState::SNAKERUNNING:
		this->running();
		break;
	case eSnakeState::SNAKEFINISHED:
		this->gameFinished();
		break;
	case eSnakeState::SNAKESETUP:
		this->objects.clear();
		this->snakeBody.clear();
		this->createScene();
		break;
	}
}

bool SceneSnakeGame::setupFood()
{
	mt19937 rd;
	rd.seed(random_device()());
	uniform_int_distribution<mt19937::result_type> randomFoodX(0, cellCount.x - 1);
	uniform_int_distribution<mt19937::result_type> randomFoodY(0, cellCount.y - 1);

	float partSizeX = float(PITCH) / float(cellCount.x);
	float partSizeY = float(PITCH) / float(cellCount.y);

	unsigned int randomX;
	unsigned int randomY;

	bool error = true;
	while (error)
	{
		error = false;
		randomX = randomFoodX(rd);
		randomY = randomFoodY(rd);

		for (unsigned int i = 0; i < this->snakeBody.size(); i++)
		{
			Vector2f snakePos = this->snakeBody.at(i)->objectShape->getPosition();

			if (snakePos.x == float(randomX * partSizeX + POSX + THICKNESS)
			 && snakePos.y == float(randomY * partSizeY + POSY + THICKNESS))
				error = true;
		}
	}

	this->snakeFood->objectShape->setPosition(Vector2f(float(randomX * partSizeX + POSX + THICKNESS)
											   , float(randomY * partSizeY + POSY + THICKNESS)));

	return true;
}

void SceneSnakeGame::createScene()
{
	this->sceneWorld = new Box2DWorld(b2Vec2(5, 10.0f));
	
	addResource("Ground", new PhysicalObjectBase(new ShapeRectangle(FloatRect(200, 600, 1000, 100), Color::Green), new BodyRectangle(), this->sceneWorld));
	PhysicalObjectBase* tmp = addResource("Box", new PhysicalObjectBase(new ShapeRectangle(FloatRect(700, 100, 20, 20), Color::Blue)));
	
	//set Friction and density
	b2FixtureDef fixtureDef;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	//cast fixture to body
	tmp->setDynamicBody(new BodyRectangle(), fixtureDef, this->sceneWorld);



	//this->texture->loadFromFile("Textures/plus.png");
	texture = new Texture();
	texture->loadFromFile("Textures/plus.png");

	addObject("Background", new ShapeRectangle(FloatRect(POSX, POSY, PITCH, PITCH), Color::Black, float(PITCH) / float(50), Color::White));

	float partSizeX = float(PITCH) / float(cellCount.x);
	float partSizeY = float(PITCH) / float(cellCount.y);

	for (int i = 0; i < this->partCount; i++)
	{
		this->snakeBody.push_back(addObject("Snake" + to_string(i), new ShapeRectangle(Vector2f((partSizeX - THICKNESS * 2), (partSizeY - THICKNESS * 2)), Color::Color(stoul(configHelper->get("Snake", "BodyColor"), nullptr, 16)), THICKNESS, Color::Color(stoul(configHelper->get("Snake", "BodyOColor"), nullptr, 16)))));
		this->objects.get("Snake" + to_string(i))->objectShape->setPosition(Vector2f((POSX + THICKNESS) + (cellCount.x / 2) * partSizeX + partSizeX * i, ((POSY + THICKNESS) + partSizeY * (cellCount.x / 2))));
	}

	this->objects.get("Snake0")->objectShape->setFillColor(Color::Color(stoul(configHelper->get("Snake", "HeadColor"), nullptr, 16)));
	this->objects.get("Snake0")->objectShape->setOutlineColor(Color::Color(stoul(configHelper->get("Snake", "HeadOColor"), nullptr, 16)));

	this->snakeFood = addObject("Food", new ShapeRectangle(Vector2f((partSizeX - THICKNESS * 2), (partSizeY - THICKNESS * 2)), Color::Color(stoul(configHelper->get("Snake", "FoodColor"), nullptr, 16)), THICKNESS, Color::Color(stoul(configHelper->get("Snake", "FoodOColor"), nullptr, 16))));

	// Scorecounter Setup
	score = addObject("GridSizeText", new ShapeRectangle(Vector2f(200, 100)));
	score->shapeVisible = NONE;
	score->addText(new ObjectText("Score: " + to_string(scoreCount), *font));
	score->objectText->setCharacterSize(40);
	score->objectText->setFillColor(Color::White);

	alignNextTo(*score->objectText, *objects.get("Background")->objectShape, RIGHT, 100);

	// Nachricht wenn du gestorben bist
	addObject("Finished", new ShapeRectangle(FloatRect(POSX + PITCH / 2 - 40, POSY + PITCH / 2 - 40, 40, 40)));
	this->objects.get("Finished")->addText(new ObjectText("Press R to Restart", *font));
	alignTo(*objects.get("Finished")->objectText, *objects.get("Background")->objectShape);
	this->objects.get("Finished")->textVisible = NONE;

	this->setupFood();

	// Werte setzen
	this->snakeDirection = LEFT;
	this->snakeDirectionNew = LEFT;
	this->scoreCount = 0;
	this->updateRate = 150;
	this->gameState = eSnakeState::SNAKERUNNING;
}

void SceneSnakeGame::gameFinished()
{
	this->objects.get("Finished")->textVisible = ALL;
	this->gameState = eSnakeState::SNAKEFINISHED;
}

void SceneSnakeGame::running()
{
	float partSizeX = float(PITCH) / float(cellCount.x);
	float partSizeY = float(PITCH) / float(cellCount.y);

	Vector2f nextPos;
	//Berechne NeuePos
	if (snakeDirectionNew == LEFT)
	{
		snakeDirection = LEFT;

		nextPos = Vector2f(this->snakeBody.at(0)->objectShape->getPosition().x - partSizeX, this->snakeBody.at(0)->objectShape->getPosition().y);
	}
	else if (snakeDirectionNew == RIGHT)
	{
		snakeDirection = RIGHT;

		nextPos = Vector2f(this->snakeBody.at(0)->objectShape->getPosition().x + partSizeX, this->snakeBody.at(0)->objectShape->getPosition().y);
	}
	else if (snakeDirectionNew == TOP)
	{
		snakeDirection = TOP;

		nextPos = Vector2f(this->snakeBody.at(0)->objectShape->getPosition().x, this->snakeBody.at(0)->objectShape->getPosition().y - partSizeY);
	}
	else if (snakeDirectionNew == BOTTOM)
	{
		snakeDirection = BOTTOM;

		nextPos = Vector2f(this->snakeBody.at(0)->objectShape->getPosition().x, this->snakeBody.at(0)->objectShape->getPosition().y + partSizeY);
	}

	//Collisionsabfragen
	for (int i = this->snakeBody.size() - 2; i > 0; i--)
	{
		if (this->snakeBody.at(i)->objectShape->getPosition() == nextPos)
		{
			this->gameState = SNAKEFINISHED;
			return;
		}
	}

	if ((POSX > nextPos.x) || ((POSX + PITCH) <= nextPos.x) || ((POSY + PITCH) <= nextPos.y) || (POSY > nextPos.y))
	{
		this->gameState = SNAKEFINISHED;
		return;
	}

	//Bewegung der Snake
	for (int i = this->snakeBody.size() - 1; i > 0; i--)
	{
		this->snakeBody.at(i)->objectShape->setPosition(this->snakeBody.at(i - 1)->objectShape->getPosition());
	}
	this->snakeBody.at(0)->objectShape->setPosition(nextPos);

	//Snakewachstum und Essensspawning
	Vector2f lastSnakePartPos = this->snakeBody.at(this->snakeBody.size() - 1)->objectShape->getPosition();
	Vector2f foodPos = this->snakeFood->objectShape->getPosition();
	if (foodPos.x == nextPos.x && foodPos.y == nextPos.y)
	{
		this->setupFood();
		this->snakeBody.push_back(addObject("Snake" + to_string(this->snakeBody.size()), new ShapeRectangle(Vector2f((partSizeX - THICKNESS * 2), (partSizeY - THICKNESS * 2)), Color::Color(stoul(configHelper->get("Snake", "BodyColor"), nullptr, 16)), THICKNESS, Color::Color(stoul(configHelper->get("Snake", "BodyOColor"), nullptr, 16))), 1));
		this->objects.get("Snake" + to_string(this->snakeBody.size() - 1))->objectShape->setPosition(lastSnakePartPos);

		// Erh�he Scorecount
		scoreCount++;
		score->objectText->setString("Score: " + to_string(scoreCount));
		updateRate -= 2;
	}
}
