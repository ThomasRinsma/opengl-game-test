#include "player.ih"

void Player::setProjMat(float fov, float ratio, float near, float far)
{
	d_projMat = glm::perspective(fov, ratio, near, far);
}