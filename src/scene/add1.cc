#include "scene.ih"

void Scene::add(string const name, SceneObject *object)
{
	// TODO: sort based on shader program, texture, etc? Maybe some sort of tree
	d_sceneObjects[name] = unique_ptr<SceneObject>(object);
}