#include "player.ih"

mat4 const Player::viewMatrix() const
{
	mat4 viewMat(1.0f);

	viewMat = translate(viewMat, -d_position);

	// TODO: orientation

	return viewMat;
}