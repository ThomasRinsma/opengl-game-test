#include "player.ih"

void Player::updateImpl(float deltaTime)
{
	float latMovement = d_controller.moveRight() * 1.0f - d_controller.moveLeft() * 1.0f;
	float longMovement = d_controller.moveBack() * 1.0f - d_controller.moveForward() * 1.0f;
	float verticalMovement = d_controller.moveUp() * 1.0f - d_controller.moveDown() * 1.0f;

	glm::vec2 mousePosDelta = d_controller.mouseOffset();

	d_yaw -= mousePosDelta.x * s_mouseSpeed; 
	d_pitch -= mousePosDelta.y * s_mouseSpeed;

	if (d_yaw > M_PI)
		d_yaw -= 2.0f * M_PI;

	if (d_yaw < -M_PI)
		d_yaw += 2.0f * M_PI;

	if(d_pitch > M_PI/2.0f)
		d_pitch = M_PI/2.0f;

	if(d_pitch < -M_PI/2.0f)
		d_pitch = -M_PI/2.0f;


	resetOrientation();
	addOrientation(glm::vec3(0.0f, 1.0f, 0.0f), d_yaw, true);
	addOrientation(glm::vec3(1.0f, 0.0f, 0.0f), d_pitch, false);

	// Sets d_velocity according to movement keys
	// lat and long movement are relative to d_orientation, vertical movement is not.
	// normalize them all three to get a semi-constant speed
	glm::vec3 relVel = glm::vec3(latMovement, verticalMovement, longMovement);
	glm::vec3 normVel = glm::length(relVel) > 0 ? glm::normalize(relVel) : relVel;
	d_velocity = glm::vec3(normVel.x, 0.0f, normVel.z) * glm::conjugate(d_orientation);
	d_velocity += glm::vec3(0.0f, verticalMovement, 0.0f);

	// Integrate velocity to a new position using time
	integratePosition(deltaTime * s_moveSpeed);
}