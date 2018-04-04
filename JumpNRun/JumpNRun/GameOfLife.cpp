#include "standardInclude.h"



GameOfLife::GameOfLife(string name, SceneHandler * sceneHandler, RenderWindow* window): Scene(name, sceneHandler, window)
{
	this->setupResources();
}


GameOfLife::~GameOfLife()
{
}

bool GameOfLife::setupResources()
{
	// Standard Gamestate angeben
	gameState = SETUPSIZE;

	// Font laden
	font = new Font();
	this->font->loadFromFile("Textures/cool.ttf");

	// StandardgridSize definieren
	gridSize = 100;
	sizeText = to_string(gridSize) + " x " + to_string(gridSize);
	cellSize = window->getSize().x / (float)gridSize;

	// UI adden
	addResource<ObjectBase*>("Background", new Button([&] {plusGridSize(); }, new DrawableShape<RectangleShape>(Vector2f(1600,900), Vector2f(0,0))));
	objects.get("Background")->shape->setFillColor(Color::Black);
	addResource<Button*>("+size", new Button([&] {plusGridSize(); }, new DrawableShape<Sprite>("Textures/plus.png")));
	addResource<Button*>("-size", new Button([&] {minusGridSize(); }, new DrawableShape<Sprite>("Textures/minus.png")));
	gridSizeText = addResource<ObjectBase*>("GridSizeText", new ObjectBase(new DrawableShape<RectangleShape>(Vector2f(200, 100), Vector2f(0, 0))));
	gridSizeText->shapeVisible = NONE;
	gridSizeText->addText(sizeText, *font);
	gridSizeText->setTextSize(40);
	objects.get("-size")->shape->scale(Vector2f(.2f, .2f));
	objects.get("+size")->shape->scale(Vector2f(.2f, .2f));
	alignTo(*objects.get("-size")->shape, *objects.get("Background")->shape, BOTTOM | LEFT);
	objects.get("-size")->shape->move(Vector2f(100, -100));
	alignNextTo(*gridSizeText->objectText, *objects.get("-size")->shape, RIGHT);
	alignNextTo(*objects.get("+size")->shape, *gridSizeText->objectText, RIGHT);

	return false;
}

void GameOfLife::update()
{
	Scene::update();
	switch (gameState) {
		case SETUPFIELD:
			setupField();
			break;
		case INGAME:
			runGameSimulation();
			break;
		case PAUSED:
			break;
	}
}

void GameOfLife::handleInput(RenderWindow& window, vector<Event>& windowEvents)
{
	Scene::handleInput(window, windowEvents);

	// Falls das Game noch im Setup ist soll an den Stellen wo der Spieler hinklickt eine Zelle zum Leben erweckt werden falls dort noch keine lebende ist
	if (gameState & SETUPFIELD || gameState & PAUSED) {
		if (Mouse::isButtonPressed(Mouse::Left)) {
			Vector2i mousePos = Mouse::getPosition(window);
			FloatRect Cell(0,0, cellSize, cellSize);
			for (int i = 0; i < gridSize / (16 / 9); i++) {
				for (int j = 0; j < gridSize; j++) {
					Cell.left = cellSize * i;
					Cell.top = cellSize * j;
					if (Cell.contains(Vector2f(mousePos.x, mousePos.y)) && !gameField[i][j]) {
						gameField[j][i] = true;
					}
				}
			}
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::C)) {
		gameState = SETUPFIELD;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
		gameState = INGAME;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::P)) {
		gameState = PAUSED;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::R)) {
		for (int i = 0; i < gridSize / (16 / 9); i++) {
			gameField.push_back(vector<bool>());
			for (int j = 0; j < gridSize; j++) {
				gameField[i][j] = false;
			}
		}
	}
}

void GameOfLife::render(RenderWindow& window, RenderStates shades) {
	Scene::render(window, shades);

	// Das richtige Gamefield anzeigen
	if (gameField.size() != 0)
	{
		RectangleShape proto(Vector2f(cellSize, cellSize));
		for (int i = 0; i < gridSize / (16 / 9); i++) {
			for (int j = 0; j < gridSize; j++) {
				if (this->gameField[i][j] == true) {
					proto.setPosition(j*cellSize, i*cellSize);
					window.draw(proto);
				}
			}
		}
	}
	
}

void GameOfLife::plusGridSize()
{
	if (gameState & SETUPSIZE)
	{
		gridSize++;
		sizeText = to_string(gridSize) + " x " + to_string(gridSize);
		gridSizeText->setText(sizeText);
		cellSize = window->getSize().x / (float)gridSize;
	}

}

void GameOfLife::minusGridSize()
{
	if (gameState & SETUPSIZE)
	{
		gridSize--;
		sizeText = to_string(gridSize) + " x " + to_string(gridSize);
		gridSizeText->setText(sizeText);
		cellSize = window->getSize().x / (float)gridSize;
	}
}

void GameOfLife::setupField()
{
	// GameField tot populieren
	for (int i = 0; i < gridSize / (16 / 9); i++) {
		gameField.push_back(vector<bool>());
		for (int j = 0; j < gridSize; j++) {
			gameField[i].push_back(false);
		}
	}
}

void GameOfLife::runGameSimulation()
{
	this->determineState();
}

void GameOfLife::determineState() {
	vector<vector<bool>> oldGen;
	oldGen = gameField;

	for (int a = 0; a < gridSize-1; a++)
	{
		for (int b = 0; b < gridSize-1; b++)
		{
			int alive = 0;
			for (int c = -1; c < 2; c++)
			{
				for (int d = -1; d < 2; d++)
				{
					if(!((a == 0 && c == -1) || (b == 0 && d == -1)))
					{
						if (oldGen[a + c][b + d])
						{
							alive++;
						}
					}
				}
			}
			if (oldGen[a][b]) alive--;
			if (alive < 2)
			{
				gameField[a][b] = false;
			}
			else if (alive == 3)
			{
				gameField[a][b] = true;
			}
			else if (alive > 3)
			{
				gameField[a][b] = false;
			}
		}
	}
}
