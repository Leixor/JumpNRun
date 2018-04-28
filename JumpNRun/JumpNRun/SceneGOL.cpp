#include "SceneGOL.h"

SceneGOL::SceneGOL(SceneHandler& sceneHandler, RenderWindow* window)
	: Scene(sceneHandler, window)
{
	this->setupResources();
}

SceneGOL::~SceneGOL()
{
}

bool SceneGOL::setupResources()
{
	// Lese die Config ein
	configHelper = new ConfigHelper("test.txt");

	// Setze updateRate
	updateRate = stoi(configHelper->get("GOL", "UpdateRate"));

	// Standard Gamestate angeben
	gameState = GOLSETUPSIZE;

	// Font laden
	font = new Font();
	this->font->loadFromFile("Textures/cool.ttf");

	// StandardgridSize definieren
	gridSize = stoi(configHelper->get("GOL", "GridSize"));
	sizeText = to_string(gridSize) + " x " + to_string(gridSize);
	cellSize = window->getSize().x / (float)gridSize;

	// UI adden

	background = new ShapeRectangle(float(windowDef::get().windowSizeX), float(windowDef::get().windowSizeY), Color::Color(stoul(configHelper->get("GOL", "BackgroundColor"),nullptr,16)));
	addResource("+size", new Button([&] {plusGridSize(); }, new ShapeSprite("Textures/plus.png", .1f)));
	addResource("-size", new Button([&] {minusGridSize(); }, new ShapeSprite("Textures/minus.png", .1f)));
	gridSizeText = addObject("GridSizeText", new ShapeRectangle(Vector2f(200, 100)));
	gridSizeText->shapeVisible = NONE;
	gridSizeText->addText(new ObjectText(sizeText, *font));
	gridSizeText->objectText->setCharacterSize(40);
	gridSizeText->objectText->setFillColor(Color::Black);
	alignTo(*objects.get("-size")->objectShape, *background, BOTTOM | LEFT);
	objects.get("-size")->objectShape->move(Vector2f(20, -20));
	alignNextTo(*gridSizeText->objectText, *objects.get("-size")->objectShape, RIGHT);
	alignNextTo(*objects.get("+size")->objectShape, *gridSizeText->objectText, RIGHT);

	generationText = addObject("generationText", new ShapeRectangle(Vector2f(200, 100)));
	generationText->shapeVisible = NONE;
	generationText->addText(new ObjectText("Generation: " + to_string(generation), *font));
	generationText->objectText->setCharacterSize(40);
	generationText->objectText->setFillColor(Color::Black);

	gpsText = addObject("generationText", new ShapeRectangle(Vector2f(200, 100)));
	gpsText->shapeVisible = NONE;
	gpsText->addText(new ObjectText("Generation/Sekunde: " + to_string(1000/updateRate), *font));
	gpsText->objectText->setCharacterSize(40);
	gpsText->objectText->setFillColor(Color::Black);

	alignNextTo(*generationText->objectText, *objects.get("+size")->objectShape, RIGHT, 100);
	alignNextTo(*gpsText->objectText, *generationText->objectText, RIGHT, 50);

	rect = new ShapeRectangle(Vector2f(cellSize, cellSize), Color::Color(stoul(configHelper->get("GOL", "CellColor"), nullptr, 16)));
	sprit = new ShapeSprite("Textures/plus.png", Vector2f(cellSize, cellSize));

	proto = sprit;

	return false;
}

void SceneGOL::update()
{
	Scene::update();

	switch (gameState)
	{
	case eGOLStates::GOLSETUPFIELD:
		break;
	case eGOLStates::GOLINGAME:
		runGameSimulation();
		generation++;
		break;
	case eGOLStates::GOLPAUSED:
		break;
	}
	generationText->objectText->setString("Generation: " + to_string(generation));
	alignNextTo(*gpsText->objectText, *generationText->objectText, RIGHT, 50);
}

void SceneGOL::handleInputs(RenderWindow & window)
{
	Scene::handleInputs(window);
	
	//Falls das Game noch im Setup ist soll an den Stellen wo der Spieler hinklickt eine Zelle zum Leben erweckt werden falls dort noch keine lebende ist
	if (gameState & GOLSETUPFIELD || gameState & GOLPAUSED)
	{
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			Vector2i mousePos = Mouse::getPosition(window);
			FloatRect Cell(0, 0, cellSize, cellSize);
			for (int i = 0; i < gridSize / (16 / 9); i++)
			{
				for (int j = 0; j < gridSize; j++)
				{
					Cell.left = cellSize * i;
					Cell.top = cellSize * j;
					if (Cell.contains(Vector2f(float(mousePos.x), float(mousePos.y))))
					{
						gameField[j][i] = true;
					}
				}
			}
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::C))
	{
		if (gameState & GOLSETUPSIZE)
		{
			setupField();
			gameState = GOLSETUPFIELD;	
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::A))
	{
		if (gameState & GOLSETUPFIELD || gameState & GOLPAUSED)
		{
			gameState = GOLINGAME;
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::P))
	{
		if (gameState & GOLINGAME)
		{
			gameState = GOLPAUSED;
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::R))
	{
		gameField.clear();
		generation = 0; 
		setupField();
		gameState = GOLSETUPFIELD;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::N))
	{
		generation = 0;
		gameState = GOLSETUPSIZE;
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
		this->getSceneHandler().setTopScene("SnakeGame");
		this->getSceneHandler().getSceneByName("SnakeGame")->setSceneVisibility(ALL);
		this->setSceneVisibility(NONE);
	}
}

void SceneGOL::handleEvents(RenderWindow & window, Event& windowEvent)
{
	Scene::handleEvents(window, windowEvent);
	if (windowEvent.type == Event::KeyPressed) 
	{
		if (Keyboard::isKeyPressed(Keyboard::Key::Up)) 
		{
			if(updateRate > 10)
				updateRate -= 10;
			gpsText->objectText->setString("Generation/Sekunde: " + to_string(1000 / updateRate));
		}
			
		if (Keyboard::isKeyPressed(Keyboard::Key::Down)) 
		{
			updateRate += 10;
			gpsText->objectText->setString("Generation/Sekunde: " + to_string(1000 / updateRate));
		}
	}
}

void SceneGOL::render(RenderWindow & window, RenderStates& shades, float timeTillUpdate)
{
	background->draw(window, shades);
	// Das richtige Gamefield anzeigen
	if (gameField.size() != 0)
	{
		for (int i = 0; i < gridSize / (16 / 9); i++) 
		{
			for (int j = 0; j < gridSize; j++) {
				if (this->gameField[i][j] == 1) 
				{
					this->proto->setPosition(Vector2f(j*cellSize, i*cellSize));
					this->proto->draw(window, shades);
				}
			}
		}
	}

	Scene::render(window, shades, timeTillUpdate);
}

void SceneGOL::plusGridSize()
{
	if (gameState & GOLSETUPSIZE)
	{
		if (!Keyboard::isKeyPressed(Keyboard::Key::LControl))
			gridSize++;
		else
			gridSize += 10;

		sizeText = to_string(gridSize) + " x " + to_string(gridSize);
		gridSizeText->objectText->setString(sizeText);
		cellSize = (float)window->getSize().x / (float)gridSize;

		proto->setSize(Vector2f(cellSize, cellSize));
	}
}

void SceneGOL::minusGridSize()
{
	if (gameState & GOLSETUPSIZE)
	{
		if (!Keyboard::isKeyPressed(Keyboard::Key::LControl))
			gridSize--;
		else
			gridSize -= 10;

		sizeText = to_string(gridSize) + " x " + to_string(gridSize);
		gridSizeText->objectText->setString(sizeText);

		cellSize = (float)window->getSize().x / (float)gridSize;

		proto->setSize(Vector2f(cellSize, cellSize));
	}
}

void SceneGOL::setupField()
{
	gameField.clear();

	for (int i = 0; i < gridSize / (16 / 9); i++) 
	{
		gameField.push_back(vector<char>());
		for (int j = 0; j < gridSize; j++) 
		{
			gameField[i].push_back(false);
		}
	}
}

void SceneGOL::runGameSimulation()
{
	vector<vector<char>> oldGen;
	oldGen = gameField; 

	for (int a = 0; a < gridSize - 1; a++)
	{
		for (int b = 0; b < gridSize - 1; b++)
		{
			int alive = 0;
			for (int c = -1; c < 2; c++)
			{
				for (int d = -1; d < 2; d++)
				{
					if (!((a == 0 && c == -1) || (b == 0 && d == -1)))
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
