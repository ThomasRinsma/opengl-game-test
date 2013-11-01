#include "scene.ih"

void Scene::draw()
{
	// Start the recursion
	size_t maxRecursionLevel = 5;
	drawRecursivePortals(d_player.viewMat(), d_player.projMat(), maxRecursionLevel);
}