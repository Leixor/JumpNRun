#include "standardInclude.h"

OverlayTestSzene::OverlayTestSzene(std::string Name, SceneHandler * sceneHandler): Scene(Name, sceneHandler)
{
	setupResources();
}

OverlayTestSzene::~OverlayTestSzene()
{
}

bool OverlayTestSzene::setupResources()
{
	OverlayButton = new Button(IntRect(0, 0, 50, 100), "Textures/button_play.png", [&] {this->overlayButtonAction(); });
	return OverlayButton->loadTextures();
}

void OverlayTestSzene::handleInput(RenderWindow & window, Event windowEvent)
{
	switch(windowEvent.type)
	{
	case Event::MouseButtonPressed:
		if (windowEvent.mouseButton.button == Mouse::Left)
		{
			OverlayButton->checkMouseButtonCollision(window);

		}
		break;
	case Event::KeyPressed:
		if (windowEvent.key.code == Keyboard::A)
		{
			sceneHandler->setSceneVisibility("Test", true);
		}
		break;
	}
}

void OverlayTestSzene::update()
{
}

void OverlayTestSzene::render(RenderWindow & window)
{
	window.draw(*OverlayButton);
}

void OverlayTestSzene::overlayButtonAction()
{
	int i = 0;
	sceneHandler->setSceneVisibility("Test", false);
}
