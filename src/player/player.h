#ifndef INCLUDED_PLAYER_
#define INCLUDED_PLAYER_

#include <glm/glm.hpp> // for glm::vec3 and glm::mat4
#include "../controller/controller.h"

class Player
{
    static constexpr float s_mouseSpeed = 0.001f * M_PI; // radians per pixel
    static constexpr float s_moveSpeed = 2.0f; // units per second

	glm::vec3 d_position;
	glm::vec3 d_velocity; // absolute
	float d_pitch = 0; // up and down
	float d_yaw = 0; // left and right

    public:
        glm::vec3 const &position() const;
        glm::vec3 const &velocity() const;

        //float pitch() const;
        //float yaw() const;

        //void setPitch(float pitch);
        //void setYaw(float yaw);
        

        void update(float deltaTime, Controller *controller);
        
        

        glm::mat4 const viewMatrix() const;

    private:
        void integratePosition(float deltaTime);
        void setRelativeVelocity(glm::vec3 velocity);
};

inline glm::vec3 const &Player::position() const
{
    return d_position;
}

inline glm::vec3 const &Player::velocity() const
{
    return d_velocity;
}
/*
inline float Player::pitch() const
{
    return d_pitch;
}

inline float Player::yaw() const
{
    return d_yaw;
}

inline void Player::setPitch(float pitch)
{
    d_pitch = pitch;
}

inline void Player::setYaw(float yaw)
{
    d_yaw = yaw;
}
*/
        
#endif
