#pragma once

class SceneGame : public Scene
{
public:
	SceneGame(string name, SceneHandler * sceneHandler, Vector2u size, int partCount);
	~SceneGame();

	void handleEvents(RenderWindow & window, Event windowEvent);
	void handleInputs(RenderWindow & window);
	bool setupResources();
	void update();

private:
	Vector2u size;
	eOrientation snakeDirection;
	eOrientation snakeDirectionNew;
	bool gameFinished;
	int partCount;
	int updateCount;

	vector<ObjectBase*> snakeBody;
};

