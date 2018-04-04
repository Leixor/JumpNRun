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
	void handleInput(RenderWindow& window, vector<Event>& windowEvents);
	void render(RenderWindow& window, RenderStates shades);

private:
	Font * font;
	vector<vector<bool>> gameField;

	int gridSize;
	float cellSize;
	string sizeText;
	ObjectBase* gridSizeText;

	void plusGridSize();
	void minusGridSize();
	void setupField();
	void runGameSimulation();
	void determineState();

	int gameState;
};
