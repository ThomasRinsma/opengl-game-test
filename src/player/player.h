#ifndef INCLUDED_PLAYER_
#define INCLUDED_PLAYER_

#include <glm/glm.hpp> // for glm::vec3 and glm::mat4
#include "../controller/controller.h"
#include "../entity/entity.h"

class Player : public Entity
{
    static constexpr float s_mouseSpeed = 0.001f * M_PI; // radians per pixel
    static constexpr float s_moveSpeed = 3.0f; // units per second

    Controller &d_controller;
    glm::mat4 d_projMat;

    // Keep these seperate because Entity's quaternion likes to
    // mess them up which makes it hard to check for bounds
    float d_pitch;
    float d_yaw;
    float d_roll;

    // Projection matrix stuff
    float d_fov;
    float d_screenRatio;
    float d_zNear;
    float d_zFar;

    public:
        Player(Controller &controller);
        glm::mat4 const viewMat() const;
        glm::mat4 const projMat() const;

        void setFov(float fov);
        void setScreenRatio(float screenRatio);
        void setZnear(float zNear);
        void setZfar(float zFar);

        float fov() const;
        float screenRatio() const;
        float zNear() const;
        float zFar() const;

    private:
        void updateImpl(float deltaTime);
        void integratePosition(float deltaTime); // TODO: move to Entity?
        void modelMatUpdated();
        void updateProjMat();
};


inline void Player::setFov(float fov)
{
    d_fov = fov;
    updateProjMat();
}

inline void Player::setScreenRatio(float screenRatio)
{
    d_screenRatio = screenRatio;
    updateProjMat();
}

inline void Player::setZnear(float zNear)
{
    d_zNear = zNear;
    updateProjMat();
}

inline void Player::setZfar(float zFar)
{
    d_zFar = zFar;
    updateProjMat();
}


inline float Player::fov() const
{
    return d_fov;
}

inline float Player::screenRatio() const
{
    return d_screenRatio;
}

inline float Player::zNear() const
{
    return d_zNear;
}

inline float Player::zFar() const
{
    return d_zFar;
}



        
#endif
