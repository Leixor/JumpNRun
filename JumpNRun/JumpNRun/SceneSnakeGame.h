#pragma once
#include "Scene.h"
#include "ShapeRectangle.h"
#include "ShapeSprite.h"
#include "StandardInclude.h"
#include "PhysicalObjectBase.h"
#include "BodyRectangle.h"

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
	SceneSnakeGame(SceneHandler& sceneHandler, Vector2u size, int partCount);
	~SceneSnakeGame();

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
	vector<BaseResource*> snakeBody;
	BaseResource* snakeFood;
	Font* font;
	BaseResource* score;
	//Die Keys werden aus der Config geladen
	Keyboard::Key moveDown;
	Keyboard::Key moveUp;
	Keyboard::Key moveRight;
	Keyboard::Key moveLeft;
	int partCount;
	int scoreCount;

	Texture* texture;

	bool setupFood();
	void createScene();
	void gameFinished();
	void running();
};

