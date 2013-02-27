#include "scene.ih"

Scene::~Scene()
{
	for (DrawableEntity *drawableEntity : d_drawableEntities)
		delete drawableEntity;
}