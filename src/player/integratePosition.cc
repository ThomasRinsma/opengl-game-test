#include "player.ih"

void Player::integratePosition(float deltaTime)
{
	d_position += d_velocity * deltaTime;
}