#pragma once
enum GameState {
	SETUPSIZE  = 1,
	SETUPFIELD = 2,
	INGAME = 4,
	PAUSED = 8
};
class GameOfLife : public Scene
{
public:
	GameOfLife(string name, SceneHandler * sceneHandler, RenderWindow* window);
	~GameOfLife();

	bool setupResources();
	void update();
	void handleInputs(RenderWindow& window);
	void handleEvents(RenderWindow & window, Event windowEvent);
	void render(RenderWindow& window, RenderStates shades, float timeTillUpdate);

private:
	Font * font;
	vector<vector<bool>> gameField;

	int gridSize;
	float cellSize;
	string sizeText;
	ObjectBase* gridSizeText;

	DrawableObject* proto;
	ShapeRectangle* rect;
	ShapeSprite* sprit;

	ObjectBase* generationText;
	DrawableObject* background;
	int generation;

	void plusGridSize();
	void minusGridSize();
	void setupField();
	void runGameSimulation();
	void determineState();

	int gameState;


	int updateCount;
	int updateRate;
};

