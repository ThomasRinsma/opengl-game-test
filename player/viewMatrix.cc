#include "player.ih"

#define degrees(X)	static_cast<float>((X) / M_PI * 180.0f)

mat4 const Player::viewMatrix() const
{
	vec3 direction(
		cos(degrees(d_pitch)) * sin(degrees(d_yaw)),
		sin(degrees(d_pitch)),
		cos(degrees(d_pitch)) * cos(degrees(d_yaw))
	);

	return lookAt(d_position, d_position + direction, vec3(0.0f, 1.0f, 0.0f));
}