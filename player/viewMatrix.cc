#include "player.ih"

glm::mat4 const Player::viewMatrix() const
{
	glm::vec3 direction(
		cos(d_pitch) * sin(d_yaw),
		sin(d_pitch),
		cos(d_pitch) * cos(d_yaw)
	);

	glm::vec3 right(
		sin(d_yaw - M_PI/2.0f),
		0,
		cos(d_yaw - M_PI/2.0f)
	);

	glm::vec3 up = glm::cross(right, direction);

	return glm::lookAt(d_position, d_position + direction, up);
}