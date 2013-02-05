#include "scene.ih"

Scene::~Scene()
{
	for (SceneObject *sceneObject : d_sceneObjects)
		delete sceneObject;
}