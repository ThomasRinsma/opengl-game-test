#include "scene.ih"

void Scene::add(string const name, Light *light)
{
	d_lights[name] = unique_ptr<Light>(light);
}