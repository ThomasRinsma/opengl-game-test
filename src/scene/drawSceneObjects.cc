#include "scene.ih"

void Scene::drawSceneObjects(glm::mat4 const &viewMat, glm::mat4 const &projMat)
{
	// Draw all scene objects
	for (SceneObject *sceneObject : d_sceneObjects)
		sceneObject->draw(viewMat, projMat);
}