#include "player.ih"

void Player::setRelativeVelocity(glm::vec3 const &relVelocity)
{
	glm::vec3 normVel = glm::length(relVelocity) > 0 ? glm::normalize(relVelocity) : relVelocity;
	
	d_velocity.x = normVel.z * sin(yaw()) * cos(pitch()) - normVel.x * cos(yaw());
	d_velocity.z = normVel.z * cos(yaw()) * cos(pitch()) + normVel.x * sin(yaw());
	d_velocity.y = normVel.z * sin(pitch()) + normVel.y;
}