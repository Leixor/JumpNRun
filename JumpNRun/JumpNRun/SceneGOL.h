#pragma once
#include "Scene.h"
#include "ShapeSprite.h"
#include "ShapeRectangle.h"
#include "Button.h"

enum eGOLStates 
{
	GOLSETUPSIZE = 1,
	GOLSETUPFIELD = 2,
	GOLINGAME = 4,
	GOLPAUSED = 8
};

class SceneGOL : public Scene
{
public:
	SceneGOL(string name, SceneHandler& sceneHandler, RenderWindow* window);
	~SceneGOL();

	bool setupResources();
	void update();
	void handleInputs(RenderWindow& window);
	void handleEvents(RenderWindow & window, Event& windowEvent);
	void render(RenderWindow& window, RenderStates& shades, float timeTillUpdate);

private:
	Font * font;
	eGOLStates gameState;
	vector<vector<char>> gameField;

	string sizeText;
	ObjectBase* generationText;
	ObjectBase* gridSizeText;
	ObjectBase* gpsText;
	DrawableObject* background;
	DrawableObject* proto;
	ShapeRectangle* rect;
	ShapeSprite* sprit;

	int gridSize;
	float cellSize;
	int generation;

	void plusGridSize();
	void minusGridSize();
	void setupField();
	void runGameSimulation();
};

