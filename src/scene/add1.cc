#include "scene.ih"

void Scene::add(SceneObject *object)
{
	// TODO: sort based on shader program, texture, etc? Maybe some sort of tree
	d_sceneObjects.push_back(object);
}