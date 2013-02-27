#include "player.ih"

void Player::updateProjMat()
{
	d_projMat = glm::perspective(d_fov, d_screenRatio, d_zNear, d_zFar);
}