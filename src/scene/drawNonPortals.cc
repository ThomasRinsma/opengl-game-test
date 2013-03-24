#include "scene.ih"

void Scene::drawNonPortals(glm::mat4 const &viewMat, glm::mat4 const &projMat)
{
	// Draw all objects that aren't portals
	for (DrawableEntity *drawableEntity : d_drawableEntities)
	{
		updateLightData(drawableEntity);
		drawableEntity->draw(viewMat, projMat);
	}
}