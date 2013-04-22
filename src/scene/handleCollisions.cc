#include "scene.ih"

void Scene::handleCollisions()
{
	for (auto &pair : d_portals)
	{
		Portal &portal = *pair.second;

		if (glm::distance(d_player.position(), portal.position()) < s_teleportThreshold)
		{
			glm::vec3 relPos = portal.position() - d_player.position();
			d_player.setPosition(portal.destination()->position() + relPos);
			break;
		}
	}
}