#include "standardInclude.h"

SceneStartMenu::SceneStartMenu(string name, SceneHandler * sceneHandler)
	: Scene(name, sceneHandler)
{
	this->setupResources();
}

SceneStartMenu::~SceneStartMenu()
{
}

bool SceneStartMenu::setupResources()
{
	this->vButton.insert(pair<String, Button>("Start", Button(IntRect(100, 100, 100, 100), "Textures/button_start_png", [&] {this->buttonStartAction(); })));

	//Schaut, ob das Laden der einzelnen Texturen erfolgreich war
	for (unsigned int i = 0; i < this->vButton.size(); i++)
	{
		this->vButton.at(1);
		/*if (!this->vButton.at(i).loadTextures())
			return false;*/
	}

	return true;
}

void SceneStartMenu::handleInput(RenderWindow & window, Event windowEvent)
{
	for (unsigned int i = 0; i < this->vButton.size(); i++)
	{
		this->vButton.at(i).checkMouseButtonCollision(window);
	}
}

void SceneStartMenu::update()
{
}

void SceneStartMenu::render(RenderWindow & window)
{
	for (unsigned int i = 0; i < this->vButton.size(); i++)
	{
		window.draw(this->vButton.at(i));
	}
}

void SceneStartMenu::buttonStartAction()
{
}
