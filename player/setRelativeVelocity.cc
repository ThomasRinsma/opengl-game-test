#include "player.ih"

void Player::setRelativeVelocity(glm::vec3 relVelocity)
{
	glm::vec3 normVel = glm::length(relVelocity) > 0 ? glm::normalize(relVelocity) : relVelocity;
	
	d_velocity.x = normVel.z * sin(d_yaw) * cos(d_pitch) - normVel.x * cos(d_yaw);
	d_velocity.z = normVel.z * cos(d_yaw) * cos(d_pitch) + normVel.x * sin(d_yaw);
	d_velocity.y = normVel.z * sin(d_pitch) + normVel.y;
}