#include "player.ih"

void Player::update(float deltaTime)
{
	float latMovement = d_controller.moveRight() * 1.0f - d_controller.moveLeft() * 1.0f;
	float longMovement = d_controller.moveForward() * 1.0f - d_controller.moveBack() * 1.0f;
	float verticalMovement = d_controller.moveUp() * 1.0f - d_controller.moveDown() * 1.0f;

	// Mouse stuff
	glm::vec2 mousePosDelta = d_controller.mouseOffset();
	d_yaw -= mousePosDelta.x * s_mouseSpeed;
	d_pitch -= mousePosDelta.y * s_mouseSpeed;

	if(d_yaw > M_PI) d_yaw -= 2.0f * M_PI;
	if(d_yaw < -M_PI) d_yaw += 2.0f * M_PI;

	if(d_pitch > M_PI/2.0f) d_pitch = M_PI/2.0f;
	if(d_pitch < -M_PI/2.0f) d_pitch = -M_PI/2.0f;

	setRelativeVelocity(glm::vec3(latMovement, verticalMovement, longMovement));
	integratePosition(deltaTime * s_moveSpeed);
}