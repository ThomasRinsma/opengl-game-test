#include "player.ih"

void Player::updateImpl(float deltaTime)
{
	float latMovement = d_controller.moveRight() * 1.0f - d_controller.moveLeft() * 1.0f;
	float longMovement = d_controller.moveForward() * 1.0f - d_controller.moveBack() * 1.0f;
	float verticalMovement = d_controller.moveUp() * 1.0f - d_controller.moveDown() * 1.0f;

	// Mouse stuff
	glm::vec2 mousePosDelta = d_controller.mouseOffset();
	setYaw(yaw() - mousePosDelta.x * s_mouseSpeed);
	setPitch(pitch() - mousePosDelta.y * s_mouseSpeed);

	if(yaw() > M_PI) setYaw(yaw() - 2.0f * M_PI);
	if(yaw() < -M_PI) setYaw(yaw() + 2.0f * M_PI);

	if(pitch() > M_PI/2.0f) setPitch(M_PI/2.0f);
	if(pitch() < -M_PI/2.0f) setPitch(-M_PI/2.0f);

	setRelativeVelocity(glm::vec3(latMovement, verticalMovement, longMovement));
	integratePosition(deltaTime * s_moveSpeed);
}