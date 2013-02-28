#include "scene.ih"

Scene::~Scene()
{
	for (DrawableEntity *drawableEntity : d_drawableEntities)
		delete drawableEntity;

	for (Portal *portal : d_portals)
		delete portal;
}