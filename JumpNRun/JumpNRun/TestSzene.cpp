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
	toggleOverlay = new Button(IntRect(0, 0, 100, 100), "Textures/button_play.png", [&] {this->toggleOverlayAction(); });

	toggleOverlay->loadTextures();
	toggleOverlay->unloadTextures();
	return toggleOverlay->loadTextures();
}

void TestSzene::handleInput(RenderWindow& window, Event windowEvent)
{
	switch (windowEvent.type)
	{
	case Event::MouseButtonPressed:
		if (windowEvent.mouseButton.button == Mouse::Right)
		{
			toggleOverlay->checkMouseButtonCollision(window);
		}
		break;
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
