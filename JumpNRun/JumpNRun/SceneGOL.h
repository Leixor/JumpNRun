#pragma once

enum eGameState 
{
	SETUPSIZE = 1,
	SETUPFIELD = 2,
	INGAME = 4,
	PAUSED = 8
};

class SceneGOL : public Scene
{
public:
	SceneGOL(string name, SceneHandler * sceneHandler, RenderWindow* window);
	~SceneGOL();

	bool setupResources();
	void update();
	void handleInputs(RenderWindow& window);
	void handleEvents(RenderWindow & window, Event windowEvent);
	void render(RenderWindow& window, RenderStates shades, float timeTillUpdate);

private:
	Font * font;
	eGameState gameState;
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

