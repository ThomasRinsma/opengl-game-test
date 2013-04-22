#include "scene.ih"

void Scene::add(string const name, Portal *portal)
{
	d_portals[name] = unique_ptr<Portal>(portal);
}