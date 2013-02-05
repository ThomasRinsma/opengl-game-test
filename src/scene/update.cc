#include "scene.ih"

void Scene::update(float deltaTime)
{
	for (SceneObject *sceneObject : d_sceneObjects)
		sceneObject->update(deltaTime);

	for (Portal *portal : d_portals)
		portal->update(deltaTime);
}