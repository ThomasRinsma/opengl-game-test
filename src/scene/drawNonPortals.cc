#include "scene.ih"

void Scene::drawNonPortals(glm::mat4 const &viewMat, glm::mat4 const &projMat)
{
	// Draw all objects that aren't portals
	for (auto &pair : d_drawableEntities)
	{
		updateLightData(*pair.second);
		pair.second->draw(viewMat, projMat);
	}
}