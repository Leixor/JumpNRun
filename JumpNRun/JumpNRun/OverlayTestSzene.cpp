#include "OverlayTestSzene.h"




OverlayTestSzene::OverlayTestSzene(std::string Name, SceneHandler * sceneHandler): Scene(Name, sceneHandler)
{
	setupResources();
}

OverlayTestSzene::~OverlayTestSzene()
{
}

bool OverlayTestSzene::setupResources()
{
	OverlayButton = new Button(IntRect(0, 0, 50, 100), [&] {this->machShit(); });
	OverlayButton->buttonShape.setFillColor(Color::Green);
	return true;
}

void OverlayTestSzene::handleInput(RenderWindow & window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		OverlayButton->checkMouseButtonCollision(window);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		sceneHandler->setSceneVisibility("Test", true);
	}
}

void OverlayTestSzene::update()
{
}

void OverlayTestSzene::render(RenderWindow & window)
{
	window.draw(OverlayButton->buttonShape);
}

void OverlayTestSzene::machShit()
{
	int i = 0;
	sceneHandler->setSceneVisibility("Test", false);
}
