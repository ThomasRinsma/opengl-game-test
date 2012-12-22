#include "player.ih"

void Player::setRelativeVelocity(glm::vec3 relVelocity)
{
	// Use yaw and relative velocity to calculate absolute velocity
	// x = lateral, y = vertical, z = longitudinal
	
	vec3 normVelocity = length(relVelocity) > 0 ? normalize(relVelocity) : relVelocity;

	d_velocity.x = normVelocity.z * cos(M_PI/2.0f - d_yaw);
	d_velocity.z = normVelocity.z * cos(d_yaw);

	d_velocity.x += -normVelocity.x * sin(M_PI/2.0f - d_yaw);
	d_velocity.z += normVelocity.x * sin(d_yaw);
}