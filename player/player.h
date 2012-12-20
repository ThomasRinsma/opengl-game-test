#ifndef INCLUDED_PLAYER_
#define INCLUDED_PLAYER_

#include <glm/glm.hpp> // for glm::vec3 and glm::mat4

class Player
{
	glm::vec3 d_position;
	glm::vec3 d_velocity;
	float d_pitch; // up and down
	float d_yaw; // left and right

    public:
        glm::vec3 const &position() const;
        void setPosition(glm::vec3 position);

        glm::vec3 const &velocity() const;
        void setVelocity(glm::vec3 velocity);

        void integratePosition(float deltaTime);

        glm::mat4 const viewMatrix() const;

    private:
};
        
#endif
