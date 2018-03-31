#include "standardInclude.h"

TestSzene::TestSzene(std::string Name, SceneHandler * sceneHandler) : Scene(Name, sceneHandler)
{
	setupResources();
}

TestSzene::~TestSzene()
{
}

bool TestSzene::setupResources()
{
	toggleOverlay = new Button(IntRect(0, 0, 100, 100), [&] {this->toggleOverlayAction();});
	toggleOverlay->setFillColor(Color::Blue);

	return true;
}

void TestSzene::handleInput(RenderWindow& window, Event windowEvent)
{
	if (Mouse::isButtonPressed(Mouse::Left)) {
		toggleOverlay->checkMouseButtonCollision(window);
	}
}

void TestSzene::update()
{
	
}

void TestSzene::render(RenderWindow& window)
{
	window.draw(*toggleOverlay);
}

void TestSzene::toggleOverlayAction()
{
	toggleOverlay->setFillColor(Color::Red);
	sceneHandler->addScene(new OverlayTestSzene("Overlay", sceneHandler), true);
}
