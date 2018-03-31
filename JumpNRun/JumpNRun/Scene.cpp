#include "standardInclude.h"

Scene::Scene(std::string Name, SceneHandler * sceneHandler) : sceneName(Name), sceneHandler(sceneHandler)
{

}

Scene::~Scene()
{
}

string Scene::getSceneName() const
{
	return this->sceneName;
}

SceneHandler * Scene::getSceneHandler() const
{
	return this->sceneHandler;
}

