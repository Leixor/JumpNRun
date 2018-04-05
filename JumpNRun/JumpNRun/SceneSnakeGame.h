#pragma once

class SceneSnakeGame : public Scene
{
public:
	SceneSnakeGame(string name, SceneHandler * sceneHandler, Vector2u size, int partCount);
	~SceneSnakeGame();

	void handleEvents(RenderWindow & window, Event windowEvent);
	void handleInputs(RenderWindow & window);
	bool setupResources();
	void update();

private:
	Vector2u cellCount;
	eOrientation snakeDirection;
	eOrientation snakeDirectionNew;
	bool gameFinished;
	int partCount;

	vector<ObjectBase*> snakeBody;
	ObjectBase* snakeFood;

	Font* font;
	ObjectBase* score;
	int scoreCount;

	bool setupFood();
};

