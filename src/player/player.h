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

    public:
        Player(Controller &controller);
        glm::mat4 const viewMat() const;
        glm::mat4 const projMat() const;

        void setProjMat(float fov, float ratio, float near, float far);

    private:
        void updateImpl(float deltaTime);
        void integratePosition(float deltaTime); // TODO: move to Entity?
        void modelMatUpdated();
};

        
#endif
