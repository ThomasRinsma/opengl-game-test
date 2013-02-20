#include "player.ih"

glm::mat4 const Player::viewMat() const
{
	glm::mat4 rot = glm::mat4_cast(glm::conjugate(d_orientation));
	glm::mat4 pos = glm::translate(glm::mat4(1.0f), -d_position);

	return rot * pos;
}