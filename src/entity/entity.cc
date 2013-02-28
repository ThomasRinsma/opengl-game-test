#include "entity.ih"

Entity::Entity(glm::vec3 position, glm::vec3 scale)
:
	d_velocity(0.0f),
	d_position(position),
	d_scale(scale),
	d_orientation(1.0f, 0.0f, 0.0f, 0.0f)
{
	updateModelMat();
}