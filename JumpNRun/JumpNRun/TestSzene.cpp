#include "TestSzene.h"

TestSzene::TestSzene(std::string Name, SceneHandler * sceneHandler) : Scene(Name, sceneHandler)
{
	setupResources();
}

TestSzene::~TestSzene()
{
}

bool TestSzene::setupResources()
{
	movePlayer = new Button(IntRect(0, 0, 100, 100), [&] {this->machShit();});
	movePlayer->buttonShape.setFillColor(Color::Blue);

	return true;
}

void TestSzene::handleInput(RenderWindow& window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		movePlayer->checkMouseButtonCollision(window);
	}
}

void TestSzene::update()
{
	
}

void TestSzene::render(RenderWindow& window)
{
	window.draw(movePlayer->buttonShape);
}

void TestSzene::machShit()
{
	movePlayer->buttonShape.setFillColor(Color::Red);
	sceneHandler->addScene(new OverlayTestSzene("Overlay", sceneHandler), true);
}
