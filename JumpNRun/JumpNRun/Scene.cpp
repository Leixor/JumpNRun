#include "standardInclude.h"

Scene::Scene(string Name, SceneHandler * sceneHandler, RenderWindow* window)
	: sceneName(Name), sceneHandler(sceneHandler), window(window)
{

}

Scene::~Scene()
{
}

void Scene::handleInput(RenderWindow & window, Event windowEvent)
{
	for (unsigned int i = 0; i < this->objects.size(); i++)
	{
		objects.get(i)->handleInput(window, windowEvent);
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
string Scene::getSceneName() const
{
	return this->sceneName;
}

SceneHandler * Scene::getSceneHandler() const
{
	return this->sceneHandler;
}

