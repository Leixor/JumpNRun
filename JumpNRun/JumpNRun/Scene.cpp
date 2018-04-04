#include "standardInclude.h"

Scene::Scene(string Name, SceneHandler * sceneHandler, RenderWindow* window, int visible)
	: sceneName(Name), sceneHandler(sceneHandler), window(window), visible(visible)
{

}

Scene::~Scene()
{
}

void Scene::handleInputs(RenderWindow & window)
{
	for (int i = this->objects.size() - 1; i >= 0; i--)
	{
		objects.get(i)->handleInputs(window);
	}
}

void Scene::handleEvents(RenderWindow & window, Event windowEvent)
{
	for (int i = this->objects.size() - 1; i >= 0; i--)
	{
		if(objects.get(i)->handleEvents(window, windowEvent))
			break;
	}
}

void Scene::update()
{
	for (unsigned int i = 0; i < this->objects.size(); i++)
	{
		objects.get(i)->update();
	}
}

void Scene::render(RenderWindow & window, RenderStates shades)
{
	for (unsigned int i = 0; i < this->objects.size(); i++)
	{
		objects.get(i)->draw(window, shades);
	}
}
string Scene::getSceneName()
{
	return this->sceneName;
}

SceneHandler * Scene::getSceneHandler() const
{
	return this->sceneHandler;
}

