#include "standardInclude.h"

SceneGOL::SceneGOL(string name, SceneHandler * sceneHandler, RenderWindow* window) : Scene(name, sceneHandler, window)
{
	this->setupResources();
}

SceneGOL::~SceneGOL()
{
}

bool SceneGOL::setupResources()
{
	// Lese die Config ein
	conf = new ConfigHelper("test.txt");

	// Setze updateRate
	updateRate = stoi(conf->get("GOL", "UpdateRate"));

	// Standard Gamestate angeben
	gameState = SETUPSIZE;

	// Font laden
	font = new Font();
	this->font->loadFromFile("Textures/cool.ttf");

	// StandardgridSize definieren
	gridSize = stoi(conf->get("GOL", "GridSize"));
	sizeText = to_string(gridSize) + " x " + to_string(gridSize);
	cellSize = window->getSize().x / (float)gridSize;

	// UI adden

	background = new ShapeRectangle(windowDef::get().windowSizeX, windowDef::get().windowSizeY, Color::Color(stoul(conf->get("GOL", "BackgroundColor"),nullptr,16)));
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

	gpsText = addObject("generationText", new ShapeRectangle(Vector2f(200, 100)));
	gpsText->shapeVisible = NONE;
	gpsText->addText("Generation/Sekunde: " + to_string(1000/updateRate), *font);
	gpsText->setTextSize(40);
	gpsText->objectText->setFillColor(Color::Black);

	alignNextTo(*generationText->objectText, *objects.get("+size")->shape, RIGHT, 100);
	alignNextTo(*gpsText->objectText, *generationText->objectText, RIGHT, 50);

	rect = new ShapeRectangle(Vector2f(cellSize, cellSize), Color::Color(stoul(conf->get("GOL", "CellColor"), nullptr, 16)));
	sprit = new ShapeSprite("Textures/plus.png", Vector2f(cellSize, cellSize));

	proto = sprit;

	return false;
}

void SceneGOL::update()
{
	Scene::update();

	if (this->getUpdateSync())
	{
		switch (gameState)
		{
		case SETUPFIELD:
			break;
		case INGAME:
			runGameSimulation();
			generation++;
			break;
		case PAUSED:
			break;
		}
		generationText->setText("Generation: " + to_string(generation));
		alignNextTo(*gpsText->objectText, *generationText->objectText, RIGHT, 50);
	}
}

void SceneGOL::handleInputs(RenderWindow & window)
{
	Scene::handleInputs(window);

	//Falls das Game noch im Setup ist soll an den Stellen wo der Spieler hinklickt eine Zelle zum Leben erweckt werden falls dort noch keine lebende ist
	if (gameState & SETUPFIELD || gameState & PAUSED)
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
		if (gameState & SETUPSIZE)
		{
			setupField();
			gameState = SETUPFIELD;	
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::A))
	{
		if (gameState & SETUPFIELD || gameState & PAUSED)
		{
			gameState = INGAME;
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::P))
	{
		if (gameState & INGAME)
		{
			gameState = PAUSED;
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::R))
	{
		gameField.clear();
		generation = 0; 
		setupField();
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

void SceneGOL::handleEvents(RenderWindow & window, Event windowEvent)
{
	Scene::handleEvents(window, windowEvent);
	if (windowEvent.type == Event::KeyPressed) 
	{
		if (Keyboard::isKeyPressed(Keyboard::Key::Up)) 
		{
			if(updateRate > 10)
				updateRate -= 10;
			gpsText->setText("Generation/Sekunde: " + to_string(1000 / updateRate));
		}
			
		if (Keyboard::isKeyPressed(Keyboard::Key::Down)) 
		{
			updateRate += 10;
			gpsText->setText("Generation/Sekunde: " + to_string(1000 / updateRate));
		}
			
	}
}

void SceneGOL::render(RenderWindow & window, RenderStates shades, float timeTillUpdate)
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
	if (gameState & SETUPSIZE)
	{
		if (!Keyboard::isKeyPressed(Keyboard::Key::LControl))
			gridSize++;
		else
			gridSize += 10;

		sizeText = to_string(gridSize) + " x " + to_string(gridSize);
		gridSizeText->setText(sizeText);
		cellSize = (float)window->getSize().x / (float)gridSize;

		proto->setSize(Vector2f(cellSize, cellSize));
	}
}

void SceneGOL::minusGridSize()
{
	if (gameState & SETUPSIZE)
	{
		if (!Keyboard::isKeyPressed(Keyboard::Key::LControl))
			gridSize--;
		else
			gridSize -= 10;

		sizeText = to_string(gridSize) + " x " + to_string(gridSize);
		gridSizeText->setText(sizeText);

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
