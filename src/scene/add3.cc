#include "scene.ih"

void Scene::add(Light *light)
{
	d_lights.push_back(light);
}