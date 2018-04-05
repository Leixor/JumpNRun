#include "standardInclude.h"

#define PITCH 600
#define POSX 100
#define POSY 100
#define THICKNESS float(PITCH) / float(300)

SceneSnakeGame::SceneSnakeGame(string name, SceneHandler * sceneHandler, Vector2u size, int partCount)
	:Scene(name, sceneHandler), cellCount(size), partCount(partCount)
{
	this->setupResources();
	this->snakeDirection = LEFT;
	this->snakeDirectionNew = LEFT;
	this->gameFinished = false;
	
	this->setupFood();
}

SceneSnakeGame::~SceneSnakeGame()
{
}

void SceneSnakeGame::handleEvents(RenderWindow & window, Event windowEvent)
{
	for (int i = this->objects.size() - 1; i >= 0; i--)
	{
		if (objects.get(i)->handleEvents(window, windowEvent))
			break;
	}
	if (windowEvent.type == Event::KeyPressed)
		if (Keyboard::isKeyPressed(Keyboard::E))
			this->visible = VISIBLE;
}

void SceneSnakeGame::handleInputs(RenderWindow & window)
{
	if (Keyboard::isKeyPressed(Keyboard::A) && this->snakeDirection != RIGHT)
		this->snakeDirectionNew = LEFT;
	else if (Keyboard::isKeyPressed(Keyboard::D) && this->snakeDirection != LEFT)
		this->snakeDirectionNew = RIGHT;
	else if (Keyboard::isKeyPressed(Keyboard::W) && this->snakeDirection != BOTTOM)
		this->snakeDirectionNew = TOP;
	else if (Keyboard::isKeyPressed(Keyboard::S) && this->snakeDirection != TOP)
		this->snakeDirectionNew = BOTTOM;
}

bool SceneSnakeGame::setupResources()
{
	addResource<ObjectBase*>("Background", new ObjectBase(RectangleShape()));
	this->objects.get("Background")->shape->setPosition(Vector2f(POSX, POSY));
	this->objects.get("Background")->shape->setSize(Vector2f(PITCH, PITCH));
	this->objects.get("Background")->shape->setFillColor(Color::Black);
	this->objects.get("Background")->shape->setOutlineThickness(float(PITCH) / float(50));
	this->objects.get("Background")->shape->setOutlineColor(Color::White);

	float partSizeX = float(PITCH) / float(cellCount.x);
	float partSizeY = float(PITCH) / float(cellCount.y);

	for (int i = 0; i < this->partCount; i++)
	{
		this->snakeBody.push_back(addResource<ObjectBase*>("Snake" + to_string(i), new ObjectBase(RectangleShape())));
		this->objects.get("Snake" + to_string(i))->shape->setPosition(Vector2f((POSX + THICKNESS) + (cellCount.x / 2) * partSizeX + partSizeX * i, ((POSY + THICKNESS) + partSizeY * (cellCount.x / 2))));
		this->objects.get("Snake" + to_string(i))->shape->setSize(Vector2f((partSizeX - THICKNESS * 2), (partSizeY - THICKNESS * 2)));
		this->objects.get("Snake" + to_string(i))->shape->setFillColor(Color::Black);
		this->objects.get("Snake" + to_string(i))->shape->setOutlineThickness(THICKNESS);
		this->objects.get("Snake" + to_string(i))->shape->setOutlineColor(Color::White);
	}

	this->objects.get("Snake0")->shape->setOutlineColor(Color::Red);

	this->snakeFood = addResource<ObjectBase*>("Food", new ObjectBase(RectangleShape()));
	this->objects.get("Food")->shape->setSize(Vector2f((partSizeX - THICKNESS * 2), (partSizeY - THICKNESS * 2)));
	this->objects.get("Food")->shape->setFillColor(Color::Black);
	this->objects.get("Food")->shape->setOutlineThickness(THICKNESS);
	this->objects.get("Food")->shape->setOutlineColor(Color::Cyan);

	return false;
}

void SceneSnakeGame::update()
{
	if (!gameFinished)
	{
		float partSizeX = float(PITCH) / float(cellCount.x);
		float partSizeY = float(PITCH) / float(cellCount.y);

		Vector2f nextPos;
		//Berechne NeuePos
		if (snakeDirectionNew == LEFT)
		{
			snakeDirection = LEFT;

			nextPos = Vector2f(this->snakeBody.at(0)->shape->getPosition().x - partSizeX, this->snakeBody.at(0)->shape->getPosition().y);
		}
		else if (snakeDirectionNew == RIGHT)
		{
			snakeDirection = RIGHT;

			nextPos = Vector2f(this->snakeBody.at(0)->shape->getPosition().x + partSizeX, this->snakeBody.at(0)->shape->getPosition().y);
		}
		else if (snakeDirectionNew == TOP)
		{
			snakeDirection = TOP;

			nextPos = Vector2f(this->snakeBody.at(0)->shape->getPosition().x, this->snakeBody.at(0)->shape->getPosition().y - partSizeY);
		}
		else if (snakeDirectionNew == BOTTOM)
		{
			snakeDirection = BOTTOM;

			nextPos = Vector2f(this->snakeBody.at(0)->shape->getPosition().x, this->snakeBody.at(0)->shape->getPosition().y + partSizeY);
		}

		//Collisionsabfragen
		for (int i = this->snakeBody.size() - 2; i > 0; i--)
		{
			if (this->snakeBody.at(i)->shape->getPosition() == nextPos)
			{
				this->gameFinished = true;
				return;
			}
		}

		if ((POSX > nextPos.x) || ((POSX + PITCH) <= nextPos.x) || ((POSY + PITCH) <= nextPos.y) || (POSY > nextPos.y))
		{
			this->gameFinished = true;
			return;
		}

		//Bewegung der Snake
		for (int i = this->snakeBody.size() - 1; i > 0; i--)
		{
			this->snakeBody.at(i)->shape->setPosition(this->snakeBody.at(i - 1)->shape->getPosition());
		}
		this->snakeBody.at(0)->shape->setPosition(nextPos);

		//Snakewachstum und Essensspawning
		Vector2f lastSnakePartPos = this->snakeBody.at(this->snakeBody.size() - 1)->shape->getPosition();
		Vector2f foodPos = this->snakeFood->shape->getPosition();
		if (foodPos.x == nextPos.x && foodPos.y == nextPos.y)
		{
			this->setupFood();
			this->snakeBody.push_back(addResource<ObjectBase*>("Snake" + to_string(this->snakeBody.size()), new ObjectBase(RectangleShape())));
			this->objects.get("Snake" + to_string(this->snakeBody.size() - 1))->shape->setPosition(lastSnakePartPos);
			this->objects.get("Snake" + to_string(this->snakeBody.size() - 1))->shape->setSize(Vector2f((partSizeX - THICKNESS * 2), (partSizeY - THICKNESS * 2)));
			this->objects.get("Snake" + to_string(this->snakeBody.size() - 1))->shape->setFillColor(Color::Black);
			this->objects.get("Snake" + to_string(this->snakeBody.size() - 1))->shape->setOutlineThickness(THICKNESS);
			this->objects.get("Snake" + to_string(this->snakeBody.size() - 1))->shape->setOutlineColor(Color::White);
		}
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
			Vector2f snakePos = this->snakeBody.at(i)->shape->getPosition();

			if (snakePos.x == float(randomX * partSizeX + POSX + THICKNESS)
			 && snakePos.y == float(randomY * partSizeY + POSY + THICKNESS))
				error = true;
		}
	}

	this->snakeFood->shape->setPosition(Vector2f(float(randomX * partSizeX + POSX + THICKNESS)
											   , float(randomY * partSizeY + POSY + THICKNESS)));

	return true;
}
