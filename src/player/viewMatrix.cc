#include "player.ih"

glm::mat4 const Player::viewMatrix() const
{
	glm::vec3 direction(
		cos(pitch()) * sin(yaw()),
		sin(pitch()),
		cos(pitch()) * cos(yaw())
	);

	glm::vec3 right(
		sin(yaw() - M_PI/2.0f),
		0,
		cos(yaw() - M_PI/2.0f)
	);

	glm::vec3 up = glm::cross(right, direction);

	return glm::lookAt(d_position, d_position + direction, up);
}