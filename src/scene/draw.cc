#include "scene.ih"

void Scene::draw()
{
	// Start the recursion
	drawRecursivePortals(d_player.viewMat(), d_player.projMat(), 0);
}