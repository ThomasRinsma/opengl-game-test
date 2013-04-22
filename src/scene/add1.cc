#include "scene.ih"

void Scene::add(string const name, DrawableEntity *object)
{
	// TODO: sort based on shader program, texture, etc? Maybe some sort of tree
	d_drawableEntities[name] = unique_ptr<DrawableEntity>(object);
}