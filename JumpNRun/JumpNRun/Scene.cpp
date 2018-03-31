#include "Scene.h"



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

