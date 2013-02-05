#include "player.ih"

Player::Player(Controller &controller)
:
	d_controller(controller),
	d_projMat(glm::mat4(1.0f))
{}