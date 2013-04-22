#include "scene.ih"

void Scene::update(float deltaTime)
{
	for (auto &pair : d_drawableEntities)
		pair.second->update(deltaTime);

	for (auto &pair : d_portals)
		pair.second->update(deltaTime);

	handleCollisions();
}