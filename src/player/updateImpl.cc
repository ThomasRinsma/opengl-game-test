#include "player.ih"

void Player::updateImpl(float deltaTime)
{
	float latMovement = d_controller.moveRight() * 1.0f - d_controller.moveLeft() * 1.0f;
	float longMovement = d_controller.moveBack() * 1.0f - d_controller.moveForward() * 1.0f;
	float verticalMovement = d_controller.moveUp() * 1.0f - d_controller.moveDown() * 1.0f;

	glm::vec2 mousePosDelta = d_controller.mouseOffset();

	// Yaw in world space (we don't want accidential rolling)
	addOrientation(glm::vec3(0.0f, 1.0f, 0.0f), -mousePosDelta.x * s_mouseSpeed, true);

	// Pitch in model space (relative to our yaw)
	addOrientation(glm::vec3(1.0f, 0.0f, 0.0f), -mousePosDelta.y * s_mouseSpeed, false);

	// Somehow roll flips to 180 and pitch += 180 when rotating over a quarter of a turn in yaw.
	// (TODO: why? Seems like something to do with how quaternions work)
	// Fix it by adding pitch+roll to get the actual pitch.
	float actualPitch = glm::pitch(d_orientation) + glm::roll(d_orientation);

	// When the actual pitch is outside of [-90, 90], revert the added orientation
	// to prevent the camera from going upside down
	if(actualPitch > 90.0f or actualPitch < -90.0f)
		addOrientation(glm::vec3(1.0f, 0.0f, 0.0f), mousePosDelta.y * s_mouseSpeed, false);


	// Sets d_velocity according to movement keys
	// lat and long movement are relative to d_orientation, vertical movement is not.
	// normalize them all three to get a semi-constant speed
	glm::vec3 relVel = glm::vec3(latMovement, verticalMovement, longMovement);
	glm::vec3 normVel = glm::length(relVel) > 0 ? glm::normalize(relVel) : relVel;
	d_velocity = glm::vec3(relVel.x, 0.0f, relVel.z) * glm::conjugate(d_orientation);
	d_velocity += glm::vec3(0.0f, verticalMovement, 0.0f);

	// Integrate velocity to a new position using time
	integratePosition(deltaTime * s_moveSpeed);
}