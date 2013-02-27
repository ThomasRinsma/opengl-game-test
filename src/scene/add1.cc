#include "scene.ih"

void Scene::add(DrawableEntity *object)
{
	// TODO: sort based on shader program, texture, etc? Maybe some sort of tree
	d_drawableEntities.push_back(object);
}