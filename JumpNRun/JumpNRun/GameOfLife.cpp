#include "standardInclude.h"

#define CELLCOLOR Color::Cyan

GameOfLife::GameOfLife(string name, SceneHandler * sceneHandler, RenderWindow* window): Scene(name, sceneHandler, window)
{
	this->setupResources();
}

GameOfLife::~GameOfLife()
{
}

bool GameOfLife::setupResources()
{
	updateRate = 100;
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
	background = new ShapeRectangle(1600, 900, Color::White);
	addResource("+size", new Button([&] {plusGridSize(); }, new ShapeSprite("Textures/plus.png", .1f)));
	addResource("-size", new Button([&] {minusGridSize(); }, new ShapeSprite("Textures/minus.png", .1f)));
	gridSizeText = addObject("GridSizeText", new ShapeRectangle(Vector2f(200, 100)));
	gridSizeText->shapeVisible = NONE;
	gridSizeText->addText(sizeText, *font);
	gridSizeText->setTextSize(40);
	gridSizeText->objectText->setFillColor(Color::Black);
	alignTo(*objects.get("-size")->shape, *background, BOTTOM | LEFT);
	objects.get("-size")->shape->move(Vector2f(20, -20));
	alignNextTo(*gridSizeText->objectText, *objects.get("-size")->shape, RIGHT);
	alignNextTo(*objects.get("+size")->shape, *gridSizeText->objectText, RIGHT);

	generationText = addObject("generationText", new ShapeRectangle(Vector2f(200, 100)));
	generationText->shapeVisible = NONE;
	generationText->addText("Generation: " + to_string(generation), *font);
	generationText->setTextSize(40);
	generationText->objectText->setFillColor(Color::Black);

	alignNextTo(*generationText->objectText, *objects.get("+size")->shape, RIGHT, 100);

	rect = new ShapeRectangle(Vector2f(cellSize, cellSize), CELLCOLOR);
	sprit = new ShapeSprite("Textures/plus.png", Vector2f(cellSize, cellSize));

	proto = sprit;

	return false;
}

void GameOfLife::update()
{
	Scene::update();

	if (this->getUpdateSync()) 
	{
		switch (gameState) 
		{
		case SETUPFIELD:
			setupField();
			break;
		case INGAME:
			runGameSimulation();
			generation++;
			break;
		case PAUSED:
			break;
		}
		generationText->setText("Generation: " + to_string(generation));
	}
}

void GameOfLife::handleInputs(RenderWindow& window)
{
	Scene::handleInputs(window);

	// Falls das Game noch im Setup ist soll an den Stellen wo der Spieler hinklickt eine Zelle zum Leben erweckt werden falls dort noch keine lebende ist
	if (gameState & SETUPFIELD || gameState & PAUSED) 
	{
		if (Mouse::isButtonPressed(Mouse::Left)) 
		{
			Vector2i mousePos = Mouse::getPosition(window);
			FloatRect Cell(0,0, cellSize, cellSize);
			for (int i = 0; i < gridSize / (16 / 9); i++) 
			{
				for (int j = 0; j < gridSize; j++) 
				{
					Cell.left = cellSize * i;
					Cell.top = cellSize * j;
					if (Cell.contains(Vector2f(float(mousePos.x), float(mousePos.y)))/* && !gameField[i][j]*/) 
					{
						gameField[j][i] = true;
					}
				}
			}
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::C)) 
	{
		gameState = SETUPFIELD;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::A)) 
	{
		setupField();
		gameState = INGAME;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::P)) 
	{
		gameState = PAUSED;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::R)) 
	{
		gameField.clear();
		generation = 0;
		gameState = SETUPFIELD;
	}

	if (Keyboard::isKeyPressed(Keyboard::Key::N)) 
	{
		generation = 0;
		gameState = SETUPSIZE;
		gameField.clear();
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Right)) 
	{
		
		proto = rect;
		proto->setSize(Vector2f(cellSize, cellSize));
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Left)) 
	{

		proto = sprit;
		proto->setSize(Vector2f(cellSize, cellSize));
	}
	
	if (Keyboard::isKeyPressed(Keyboard::Key::O)) 
	{
		this->getSceneHandler()->setTopScene("SnakeGame");
		this->getSceneHandler()->getSceneByName("SnakeGame")->visible = ALL;
		this->visible = NONE;
	}
}

void GameOfLife::handleEvents(RenderWindow & window, Event windowEvent)
{
	Scene::handleEvents(window, windowEvent);
	if (windowEvent.type == Event::KeyPressed) {
		if (Keyboard::isKeyPressed(Keyboard::Key::Up)) {

			updateRate -= 10;
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::Down)) {

			updateRate += 10;
		}
	}
}

void GameOfLife::render(RenderWindow& window, RenderStates shades, float timeTillUpdate) {
	
	background->draw(window, shades);
	// Das richtige Gamefield anzeigen
	if (gameField.size() != 0)
	{
		for (int i = 0; i < gridSize / (16 / 9); i++) {
			for (int j = 0; j < gridSize; j++) {
				if (this->gameField[i][j] == true) {
					this->proto->setPosition(Vector2f(j*cellSize, i*cellSize));
					this->proto->draw(window, shades);
				}
			}
		}
	}
	Scene::render(window, shades, timeTillUpdate);
}

void GameOfLife::plusGridSize()
{
	if (gameState & SETUPSIZE)
	{
		gridSize++;
		sizeText = to_string(gridSize) + " x " + to_string(gridSize);
		gridSizeText->setText(sizeText);
		cellSize = (float)window->getSize().x / (float)gridSize;
		
		cout << cellSize << "\n";
		
		proto->setSize(Vector2f(cellSize, cellSize));
	}
}

void GameOfLife::minusGridSize()
{
	if (gameState & SETUPSIZE)
	{
		gridSize--;

		sizeText = to_string(gridSize) + " x " + to_string(gridSize);
		gridSizeText->setText(sizeText);

		cellSize = (float)window->getSize().x / (float)gridSize;

		cout << cellSize << "\n";

		proto->setSize(Vector2f(cellSize, cellSize));
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
