#include "player.ih"

void Player::update(float deltaTime, Controller *controller)
{
	float latMovement = controller->moveRight() * 1.0f - controller->moveLeft() * 1.0f;
	float longMovement = controller->moveForward() * 1.0f - controller->moveBack() * 1.0f;
	float verticalMovement = controller->moveUp() * 1.0f - controller->moveDown() * 1.0f;

	// Mouse stuff
	glm::vec2 mousePosDelta = controller->mouseOffset();
	d_yaw -= mousePosDelta.x * s_mouseSpeed;
	d_pitch -= mousePosDelta.y * s_mouseSpeed;

	if(d_yaw > M_PI) d_yaw -= 2.0f * M_PI;
	if(d_yaw < -M_PI) d_yaw += 2.0f * M_PI;

	if(d_pitch > M_PI/2.0f) d_pitch = M_PI/2.0f;
	if(d_pitch < -M_PI/2.0f) d_pitch = -M_PI/2.0f;

	setRelativeVelocity(glm::vec3(latMovement, verticalMovement, longMovement));
	integratePosition(deltaTime * s_moveSpeed);
}