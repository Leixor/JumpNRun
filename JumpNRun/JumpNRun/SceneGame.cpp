#include "standardInclude.h"

#define PITCH 600
#define POSX 100
#define POSY 100

SceneGame::SceneGame(string name, SceneHandler * sceneHandler, Vector2u size, int partCount)
	:Scene(name, sceneHandler), size(size), partCount(partCount)
{
	this->setupResources();
	this->snakeDirection = LEFT;
	this->snakeDirectionNew = LEFT;
	this->gameFinished = false;
}

SceneGame::~SceneGame()
{
}

void SceneGame::handleEvents(RenderWindow & window, Event windowEvent)
{
	for (int i = this->objects.size() - 1; i >= 0; i--)
	{
		if (objects.get(i)->handleEvents(window, windowEvent))
			break;
	}
}

void SceneGame::handleInputs(RenderWindow & window)
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

bool SceneGame::setupResources()
{
	addResource<ObjectBase*>("Background", new ObjectBase(RectangleShape()));
	this->objects.get("Background")->shape->setPosition(Vector2f(POSX, POSY));
	this->objects.get("Background")->shape->setSize(Vector2f(PITCH, PITCH));
	this->objects.get("Background")->shape->setFillColor(Color::Black);
	this->objects.get("Background")->shape->setOutlineThickness(float(PITCH) / float(50));
	this->objects.get("Background")->shape->setOutlineColor(Color::White);

	float partSizeX = float(PITCH) / float(size.x);
	float partSizeY = float(PITCH) / float(size.y);
	float thickness = float(PITCH) / float(300);

	for (int i = 0; i < this->partCount; i++)
	{
		this->snakeBody.push_back(addResource<ObjectBase*>("Snake" + to_string(i), new ObjectBase(RectangleShape())));
		this->objects.get("Snake" + to_string(i))->shape->setPosition(Vector2f((POSX + thickness) + (size.x / 2) * partSizeX + partSizeX * i, ((POSY + thickness) + partSizeY * (size.x / 2))));
		this->objects.get("Snake" + to_string(i))->shape->setSize(Vector2f((partSizeX - thickness * 2), (partSizeY - thickness * 2)));
		this->objects.get("Snake" + to_string(i))->shape->setFillColor(Color::Black);
		this->objects.get("Snake" + to_string(i))->shape->setOutlineThickness(thickness);
		this->objects.get("Snake" + to_string(i))->shape->setOutlineColor(Color::White);
	}

	this->objects.get("Snake0")->shape->setOutlineColor(Color::Red);

	return false;
}

void SceneGame::update()
{
	if (!gameFinished)
	{
		float partSizeX = float(PITCH) / float(size.x);
		float partSizeY = float(PITCH) / float(size.y);
		
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
	}
}
