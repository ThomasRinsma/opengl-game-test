#include "scene.ih"

void Scene::update(float deltaTime)
{
	for (DrawableEntity *drawableEntity : d_drawableEntities)
		drawableEntity->update(deltaTime);

	for (Portal *portal : d_portals)
		portal->update(deltaTime);
}