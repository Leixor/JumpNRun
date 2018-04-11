#pragma once

enum eSnakeState
{
	SNAKEPAUSED = 1,
	SNAKERUNNING = 2,
	SNAKEFINISHED = 4,
	SNAKESETUP = 8
};

class SceneSnakeGame : public Scene
{
public:
	SceneSnakeGame(string name, SceneHandler& sceneHandler, Vector2u size, int partCount);
	~SceneSnakeGame();

	void handleEvents(RenderWindow & window, Event& windowEvent);
	void handleInputs(RenderWindow & window);
	void render(RenderWindow& window, RenderStates& shades, float timeTillUpdate);
	void confVarUpdate();
	bool setupResources();
	void update();

private:
	//Speichert die Anzahl der Felder des SnakeGame
	Vector2u cellCount;
	//Die alte Richtung gibt diehnt zur Bestimmung welche Richtung nicht als neue Richtung definiert werden kann
	eOrientation snakeDirection;
	//Die neue Richtung wird bei Update der Snake gegeben
	eOrientation snakeDirectionNew;
	eSnakeState gameState;
	vector<ObjectBase*> snakeBody;
	ObjectBase* snakeFood;
	Font* font;
	ObjectBase* score;
	//Die Keys werden aus der Config geladen
	Keyboard::Key moveDown;
	Keyboard::Key moveUp;
	Keyboard::Key moveRight;
	Keyboard::Key moveLeft;
	int partCount;
	int scoreCount;

	bool setupFood();
	void createScene();
	void gameFinished();
	void running();
};

